// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankProjectile.h"
#include "TankTurrent.h"

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

//------------------------------------------------------public----------------------------------------------------------
//SET projectile number
void ATank::_set_projectile_number(int number)
{
	//Add check : if projectile exists (is set already) ? 	------------------TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
	switch (number)
	{
	case 0:
		if (tank_projectile_0)
		{
			projectile_number = (projectile_number % 10) * 10 + number;
		}
		break;
	case 1:
		if (tank_projectile_1)
		{
			projectile_number = (projectile_number % 10) * 10 + number;
		}
		break;
	default:
		break;
	}
};

//SET exchange weapon
void ATank::_exchange_projectile()
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile is : %i"), projectile_number);

	projectile_number = (((projectile_number % 10) * 10) + (projectile_number / 10));
};

//Get Launch Speed
float ATank::_get_launch_speed() //---------	TODO ------------Refact : using Template to get differen projectile speed
{
	switch (projectile_number % 10)
	{
	case 0:
		/* code */
		return tank_projectile_0.GetDefaultObject()->_get_launch_speed(); // Here is the point
		break;
	case 1:
		/* code */
		return tank_projectile_1.GetDefaultObject()->_get_launch_speed(); // Here is the point
		break;

	default:
		return 0.f;
		break;
	}
}

//Launch()
void ATank::_fire() //---------	TODO ------------Refact : using Template to Fire with differen projectile number
{
	if (!barrel)
	{
		return;
	}

	switch (projectile_number % 10)
	{
	case 0:
		GetWorld()->SpawnActor<ATankProjectile>(
					  tank_projectile_0,
					  barrel->_get_launch_location(),
					  barrel->_get_launch_normal().Rotation())
			->_launch();
		break;
	case 1:
		GetWorld()->SpawnActor<ATankProjectile>(
					  tank_projectile_1,
					  barrel->_get_launch_location(),
					  barrel->_get_launch_normal().Rotation())
			->_launch();
		break;
	default:
		break;
	}
};
