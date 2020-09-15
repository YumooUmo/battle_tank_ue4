// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "AimingComponent.h"
#include "ForceNavMovementComponent.h"
#include "StraightWeaponComponent.h"

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
	// - BP -
	Super::BeginPlay();
	//Cpp
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ BeginPlay "), *name);
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
void ATank::_setup_component(UStraightWeaponComponent *weapon_component_toset,
							 UForceNavMovementComponent *move_component_toset)
{
	//runtime new component : Component* component = NewObject<Comoponent>(FName);
	//-----------------------component->RegisterComponent();
	weapon_component = weapon_component_toset;
	move_component = move_component_toset;
};
//setup - UI -
void ATank::_setup_ui()
{
	// - UI -
	if (IsPlayerControlled())
	{
		if (ensure(weapon_component))
		{
			weapon_component->_set_hud();
			weapon_component->_setup_widget();
		}
	}
};

// - Get -
// is aiming on
bool ATank::_is_aiming_on()
{
	if (weapon_component)
		return weapon_component->_is_aiming_on();
	return false;
}

// - Turning -
void ATank::_turning_to(FVector aiming_normal)
{
	if (weapon_component)
	{
		weapon_component->_turning_to(aiming_normal);
	}
}
// - AI - aiming at location
void ATank::_ai_turning(FVector location)
{
	if (weapon_component)
		weapon_component->_ai_turning(location);
}

// ## Bind Action ##
/*	with UI */
// - Lock -
void ATank::_lock(bool if_lock)
{
	if (!weapon_component)
	{
		return;
	}
	weapon_component->_lock(if_lock);
}
// - Weapon -	#### TODO : add new weapon
//set projectile by number - (Initialize Weapon)
void ATank::_set_projectile(uint8 number)
{
	if (!weapon_component)
	{
		return;
	}
	weapon_component->_set_projectile(number);
};
//exchange
void ATank::_exchange_projectile()
{
	if (!weapon_component)
	{
		return;
	}
	weapon_component->_exchange_projectile();
};
//fire()
void ATank::_fire()
{
	if (!weapon_component)
	{
		return;
	}
	weapon_component->_fire();
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
