// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
//FIRST include
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

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
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(GetWorld()->DeltaTimeSeconds, TickType, ThisTickFunction);
	// ...
}

//-----------------------------------		private		---------------------------------

//-----------------------------------		public		---------------------------------

//-----------------------------------		Draw		---------------------------------
void UAimingComponent::_lock_projectile_path(FVector launch_velocity, FVector launch_location, AActor *ignore)
{
	//Initiallize Parameters to _predict path method()

	FPredictProjectilePathParams PredictParams{
		10.f,			 //CollisionRadius
		launch_location, //start location
		launch_velocity, //----------------- get owner->barrel aiming velocity : launch_velocity
		3.0f,			 //MaxSimTime
		ECollisionChannel::ECC_Visibility,
		nullptr}; //													####	TODO : Debug
	PredictParams.ActorsToIgnore.Add(ignore);
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

bool UAimingComponent::_should_lock()
{
	//Draw_Path : Pressed
	if (aiming_state == AimingState::locking)
	{
		if (draw_buffer <= 0.f)
		{
			draw_buffer = -overheat_lag;
			aiming_state = AimingState::overheat;
			return false;
		}
		else
		{
			draw_buffer -= GetWorld()->DeltaTimeSeconds;
			return true;
		}
	}
	//Draw_Path : Not Pressed
	else
	{
		if (draw_buffer < max_buffer)
		{
			draw_buffer += GetWorld()->DeltaTimeSeconds * cool_rate;
			if (aiming_state == AimingState::overheat && draw_buffer > recover_value)
			{
				aiming_state = AimingState::usable;
			}
			if (draw_buffer > max_buffer)
			{
				draw_buffer = max_buffer;
			}
		}
		return false;
	}
};

// 
float UAimingComponent::_lock(bool flag)
{
	//Draw_Path : Pressed
	if (aiming_state != AimingState::overheat)
	{
		if (flag)
		{
			aiming_state = AimingState::locking;
		}
		//Draw_Path : Released
		else
		{
			aiming_state = AimingState::usable;
		}
	}
	return draw_buffer;
};
