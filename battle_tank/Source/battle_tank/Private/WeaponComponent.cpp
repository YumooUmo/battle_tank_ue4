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

//----------------------------		GET			----------------------------------
TSubclassOf<ATankProjectile> UWeaponComponent::_get_current_projectile()
{
	switch (weapon_number % 10)
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

float UWeaponComponent::_get_launch_speed()
{
	return _get_current_projectile().GetDefaultObject()->launch_force; // Here is the point
}
//----------------------------		PLAY		----------------------------------
//Add check : if projectile exists (is set already) ? 	------------####   TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
void UWeaponComponent::_exchange_weapon(int number)
{
	if (weapon_number % 10 != number)
	{
		//Add check : if weapon exists (is set already) ? 	------------------TODO-------------add new weapon FUNCTION() : SET new tank_projectile;
		switch (number)
		{
		case 0:
			if (tank_projectile_0)
			{
				weapon_number = (weapon_number % 10) * 10 + number;
				reloaded = false;
				_reload();
			}

			break;
		case 1:
			if (tank_projectile_1)
			{
				weapon_number = (weapon_number % 10) * 10 + number;
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
void UWeaponComponent::_exchange_weapon()
{
	if (weapon_number != 0)
	{
		weapon_number = (((weapon_number % 10) * 10) + (weapon_number / 10));
		reloaded = false;
		_reload();
	}
};

//Fire()
void UWeaponComponent::_fire(FVector launch_normal, FVector launch_location)
{
	if (_get_current_projectile())
	{
		if ((FPlatformTime::Seconds() - start_reload_time) > _get_current_projectile().GetDefaultObject()->reload_time && reloaded == true)
		{
		UE_LOG(LogTemp,Error,TEXT("ForwardVector Component of %s is "),*(launch_normal.ToString()));

			reloaded = false;
			GetWorld()->SpawnActor<ATankProjectile>(
						  _get_current_projectile(),
						  launch_location,
						  launch_normal.Rotation())
				->_launch();
		}
	}
};

//Reload
void UWeaponComponent::_reload()
{
	if ((FPlatformTime::Seconds() - start_reload_time) > _get_current_projectile().GetDefaultObject()->reload_time && reloaded == false)
	{
		start_reload_time = FPlatformTime::Seconds();
		reloaded = true;
		UE_LOG(LogTemp, Warning, TEXT("Reloading ~!"));
	}
	// UE_LOG(LogTemp, Warning, TEXT("Can't reload , Minus : %f , Reloaded is %i"), FPlatformTime::Seconds() - start_reload_time, reloaded);
};
