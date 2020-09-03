// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "ForceNavMovementComponent.h"
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
//	Set Up
void ATank::_set_up(UTankBarrel *barrel_to_set, UTankTurrent *turrent_to_set,
					UTankTrack *left_track_to_set, UTankTrack *right_track_to_set,
					UAimingComponent *aiming_component_toset,
					UWeaponComponent *weapon_component_toset,
					UForceNavMovementComponent *move_component_toset)
{
	//Set Barrel Reference
	barrel = barrel_to_set;
	//Set Turrent Reference
	turrent = turrent_to_set;
	//Set Track Reference
	left_track = left_track_to_set;
	right_track = right_track_to_set;

	//runtime new component : Component* component = NewObject<Comoponent>(FName);
	//-----------------------component->RegisterComponent();
	aiming_component = aiming_component_toset;
	weapon_component = weapon_component_toset;
	move_component = move_component_toset;
};

//	Start Up : Controller_Tick
void ATank::_controller_do(FVector aiming_normal)
{
	_turning_to(aiming_normal);

	if (aiming_component && aiming_component->_should_lock())
	{
		aiming_component->_lock_projectile_path(_get_launch_normal() * _get_launch_speed(),
												_get_launch_location(), this);
	}

	if (move_component && move_component->_should_move())
	{
		left_track->_apply_force(move_component->_get_left_throttle());
		right_track->_apply_force(move_component->_get_right_throttle());
	}
}

//---------------------------------------------        PUBLIC : GET        -------------------------------------
//Get Current Launch direction normal
FVector ATank::_get_launch_normal()
{
	if (barrel == nullptr)
	{
		return GetActorForwardVector();
	}
	return barrel->_get_launch_normal();
};
//Get Current Launch location
FVector ATank::_get_launch_location()
{
	if (barrel == nullptr)
	{
		return GetActorLocation();
	}

	return barrel->_get_launch_location();
}
//Get Current Projectile's Launch Speed
float ATank::_get_launch_speed()
{
	if (weapon_component == nullptr)
	{
		return 600.f;
	}
	return weapon_component->_get_launch_speed();
}


//---------------------------------------------		PUBLIC :PLAY		---------------------------	#### TODO : Refactor switch to Template
//										UI
// self action
void ATank::_turning_to(FVector aiming_normal)
{
	if (barrel == nullptr || turrent == nullptr)
	{
		return;
	}
	FRotator launch_rotation = _get_launch_normal().Rotation();
	float pitch = aiming_normal.Rotation().Pitch - launch_rotation.Pitch;
	float yaw = aiming_normal.Rotation().Yaw - launch_rotation.Yaw;

	if (FMath::Abs(yaw) <= 0.001f && FMath::Abs(pitch) <= 0.001f)
	{
		if (turning)
		{
			turning = false;
		}
		return;
	}

	if (FMath::Abs(pitch) > 0.001f)
	{
		//call _elevate_barrel
		barrel->_elevate_barrel(pitch);
	}
	if (FMath::Abs(yaw) > 0.001f)
	{
		//call   _rotate_turrent
		turrent->_rotate_turrent(yaw);
	}

	if (!turning)
	{
		turning = true;
	}

	/*  #### BUG fixed : Value tremble around destnation. 
    *   Float value is not accurate.
    *   Method is : Lower accurency.
    */
};

//Exchange projectile by number
//Add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
void ATank::_set_weapon(uint8 number)
{
	if (weapon_component == nullptr)
	{
		return;
	}
	weapon_component->_exchange_weapon(number);
};

//Exchange
void ATank::_exchange_weapon()
{
	if (weapon_component == nullptr)
	{
		return;
	}
	weapon_component->_exchange_weapon();
};

//Fire()
void ATank::_fire()
{
	if (barrel == nullptr || weapon_component == nullptr)
	{
		return;
	}
	weapon_component->_fire(_get_launch_normal(), _get_launch_location());
};

//Reload
void ATank::_reload()
{
	if (weapon_component == nullptr)
	{
		return;
	}

	weapon_component->_reload();
	// UE_LOG(LogTemp, Warning, TEXT("Can't reload , Minus : %f , Reloaded is %i"), FPlatformTime::Seconds() - start_reload_time, reloaded);
};

//DrawProjectilePath
void ATank::_lock(bool if_lock)
{
	if (aiming_component == nullptr)
	{
		return;
	}
	aiming_component->_lock(if_lock);
}

//										No UI
//Move
void ATank::_move_forward(bool if_move)
{
	if (move_component == nullptr)
	{
		return;
	}
	move_component->_move_forward(if_move);
};
void ATank::_move_backward(bool if_move)
{
	if (move_component == nullptr)
	{
		return;
	}
	move_component->_move_backward(if_move);
};
void ATank::_move_left(bool if_move)
{
	if (move_component == nullptr)
	{
		return;
	}
	move_component->_move_left(if_move);
};
void ATank::_move_right(bool if_move)
{
	if (move_component == nullptr)
	{
		return;
	}
	move_component->_move_right(if_move);
};
void ATank::_burst(bool if_burst)
{
	if (move_component == nullptr)
	{
		return;
	}
	move_component->_burst(if_burst);
};
