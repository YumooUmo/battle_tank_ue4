// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
//FIRST include
#include "Config.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
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
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : AimingComponent %s C++ Construct "), *name);
}
// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : AimingComponent %s C++ BeginPlay "), *name);
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
	if (ensure(Cast<ATankHUD>(
			Cast<APlayerController>(
				Cast<APawn>(GetOwner())
					->GetController())
				->GetHUD())))
		tank_hud = Cast<ATankHUD>(
			Cast<APlayerController>(
				Cast<APawn>(GetOwner())
					->GetController())
				->GetHUD());
};
void UAimingComponent::_set_widget()
{
	tank_hud->_setup_tank_widget();
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

// - Turing -
// self action
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

// - Lock Action -
// - call in
void UAimingComponent::_lock(bool flag)
{
	if (!(launch_speed > 0))
	{
		return;
	}
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
												   &UAimingComponent::_should_lock,
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
};
// lock buffer counter
void UAimingComponent::_should_lock()
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
			UAimingComponent::_draw_projectile_path();
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
/*OUT Dpendence - launch speed*/
void UAimingComponent::_update_launch_speed(float launch_speed_toset)
{
	launch_speed = launch_speed_toset;
};

// - Draw UI -
void UAimingComponent::_draw_projectile_path()
{
	//Initiallize Parameters to _predict path method()
	FVector launch_velocity = _get_launch_normal() * launch_speed;
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
		DrawDebugLine(
			GetWorld(),
			launch_location, //start location
			PredictResult.HitResult.Location,
			FColor::Blue,
			false,
			0.0f,
			0.0f,
			100.0f);
	}
	else
	{
		//-----####有效射程外 out of MaxSimTime
		//---------------------------------------------------------Debug
		DrawDebugLine(
			GetWorld(),
			launch_location, //start location
			PredictResult.LastTraceDestination.Location,
			FColor::Blue,
			false,
			0.0f,
			0.0f,
			100.0f);
	}
}
