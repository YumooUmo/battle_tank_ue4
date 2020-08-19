// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankProjectile.h"
#include "TankTurrent.h"
#include "TankTrack.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	aiming_component = CreateDefaultSubobject<UAimingComponent>(FName(TEXT("aiming_component")));
	aiming_component->_set_owner(this);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
//-----------------------------------------------------private--------------------------------------------------------
//Set Barrel Reference
void ATank::_set_barrel_reference(UTankBarrel *barrel_to_set)
{
	barrel = barrel_to_set;
};

//Set Turrent Reference
void ATank::_set_turrent_reference(UTankTurrent *turrent_to_set)
{
	turrent = turrent_to_set;
};

//Set Track Reference
void ATank::_set_left_track_reference(UTankTrack *track_to_set)
{
	left_track = track_to_set;
};
void ATank::_set_right_track_reference(UTankTrack *track_to_set)
{
	right_track = track_to_set;
};

//GET Current Projectile
TSubclassOf<ATankProjectile> ATank::_get_current_projectile()
{
	switch (projectile_number % 10)
	{
	case 0:
		if (tank_projectile_0)
		{
			return tank_projectile_0;
		}
		else
		{
			return nullptr;
		}
		break;
	case 1:
		if (tank_projectile_1)
		{
			return tank_projectile_1;
		}
		else
		{
			return nullptr;
		}
		break;
	default:
		return nullptr;
		break;
	}
};

//------------------------------------------------------public----------------------------------------------------------  TODO : Refactor switch to Template
//SET projectile number---------------------------------------------####   TODO : Refactor switch to Template
//Add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
void ATank::_set_projectile_number(int number)
{
	if (projectile_number % 10 != number)
	{
		//Add check : if projectile exists (is set already) ? 	------------------TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
		switch (number)
		{
		case 0:
			if (tank_projectile_0)
			{
				projectile_number = (projectile_number % 10) * 10 + number;
				reloaded = false;
				_reload();
			}

			break;
		case 1:
			if (tank_projectile_1)
			{
				projectile_number = (projectile_number % 10) * 10 + number;
				reloaded = false;
				_reload();
			}
			break;
		default:
			break;
		}
	}
};

//SET exchange weapon
void ATank::_exchange_projectile()
{
	if (projectile_number != 0)
	{
		projectile_number = (((projectile_number % 10) * 10) + (projectile_number / 10));
		reloaded = false;
		_reload();
	}
};

//Get Current Projectile's Launch Speed
float ATank::_get_launch_speed()
{
	return _get_current_projectile().GetDefaultObject()->launch_speed; // Here is the point
}

//Launch()
void ATank::_fire()
{
	if (barrel && (FPlatformTime::Seconds() - start_reload_time) > _get_current_projectile().GetDefaultObject()->reload_time && reloaded == true)
	{
		reloaded = false;
		GetWorld()->SpawnActor<ATankProjectile>(
					  _get_current_projectile(),
					  barrel->_get_launch_location(),
					  barrel->_get_launch_normal().Rotation())
			->_launch();
	}
};

//Reload
void ATank::_reload()
{
	if ((FPlatformTime::Seconds() - start_reload_time) > _get_current_projectile().GetDefaultObject()->reload_time && reloaded == false)
	{
		start_reload_time = FPlatformTime::Seconds();
		reloaded = true;
		UE_LOG(LogTemp, Warning, TEXT("Reloading ~!"));
	}
	// UE_LOG(LogTemp, Warning, TEXT("Can't reload , Minus : %f , Reloaded is %i"), FPlatformTime::Seconds() - start_reload_time, reloaded);
};
