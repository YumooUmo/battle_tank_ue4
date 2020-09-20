// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
//FIRST include
#include "Config.h"
#include "TankBarrel.h"
#include "TankHUD.h"
#include "TankTurrent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : AimingComponent C++ Construct "));
}
// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : AimingComponent C++ BeginPlay "));
	// ...
}
// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(GetWorld()->DeltaTimeSeconds, TickType, ThisTickFunction);
	// ...
}

// ## PUBLIC ##

// - SetUp -
void UAimingComponent::_setup(UTankTurrent *turrent_toset, UTankBarrel *barrel_toset)
{
	if (!turrent)
	{
		turrent = turrent_toset;
	}
	if (!barrel)
	{
		barrel = barrel_toset;
	}
};
// Set HUD -
void UAimingComponent::_set_hud()
{
	APawn *temp = Cast<APawn>(GetOwner());
	if (temp && temp->IsPlayerControlled())
	{
		AHUD *hud_toset = Cast<APlayerController>(temp->GetController())
							  ->GetHUD();
		tank_hud = Cast<ATankHUD>(hud_toset);
	}
};
void UAimingComponent::_setup_widget()
{
	if (tank_hud)
		tank_hud->_setup_tank_widget();
};
void UAimingComponent::_remove_widget()
{
	tank_hud->_remove_tank_widget();
};
void UAimingComponent::_setup_ui()
{
	_set_hud();
	_setup_widget();
};

// - Break -
void UAimingComponent::_break_barrel()
{
	if (barrel)
	{
		delete barrel;
		barrel = nullptr;
	}
};
void UAimingComponent::_break()
{
	if (barrel)
	{
		delete barrel;
		barrel = nullptr;
	}
	if (turrent)
	{
		delete turrent;
		turrent = nullptr;
	}
};
// - detach -
void UAimingComponent::_detach_weapon()
{
	if (!turrent)
	{
		return;
	}
	// barrel->SetSimulatePhysics(true);
	turrent->SetSimulatePhysics(true);
	// turrent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	turrent = nullptr;
	barrel = nullptr;
};

// - GET -
// launch vector
FVector UAimingComponent::_get_launch_normal()
{
	if (!barrel)
	{
		return GetOwner()->GetActorForwardVector();
	}
	return barrel->GetForwardVector();
};
// launch location
FVector UAimingComponent::_get_launch_location()
{
	if (!barrel)
	{
		return GetOwner()->GetActorLocation();
	}
	return barrel->_get_launch_location();
}
// is_barrel
bool UAimingComponent::_is_barrel()
{
	return barrel ? true : false;
};
// is_turrent
bool UAimingComponent::_is_turrent()
{
	return turrent ? true : false;
};
//is aiming on
bool UAimingComponent::_is_aiming_on()
{
	return ai_aiming;
};

// - Turing -
// turning action
void UAimingComponent::_turning_to(FVector aiming_normal)
{
	if (!barrel || !turrent)
	{
		return;
	}
	FVector launch_normal = _get_launch_normal();

	// UE_LOG(LogTemp, Warning, TEXT("YES ! ~~~!  %f"), yaw);

	if (launch_normal.Equals(aiming_normal, 0.01f))
	{
		if (is_moving)
		{
			if (tank_hud)
				tank_hud->_change_crosshair_color(true);
			is_moving = false;
		}
		return;
	}

	FRotator launch_rotation = launch_normal.Rotation();
	float pitch = aiming_normal.Rotation().Pitch - launch_rotation.Pitch;
	float yaw = aiming_normal.Rotation().Yaw - launch_rotation.Yaw;

	//call _elevate_barrel
	barrel->_elevate_barrel(pitch);
	//call   _rotate_turrent
	turrent->_rotate_turrent(yaw);

	if (!is_moving)
	{
		if (tank_hud)
			tank_hud->_change_crosshair_color(false);
		is_moving = true;
	}

	/*  #### BUG fixed : Value tremble around destnation. 
    *   Float value is not accurate.
    *   Method is : Lower accurency.
    */
};
// ai aiming
void UAimingComponent::_ai_turning(FVector aiming_location)
{
	FVector ai_aiming_vector = aiming_location - _get_launch_location();
	ai_aiming_vector.Normalize();
	_turning_to(ai_aiming_vector);
	if (ai_aiming_vector.Equals(_get_launch_normal(), ai_aiming_tolerance))
	{
		if (!ai_aiming)
		{
			ai_aiming = true;
		}
		return;
	}
	else
	{
		if (ai_aiming)
		{
			ai_aiming = false;
		}
	}
};
