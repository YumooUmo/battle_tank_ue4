// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
//FIRST include
#include "TankPlayerController.h"
#include "TankProjectile.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	player_controller = Cast<ATankPlayerController>(Cast<APawn>(GetOwner())->GetController());
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//----------------------------		PUBLIC		--------------------------	#### TODO : Refactor switch to Template
//----------------------------		SET			----------------------------------
void UWeaponComponent::_set_projectile(TSubclassOf<ATankProjectile> projectile_Subclass_0,
									   TSubclassOf<ATankProjectile> projectile_Subclass_1)
{
	tank_projectile_0 = projectile_Subclass_0;
	tank_projectile_1 = projectile_Subclass_1;
};

//----------------------------		GET			----------------------------------
//Subclass of projectile -
TSubclassOf<ATankProjectile> UWeaponComponent::_get_current_projectile()
{
	switch (weapon_number % 10)
	{
	case 0:
		return tank_projectile_0;
		break;
	case 1:
		return tank_projectile_1;
		break;
	default:
		return nullptr;
		break;
	}
};
//launch_speed -
float UWeaponComponent::_get_launch_speed()
{
	if (_get_current_projectile() == nullptr)
	{
		return 0.f;
	}
	return _get_current_projectile().GetDefaultObject()->launch_force; // Here is the point
}
//reload_time -
float UWeaponComponent::_get_reload_time()
{
	if (_get_current_projectile() == nullptr)
	{
		return 0.f;
	}
	return _get_current_projectile().GetDefaultObject()->reload_time; // Here is the point
}
//Image -
UTexture2D *UWeaponComponent::_get_image()
{
	if (_get_current_projectile() == nullptr)
	{
		return nullptr;
	}
	return _get_current_projectile().GetDefaultObject()->projectile_image; // Here is the point
}
//Enum -
WeaponState UWeaponComponent::_get_weapon_state()
{
	return weapon_state;
};

//----------------------------		PLAY		----------------------------------
//Add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
void UWeaponComponent::_set_weapon(uint8 number)
{
	if (weapon_number % 10 != number)
	{
		//Add check : if weapon exists (is set alreloaded) ? 	------------------TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
		switch (number)
		{
		case 0:
			if (tank_projectile_0 != nullptr)
			{
				weapon_number = (weapon_number % 10) * 10 + number;
				weapon_state = WeaponState::empty;

				_reload();
			}
			break;
		case 1:
			if (tank_projectile_1 != nullptr)
			{
				weapon_number = (weapon_number % 10) * 10 + number;
				weapon_state = WeaponState::empty;
				_reload();
			}
			break;
		default:
			break;
		}
	}
	// - UI -
	if (player_controller)
	{
		player_controller->_setup_projectile();
	}
};

//SET exchange weapon
void UWeaponComponent::_exchange_weapon()
{
	if (weapon_number != 0)
	{
		int8 temp = weapon_number / 10;
		weapon_number = (((weapon_number % 10) * 10) + temp);
		weapon_state = WeaponState::empty;
		_reload();
	}
	// - UI -
	if (player_controller)
	{
		player_controller->_setup_projectile();
	}
};

//Fire
void UWeaponComponent::_fire(FVector launch_normal, FVector launch_location)
{
	if (_get_current_projectile())
	{
		if (weapon_state == WeaponState::ready)
		{
			weapon_state = WeaponState::empty;
			GetWorld()->SpawnActor<ATankProjectile>(
						  _get_current_projectile(),
						  launch_location,
						  launch_normal.Rotation())
				->_launch();
			// - UI -
			if (player_controller)
			{
				player_controller->_hide_projectile_image();
			}
		}
	}
};

//Reload
void UWeaponComponent::_reload()
{
	if (weapon_state == WeaponState::empty)
	{
		weapon_state = WeaponState::reloading;
		GetWorld()->GetTimerManager().SetTimer(reload_timer, this,
											   &UWeaponComponent::_reload_ready,
											   _get_reload_time(), false);
		// - UI -
		if (player_controller)
		{
			player_controller->_reload_projectile();
		}
	}
};

//Ready
void UWeaponComponent::_reload_ready()
{
	weapon_state = WeaponState::ready;
	GetWorld()->GetTimerManager().ClearTimer(reload_timer);
	// - UI -
	if (player_controller)
	{
		player_controller->_reload_ready();
	}
}
