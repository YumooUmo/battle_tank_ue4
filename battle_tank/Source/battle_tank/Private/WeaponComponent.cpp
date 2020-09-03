// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
//FIRST include
#include "TankProjectile.h"
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
//----------------------------		PUBLIC		--------------------------	#### TODO : Refactor switch to Template
//----------------------------		SET			----------------------------------
void UWeaponComponent::_set_projectile(TSubclassOf<ATankProjectile> projectile_Subclass_0,
									   TSubclassOf<ATankProjectile> projectile_Subclass_1)
{
	tank_projectile_0 = projectile_Subclass_0;
	tank_projectile_1 = projectile_Subclass_1;
};

//----------------------------		GET			----------------------------------
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

float UWeaponComponent::_get_launch_speed()
{
	if (_get_current_projectile() == nullptr)
	{
		return 0.f;
	}
	return _get_current_projectile().GetDefaultObject()->launch_force; // Here is the point
}
//----------------------------		PLAY		----------------------------------
//Add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
int8 UWeaponComponent::_exchange_weapon(uint8 number)
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
				reloaded = false;
				_reload();
				return (int8)number;
			}
			break;
		case 1:
			if (tank_projectile_1 != nullptr)
			{
				weapon_number = (weapon_number % 10) * 10 + number;
				reloaded = false;
				_reload();
				return (int8)number;
			}
			break;
		default:
			break;
		}
	}
	return -1;
};

//SET exchange weapon
int8 UWeaponComponent::_exchange_weapon()
{
	if (weapon_number != 0)
	{
		int8 temp = weapon_number / 10;
		weapon_number = (((weapon_number % 10) * 10) + temp);
		reloaded = false;
		_reload();
		return temp;
	}
	return -1;
};

//Fire()
bool UWeaponComponent::_fire(FVector launch_normal, FVector launch_location)
{
	if (_get_current_projectile() == nullptr)
	{
		return false;
	}

	if (FPlatformTime::Seconds() > end_reload_time && reloaded)
	{
		reloaded = false;
		GetWorld()->SpawnActor<ATankProjectile>(
					  _get_current_projectile(),
					  launch_location,
					  launch_normal.Rotation())
			->_launch();
		return true;
	}
	return false;
};

//Reload
float UWeaponComponent::_reload()
{
	if (reloaded == false)
	{
		float temp = _get_current_projectile().GetDefaultObject()->reload_time;
		end_reload_time = FPlatformTime::Seconds() + temp;
		reloaded = true;
		UE_LOG(LogTemp, Warning, TEXT("reloaded ~!"));
		return temp;
	}
	return -1.f;
	// UE_LOG(LogTemp, Warning, TEXT("Can't reload , Minus : %f , reloaded is %i"), FPlatformTime::Seconds() - end_reload_time, reloaded);
};

//----------------------------		Enum	----------------------------------
WeaponState UWeaponComponent::_get_weapon_state()
{
	return FPlatformTime::Seconds() > end_reload_time ? (reloaded ? WeaponState::ready : WeaponState::empty)
													  : WeaponState::reloading;
};