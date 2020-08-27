// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankProjectile.h"
#include "TankTrack.h"
#include "TankTurrent.h"
#include "WeaponComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//runtime new component : Component* component = NewObject<Comoponent>(FName);
	//-----------------------component->RegisterComponent();
	aiming_component = CreateDefaultSubobject<UAimingComponent>(FName(TEXT("AimingComponent")));
	// weapon_component = CreateDefaultSubobject<UWeaponComponent>(FName(TEXT("WeaponComponent")));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	// PrimaryActorTick.bCanEverTick =false; //------------------------------------------------------------------TODO : start_up
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
void ATank::set_weapon_component(UWeaponComponent *component)
{
	weapon_component = component;
};

//---------------------------------------------		PUBLIC : GET		-------------------------------------
//Get Current Launch direction normal
FVector ATank::_get_launch_normal()
{
	return barrel->_get_launch_normal();
};
//Get Current Launch location
FVector ATank::_get_launch_location()
{
	return barrel->_get_launch_location();
};
//Get Current Projectile's Launch Speed
float ATank::_get_launch_speed()
{
	return weapon_component->_get_launch_speed(); // Here is the point
}

//---------------------------------------------		PUBLIC :PLAY		---------------------------	#### TODO : Refactor switch to Template
//Exchange projectile by number
//Add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
void ATank::_set_weapon(int number)
{
	weapon_component->_exchange_weapon(number);
};

//Exchange
void ATank::_exchange_weapon()
{
	weapon_component->_exchange_weapon();
};

//Fire()
void ATank::_fire()
{
	if (barrel)
	{
		weapon_component->_fire(_get_launch_normal(), _get_launch_location());
	}
};

//Reload
void ATank::_reload()
{
	weapon_component->_reload();
	// UE_LOG(LogTemp, Warning, TEXT("Can't reload , Minus : %f , Reloaded is %i"), FPlatformTime::Seconds() - start_reload_time, reloaded);
};

//DrawProjectilePath
void ATank::_draw()
{
	aiming_component->_set_drawable(true);
}
void ATank::_stop_draw()
{
	aiming_component->_set_drawable(false);
}

// //Move
// void ATankPlayerController::_set_left_throttle(float throttle)
// {
//     left_track->_set_throttle(throttle);
// };
// void ATankPlayerController::_set_right_throttle(float throttle)
// {
//     right_track->_set_throttle(throttle);
// };

//--------------------------------------------------Public : self action------------------------------------------------------------

void ATank::_aiming_at(FVector aiming_normal)
{
	//Caculate rotation speed : by using ----   aiming_normal & launch velocity
	FRotator delta_rotator = aiming_normal.Rotation() - _get_launch_normal().Rotation();

	//call _elevate_barrel
	if (delta_rotator.Pitch > 0.0001f || delta_rotator.Pitch < -0.0001f)
	{
		barrel->_elevate_barrel(delta_rotator.Pitch);
	}

	//		####		Format Yaw change direction,
	//		####		from -170 -> 170, move direction and amount is +340, but ACTUALLY should be -20.
	if (delta_rotator.Yaw > 180.f)
	{
		delta_rotator.Yaw = delta_rotator.Yaw - 360.f;
	}
	if (delta_rotator.Yaw < -180.f)
	{
		delta_rotator.Yaw = delta_rotator.Yaw + 360.f;
	}
	//call   _rotate_turrent
	if (delta_rotator.Yaw > 0.0001f || delta_rotator.Yaw < -0.0001f)
	{
		turrent->_rotate_turrent(delta_rotator.Yaw);
	}
};

void ATank::_controller_do(float DeltaTime, FVector aiming_normal)
{
	_aiming_at(aiming_normal);
	if (aiming_component->_is_drawable(DeltaTime))
	{
		aiming_component->_draw_projectile_path(_get_launch_normal() * _get_launch_speed(), _get_launch_location(), this);
	}
};
