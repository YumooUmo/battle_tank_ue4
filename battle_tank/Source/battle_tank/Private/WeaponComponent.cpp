// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
//FIRST include
#include "Config.h"
#include "TankHUD.h"
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
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// ## PUBLIC ##

//add ammo
void UWeaponComponent::_add_ammo(uint8 ammo_toadd, uint8 number_toset)
{
	// add 0
	if (ammo_toadd == 0 || !weapons_token[number_toset])
		return;
	// not current weapon
	if (number_toset < 10 && weapon_number % 10 != number_toset)
	{
		ammo_amount[number_toset] += ammo_toadd;
		return;
	}
	//current weapon
	ammo_amount[weapon_number % 10] += ammo_toadd;
	if (weapon_state == WeaponState::out_of_ammo)
	{
		weapon_state = WeaponState::empty;
	}
	// - UI -
	if (tank_hud)
		tank_hud->_set_ammo_amount(_get_ammo());
};
void UWeaponComponent::_add_ammo(uint8 ammo_toadd)
{
	if (ammo_toadd == 0 || !_get_current_weapon())
		return;
	ammo_amount[weapon_number % 10] = ammo_toadd;
	if (weapon_state == WeaponState::out_of_ammo)
	{
		weapon_state = WeaponState::empty;
	}
	// - UI -
	if (tank_hud)
		tank_hud->_set_ammo_amount(_get_ammo());
};
//minus ammo
void UWeaponComponent::_minus_ammo(uint8 ammo_tominus)
{
	if (!_get_current_weapon())
	{
		return;
	}
	if (_get_ammo() > ammo_tominus)
	{
		ammo_amount[weapon_number % 10] -= ammo_tominus;
	}
	else
	{
		ammo_amount[weapon_number % 10] = 0;
		weapon_state = WeaponState::out_of_ammo;
	}
	// - UI -
	if (tank_hud)
		tank_hud->_set_ammo_amount(_get_ammo());
};

// - SET UP -
//Setup HUD -
void UWeaponComponent::_set_hud()
{
	if (ensure(Cast<ATankHUD>(
			Cast<APlayerController>(
				Cast<APawn>(GetOwner())
					->GetController())
				->GetHUD())))
	{
		tank_hud = Cast<ATankHUD>(
			Cast<APlayerController>(
				Cast<APawn>(GetOwner())
					->GetController())
				->GetHUD());
	}
};
//Initialize Weapon
void UWeaponComponent::_initialize_weapon(uint8 ammo_0, TSubclassOf<ATankProjectile> weapon_0,
										  uint8 ammo_1, TSubclassOf<ATankProjectile> weapon_1,
										  uint8 ammo_2, TSubclassOf<ATankProjectile> weapon_2,
										  uint8 ammo_3, TSubclassOf<ATankProjectile> weapon_3,
										  uint8 ammo_4, TSubclassOf<ATankProjectile> weapon_4,
										  uint8 ammo_5, TSubclassOf<ATankProjectile> weapon_5,
										  uint8 ammo_6, TSubclassOf<ATankProjectile> weapon_6,
										  uint8 ammo_7, TSubclassOf<ATankProjectile> weapon_7,
										  uint8 ammo_8, TSubclassOf<ATankProjectile> weapon_8,
										  uint8 ammo_9, TSubclassOf<ATankProjectile> weapon_9)
{
	if (weapon_0)
		weapons_token[0] = weapon_0;
	ammo_amount[0] = ammo_0;

	if (weapon_1)
		weapons_token[1] = weapon_1;
	ammo_amount[1] = ammo_1;

	if (weapon_2)
		weapons_token[2] = weapon_2;
	ammo_amount[2] = ammo_2;

	if (weapon_3)
		weapons_token[3] = weapon_3;
	ammo_amount[3] = ammo_3;

	if (weapon_4)
		weapons_token[4] = weapon_4;
	ammo_amount[4] = ammo_4;

	if (weapon_5)
		weapons_token[5] = weapon_5;
	ammo_amount[5] = ammo_5;

	if (weapon_6)
		weapons_token[6] = weapon_6;
	ammo_amount[6] = ammo_6;

	if (weapon_7)
		weapons_token[7] = weapon_7;
	ammo_amount[7] = ammo_7;

	if (weapon_8)
		weapons_token[8] = weapon_8;
	ammo_amount[8] = ammo_8;

	if (weapon_9)
		weapons_token[9] = weapon_9;
	ammo_amount[9] = ammo_9;

	if (_get_ammo() > 0)
		weapon_state = WeaponState::empty;
	if (tank_hud)
	{
		tank_hud->_setup_projectile(_get_image());
		tank_hud->_set_ammo_amount(_get_ammo());
	}
};
//set projectile
void UWeaponComponent::_setup_weapon(TSubclassOf<ATankProjectile> weapon_toset,
									 uint8 num_toset)
{
	if (weapon_toset)
	{
		weapons_token[num_toset < 10 ? num_toset : weapon_number % 10] = weapon_toset;
	}
};

// - GET -
// Weapon -
TSubclassOf<ATankProjectile> UWeaponComponent::_get_current_weapon()
{
	return weapons_token[weapon_number % 10];
};
//get current_number
uint8 UWeaponComponent::_get_current_number()
{
	return weapon_number % 10;
}
//get ammo
uint8 UWeaponComponent::_get_ammo(uint8 num)
{
	if (num > 10)
		return ammo_amount[weapon_number % 10];
	return ammo_amount[num];
}
uint8 UWeaponComponent::_get_ammo()
{
	return ammo_amount[weapon_number % 10];
}
//Enum
WeaponState UWeaponComponent::_get_weapon_state()
{
	return weapon_state;
};
// Projectile -
//launch_speed
float UWeaponComponent::_get_launch_speed()
{
	if (!_get_current_weapon())
	{
		return 0.f;
	}
	ATankProjectile *projectile = _get_current_weapon().GetDefaultObject();
	return (projectile->_get_launch_speed(launch_force)); // Here is the point
}
//reload_time
float UWeaponComponent::_get_reload_time()
{
	if (!_get_current_weapon())
	{
		return 0.f;
	}
	return _get_current_weapon().GetDefaultObject()->_get_reload_time(); // Here is the point
}
//Image
UTexture2D *UWeaponComponent::_get_image()
{
	if (!_get_current_weapon())
	{
		return nullptr;
	}
	return _get_current_weapon().GetDefaultObject()->_get_projectile_image(); // Here is the point
}

// - Bind Action -
//add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
bool UWeaponComponent::_set_weapon(uint8 number)
{
	if (weapon_number % 10 != number && number < 10)
	{
		//Add check : if weapon exists (is set alreloaded) ? 	------------------TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
		if (weapons_token[number])
		{
			weapon_number = (weapon_number % 10) * 10 + number;
			// - UI -
			//set projectile image (HUD)
			if (tank_hud)
			{
				tank_hud->_setup_projectile(_get_image());
			}
			//no ammo
			if (_get_ammo() < 1)
			{
				weapon_state = WeaponState::out_of_ammo;
				// - UI -
				if (tank_hud)
					tank_hud->_set_pjt_image_opacity(1.f);
			}
			//with ammo
			else
			{
				weapon_state = WeaponState::empty;
				// - UI - & reload
				_reload();
			}
			// - UI -
			if (tank_hud)
				tank_hud->_set_ammo_amount(_get_ammo());
			return true;
		}
	}
	return false;
};

//set exchange weapon
bool UWeaponComponent::_exchange_weapon()
{
	if (weapon_number != 0)
	{
		weapon_number = (weapon_number % 10) * 10 + (weapon_number / 10);
		// - UI -
		if (tank_hud)
		{
			tank_hud->_setup_projectile(_get_image());
		}
		if (_get_ammo() < 1)
		{
			weapon_state = WeaponState::out_of_ammo;
			// - UI -
			if (tank_hud)
				tank_hud->_set_pjt_image_opacity(1.f);
		}
		else
		{
			weapon_state = WeaponState::empty;
			// - UI - & reload
			_reload();
		}
		// - UI -
		if (tank_hud)
			tank_hud->_set_ammo_amount(_get_ammo());
		return true;
	}
	//NO last used weapon
	return false;
};

//fire
void UWeaponComponent::_fire(FVector launch_normal, FVector launch_location)
{
	if (_get_current_weapon())
	{
		if (weapon_state == WeaponState::ready)
		{
			weapon_state = WeaponState::empty;
			_minus_ammo(1);
			// - UI -
			if (tank_hud)
			{
				tank_hud->_hide_projectile_image();
				tank_hud->_set_ammo_amount(_get_ammo());
			}
			GetWorld()->SpawnActor<ATankProjectile>(
				_get_current_weapon(),
				launch_location,
				launch_normal.Rotation())
			->_launch(launch_force);
		}
	}
};

//reload
void UWeaponComponent::_reload()
{
	if (weapon_state == WeaponState::empty)
	{
		weapon_state = WeaponState::reloading;
		GetWorld()->GetTimerManager().SetTimer(reload_timer, this,
											   &UWeaponComponent::_reload_ready,
											   _get_reload_time(), false);
		// - UI -
		if (tank_hud)
		{
			tank_hud->_reload_projectile();
		}
	}
};

//ready
void UWeaponComponent::_reload_ready()
{
	if (weapon_state == WeaponState::reloading)
		weapon_state = WeaponState::ready;
	if (reload_timer.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(reload_timer);
	// - UI -
	if (tank_hud)
	{
		tank_hud->_reload_ready();
	}
};
