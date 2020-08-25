// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankProjectile.h"
#include "TankTrack.h"
#include "TankTurrent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//runtime new component : Component* component = NewObject<Comoponent>(FName);
	//-----------------------component->RegisterComponent();
	aiming_component = CreateDefaultSubobject<UAimingComponent>(FName(TEXT("aiming_component")));
	aiming_component->_set_owner(this);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true; //------------------------------------------------------------------TODO : start_up
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
//-----------------------------------------------------Private--------------------------------------------------------
//-----------------------------------------------------Set Up
void ATank::_set_up(UTankBarrel *barrel_to_set, UTankTurrent *turrent_to_set, UTankTrack *left_track_to_set, UTankTrack *right_track_to_set)
{
	//Set Barrel Reference
	barrel = barrel_to_set;
	//Set Turrent Reference
	turrent = turrent_to_set;	
	//Set Track Reference
	left_track = left_track_to_set;
	right_track = right_track_to_set;
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

//------------------------------------------------Public : play action---------------------------	#### TODO : Refactor switch to Template
//------------------------------------------------SET projectile number
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

//Fire()
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

//--------------------------------------------------Public : self action------------------------------------------------------------

void ATank::_aiming_at(FVector aiming_normal)
{
	//Caculate rotation speed : by using ----   aiming_normal & launch velocity
	FRotator delta_rotator = aiming_normal.Rotation() - barrel->_get_launch_normal().Rotation();

	//call _elevate_barrel
	if (delta_rotator.Pitch > 0.001f || delta_rotator.Pitch < -0.001f)
	{
		barrel->_elevate_barrel(delta_rotator.Pitch);
	}

	//####-------------------------Format Yaw change direction, from -170 -> 170, move direction and amount is +340 , but ACTUALLY should be -20.------------------------------------
	if (delta_rotator.Yaw > 180.f)
	{
		delta_rotator.Yaw = delta_rotator.Yaw - 360.f;
	}
	if (delta_rotator.Yaw < -180.f)
	{
		delta_rotator.Yaw = delta_rotator.Yaw + 360.f;
	}
	//call   _rotate_turrent
	if (delta_rotator.Yaw > 0.01f || delta_rotator.Yaw < -0.01f)
	{

		turrent->_rotate_turrent(delta_rotator.Yaw);
	}
};
