// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
//FIRST include
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	owner_tank = Cast<ATank>(GetOwner());
	player_controller = Cast<ATankPlayerController>(owner_tank->GetController());
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(GetWorld()->DeltaTimeSeconds, TickType, ThisTickFunction);
	// ...
}

//-----------------------------------		private		---------------------------------

//-----------------------------------		public		---------------------------------

//-----------------------------------		Lock Action		---------------------------------
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
	player_controller->_update_lock_buffer(FMath::GetRangePct(0.f, max_buffer, lock_buffer), aiming_state);
};

//CALL
void UAimingComponent::_lock(bool flag)
{
	if (!player_controller)
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
			player_controller->_do_lock_buffer();
		}
		//Draw_Path : Released
		else
		{
			aiming_state = AimingState::usable;
		}
	}
};

//Draw : Projectile path
void UAimingComponent::_draw_projectile_path()
{
	if (owner_tank == nullptr)
	{
		return;
	}
	//Initiallize Parameters to _predict path method()
	FVector launch_velocity = (owner_tank->_get_launch_normal()) * (owner_tank->_get_launch_speed());
	FVector launch_location = owner_tank->_get_launch_location();

	FPredictProjectilePathParams PredictParams{
		10.f,			 //CollisionRadius
		launch_location, //start location
		launch_velocity, //----------------- get owner->barrel aiming velocity : launch_velocity
		3.0f,			 //MaxSimTime
		ECollisionChannel::ECC_Visibility,
		nullptr}; //													####	TODO : Debug
	PredictParams.ActorsToIgnore.Add(owner_tank);
	// PredictParams.OverrideGravityZ = -5000.f;

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
	// //------------------------------------Debug
	// UE_LOG(LogTemp, Error, TEXT("Hit Result is : %s"), *(PredictResult.HitResult.Location.ToString()));
	// UE_LOG(LogTemp, Error, TEXT("Last Trace Destnation is : %s"), *(PredictResult.LastTraceDestination.Location.ToString()));
	// UE_LOG(LogTemp, Error, TEXT("Barrel location is : %s"), *(owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))).ToString()));
}
