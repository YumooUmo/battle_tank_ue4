// Fill out your copyright notice in the Description page of Project Settings.

#include "StraightWeaponComponent.h"
//FIRST include
#include "Config.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TankHUD.h"
#include "TankPlayerController.h"
#include "TankProjectile.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UStraightWeaponComponent::UStraightWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	UE_LOG(LogTemp, Warning, TEXT("DONKEY : WeaponComponent C++ Construct "));
}
// Called when the game starts
void UStraightWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_setup_ui();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : WeaponComponent C++ BeginPlay "));
}
// Called every frame
void UStraightWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

// ## PUBLIC ##

// - Ammo -
//add
void UStraightWeaponComponent::_add_ammo(uint8 number_toset, uint8 ammo_toadd)
{
	// add 0
	if (ammo_toadd == 0 || !projectile_token[number_toset])
		return;
	// not current weapon
	if (number_toset < 10 && projectile_number % 10 != number_toset)
	{
		ammo_amount[number_toset] += ammo_toadd;
		return;
	}
	//current weapon
	ammo_amount[projectile_number % 10] += ammo_toadd;
	if (weapon_state == WeaponState::out_of_ammo)
	{
		weapon_state = WeaponState::empty;
	}
	// - UI -
	if (tank_hud)
		tank_hud->_set_ammo_amount(_get_ammo());
};
void UStraightWeaponComponent::_add_ammo(uint8 ammo_toadd)
{
	if (ammo_toadd == 0 || !_get_current_projectile())
		return;
	ammo_amount[projectile_number % 10] = ammo_toadd;
	if (weapon_state == WeaponState::out_of_ammo)
	{
		weapon_state = WeaponState::empty;
	}
	// - UI -
	if (tank_hud)
		tank_hud->_set_ammo_amount(_get_ammo());
};
//minus
void UStraightWeaponComponent::_minus_ammo(uint8 ammo_tominus)
{
	if (!_get_current_projectile())
	{
		return;
	}
	if (_get_ammo() > ammo_tominus)
	{
		ammo_amount[projectile_number % 10] -= ammo_tominus;
	}
	else
	{
		ammo_amount[projectile_number % 10] = 0;
		projectile_token[projectile_number % 10] = nullptr;
		weapon_state = WeaponState::out_of_ammo;
	}
	// - UI -
	if (tank_hud)
		tank_hud->_set_ammo_amount(_get_ammo());
};

/* - SETUP - */
//set
void UStraightWeaponComponent::_setup_projectile(uint8 num_toset,
												 TSubclassOf<ATankProjectile> projectile_toset,
												 uint8 ammo_toset)
{
	if (ammo_toset > 0 && projectile_toset && num_toset < 10)
	{
		if (projectile_toset)
		{
			projectile_token[num_toset < 10 ? num_toset : projectile_number % 10] = projectile_toset;
		}
		_add_ammo(num_toset, ammo_toset);
		// - Update UI -
		if (tank_hud)
		{
			tank_hud->_setup_projectile(_get_image());
		}
	}
};
//add
void UStraightWeaponComponent::_add_projectile(TSubclassOf<ATankProjectile> projectile_toset,
											   uint8 ammo_toset)
{
	for (uint8 temp = 0; temp < 10; temp++)
	{
		if (ammo_amount[temp] > 0)
			continue;
		_setup_projectile(temp, projectile_toset, ammo_toset);
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("DONKEY : Projectile Full ~! (Already 10 types token)"));
};

/* - GET - */
// Weapon -
TSubclassOf<ATankProjectile> UStraightWeaponComponent::_get_current_projectile()
{
	return projectile_token[projectile_number % 10];
};
//current_number
uint8 UStraightWeaponComponent::_get_current_number()
{
	return projectile_number % 10;
}
// Projectile -
//launch_speed
float UStraightWeaponComponent::_get_launch_speed()
{
	if (!_get_current_projectile())
	{
		return 0.f;
	}
	ATankProjectile *projectile = _get_current_projectile().GetDefaultObject();
	return (projectile->_get_launch_speed(launch_force)); // Here is the point
}
float UStraightWeaponComponent::_get_reload_time()
{
	if (!_get_current_projectile())
	{
		return 0.f;
	}
	return _get_current_projectile().GetDefaultObject()->_get_reload_time(); // Here is the point
}
UTexture2D *UStraightWeaponComponent::_get_image()
{
	if (!_get_current_projectile())
	{
		return nullptr;
	}
	return _get_current_projectile().GetDefaultObject()->_get_projectile_image(); // Here is the point
}
WeaponState UStraightWeaponComponent::_get_weapon_state()
{
	return weapon_state;
};
// Ammo -
uint8 UStraightWeaponComponent::_get_ammo(uint8 num)
{
	if (num > 10)
		return ammo_amount[projectile_number % 10];
	return ammo_amount[num];
}
uint8 UStraightWeaponComponent::_get_ammo()
{
	return ammo_amount[projectile_number % 10];
}

/* - Weapon Action - */
//add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
bool UStraightWeaponComponent::_set_projectile(uint8 number)
{
	if (projectile_number % 10 != number && number < 10)
	{
		//Add check : if weapon exists (is set alreloaded) ? 	------------------TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
		if (ammo_amount[number] > 0)
		{
			projectile_number = (projectile_number % 10) * 10 + number;
			// - UI -
			//set projectile image (HUD)
			if (tank_hud)
			{
				tank_hud->_setup_projectile(_get_image());
				tank_hud->_set_ammo_amount(_get_ammo());
			}
			weapon_state = WeaponState::empty;
			_reload();
			return true;
		}
	}
	return false;
};
//set exchange weapon
bool UStraightWeaponComponent::_exchange_projectile()
{
	if (projectile_number != 0)
	{
		if (ammo_amount[projectile_number / 10] > 0)
		{
			projectile_number = (projectile_number % 10) * 10 + (projectile_number / 10);
			// - UI -
			if (tank_hud)
			{
				tank_hud->_setup_projectile(_get_image());
				tank_hud->_set_ammo_amount(_get_ammo());
			}
			weapon_state = WeaponState::empty;
			_reload();
			return true;
		}
	}
	//NO last used weapon
	return false;
};
//fire
void UStraightWeaponComponent::_fire()
{
	if (_get_ammo() > 0 && barrel)
	{
		if (weapon_state == WeaponState::ready)
		{
			weapon_state = WeaponState::empty;
			// - UI -
			if (tank_hud)
			{
				tank_hud->_hide_projectile_image();
				tank_hud->_set_ammo_amount(_get_ammo());
			}
			GetWorld()->SpawnActor<ATankProjectile>(
						  _get_current_projectile(),
						  _get_launch_location(),
						  _get_launch_normal().Rotation())
				->_launch(launch_force);
			_lock(false);
			//Last Minus and (if null)delete current projectile
			_minus_ammo(1);
		}
	}
};
//reload
void UStraightWeaponComponent::_reload()
{
	if (weapon_state == WeaponState::empty)
	{
		weapon_state = WeaponState::reloading;
		GetWorld()->GetTimerManager().SetTimer(reload_timer, this,
											   &UStraightWeaponComponent::_reload_ready,
											   _get_reload_time(), false);
		// - UI -
		if (tank_hud)
		{
			tank_hud->_reload_projectile();
		}
	}
};
//ready
void UStraightWeaponComponent::_reload_ready()
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

/* - LOCK - */
//Lock Action -
//call in
void UStraightWeaponComponent::_lock(bool flag)
{
	if (_get_current_projectile() && barrel)
	{
		//Draw_Path : Pressed
		if (aiming_state != AimingState::overheat)
		{
			if (flag)
			{
				aiming_state = AimingState::locking;
				if (lock_timer.IsValid())
				{
					return;
				}
				GetWorld()->GetTimerManager().SetTimer(lock_timer, this,
													   &UStraightWeaponComponent::_should_lock,
													   pace, true);
				// - UI -
				tank_hud->_do_lock_buffer();
			}
			//Draw_Path : Released
			else
			{
				aiming_state = AimingState::usable;
			}
		}
	}
};
// lock buffer counter
void UStraightWeaponComponent::_should_lock()
{
	//Draw_Path : Pressed
	if (aiming_state == AimingState::locking)
	{
		if (lock_buffer <= 0.f)
		{
			lock_buffer = -overheat_lag;
			aiming_state = AimingState::overheat;
		}
		else
		{
			lock_buffer -= pace;
			UStraightWeaponComponent::_draw_projectile_path();
		}
	}
	//Draw_Path : Not Pressed
	else
	{
		if (lock_buffer < max_buffer)
		{
			lock_buffer += pace * cool_rate;
			if (aiming_state == AimingState::overheat && lock_buffer > recover_value)
			{
				aiming_state = AimingState::usable;
			}
			//limit
			if (lock_buffer > max_buffer)
			{
				lock_buffer = max_buffer;
				GetWorld()->GetTimerManager().ClearTimer(lock_timer);
			}
		}
	}
	// - UI -
	tank_hud->_update_lock_buffer(FMath::GetRangePct(0.f, max_buffer, lock_buffer), aiming_state);
};
// - Draw UI -
void UStraightWeaponComponent::_draw_projectile_path()
{
	//Initiallize Parameters to _predict path method()
	FVector launch_velocity = _get_launch_normal() * _get_launch_speed();
	FVector launch_location = _get_launch_location();

	FPredictProjectilePathParams PredictParams{
		10.f,			 //CollisionRadius
		launch_location, //start location
		launch_velocity,
		3.0f, //MaxSimTime
		ECollisionChannel::ECC_Visibility,
		nullptr};

	PredictParams.ActorsToIgnore.Add(GetOwner());

	//Initiallize Result Struct to _predict path method()
	FPredictProjectilePathResult PredictResult;

	if (UGameplayStatics::PredictProjectilePath(
			this,
			PredictParams,
			PredictResult))
	{
		//----####有效射程	in MaxSimTime
		//获得第一个击中点
		//---------------------------------------------------------Debug
		DrawDebugSphere(
			GetWorld(),
			PredictResult.HitResult.Location,
			100.f,
			64.f,
			FColor::Blue);
	}
	else
	{
		//-----####有效射程外 out of MaxSimTime
		//---------------------------------------------------------Debug
		DrawDebugSphere(
			GetWorld(), //start location
			PredictResult.LastTraceDestination.Location,
			100.f,
			64.f,
			FColor::Blue);
	}
}
