// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "ForceNavMovementComponent.h"
#include "WeaponComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ Construct "), *name);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	//BP
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;
	//Cpp
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ BeginPlay "), *name);

	// - UI -
	if (IsPlayerControlled())
	{
		if (ensure(aiming_component))
		{
			aiming_component->_set_hud();
			aiming_component->_set_widget();
		}

		if (ensure(weapon_component))
			weapon_component->_set_hud();
	}
	// - Initialize  weapon -
	_set_weapon(0);
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

	//Show Widget : When start being Possessed by Player
}

//----------------------------------		PUBLIC		----------------------------------------
//	Set Up
void ATank::_setup(UAimingComponent *aiming_component_toset,
				   UWeaponComponent *weapon_component_toset,
				   UForceNavMovementComponent *move_component_toset)
{
	//runtime new component : Component* component = NewObject<Comoponent>(FName);
	//-----------------------component->RegisterComponent();
	aiming_component = aiming_component_toset;
	weapon_component = weapon_component_toset;
	move_component = move_component_toset;
};

// - Get -

// ## Bind Action ##

/*	with UI */
// - Aiming -
void ATank::_turning_to(FVector aiming_normal)
{
	if (aiming_component)
	{
		aiming_component->_turning_to(aiming_normal);
	}
}

void ATank::_aiming_at(FVector location)
{
	_turning_to(location - aiming_component->_get_launch_location());
}

// - Lock -
void ATank::_lock(bool if_lock)
{
	if (!aiming_component)
	{
		return;
	}
	aiming_component->_lock(if_lock);
}

// - Weapon -	#### TODO : add new weapon
//set projectile by number - (Initialize Weapon)
void ATank::_set_weapon(uint8 number)
{
	if (!weapon_component)
	{
		return;
	}
	if (weapon_component->_set_weapon(number))
		aiming_component->_update_launch_speed(weapon_component->_get_launch_speed());
};
//exchange
void ATank::_exchange_weapon()
{
	if (!weapon_component)
	{
		return;
	}
	if (weapon_component->_exchange_weapon())
		aiming_component->_update_launch_speed(weapon_component->_get_launch_speed());
};
//fire()
void ATank::_fire()
{
	if (!weapon_component || !aiming_component || !aiming_component->_is_barrel())
	{
		return;
	}
	weapon_component->_fire(aiming_component->_get_launch_normal(),
							aiming_component->_get_launch_location());
};
//reload
void ATank::_reload()
{
	if (!weapon_component)
	{
		return;
	}
	weapon_component->_reload();
};

/*	without UI */
// - Move -
void ATank::_move_forward(bool if_move)
{
	if (!move_component)
	{
		return;
	}
	move_component->_move_forward(if_move);
};
void ATank::_move_backward(bool if_move)
{
	if (!move_component)
	{
		return;
	}
	move_component->_move_backward(if_move);
};
void ATank::_move_left(bool if_move)
{
	if (!move_component)
	{
		return;
	}
	move_component->_move_left(if_move);
};
void ATank::_move_right(bool if_move)
{
	if (!move_component)
	{
		return;
	}
	move_component->_move_right(if_move);
};
void ATank::_burst(bool if_burst)
{
	if (!move_component)
	{
		return;
	}
	move_component->_burst(if_burst);
};
//move by stick
void ATank::_move_stick(float LT_X, float LT_Y)
{
	move_component->_input_stick(LT_X, LT_Y);
}
