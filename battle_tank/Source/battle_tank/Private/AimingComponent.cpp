// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
//FIRST include
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurrent.h"

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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//-----------------------------------------------------------private-------------------------------------------------------------------------------
void UAimingComponent::_set_owner(ATank *owenr_tank)
{
	owner = owenr_tank;
};

//------------------------------------------------------public----------------------------------------------------------
//															------------Aiming by Normal
void UAimingComponent::_aiming_by_viewport(FVector aiming_normal)
{
	//Elevate Barrel
	//Rotate Turrent
		owner->_aiming_at(aiming_normal);
};
//															------------Aiming by Normal

//								----------------------------------Aiming by Location
void UAimingComponent::_aiming_by_location(FVector aiming_location)
{
	//Elevate Barrel
	//Rotate Turrent
		owner->_aiming_at((aiming_location - owner->barrel->_get_launch_location()).GetSafeNormal());
};
//								----------------------------------Aiming by Location

//--------------------------------------------------Move_and_Draw-----------------------------------------------------------
void UAimingComponent::_draw_projectile_path()
{
	//Initiallize Parameters to _predict path method()
	FPredictProjectilePathParams PredictParams{
		10.f,															  //CollisionRadius
		owner->barrel->_get_launch_location(),							  //start location
		owner->barrel->_get_launch_normal() * owner->_get_launch_speed(), //----------------- get owner->barrel aiming velocity : launch_velocity
		3.0f,															  //MaxSimTime
		ECollisionChannel::ECC_Visibility,
		owner};
	// PredictParams.ActorsToIgnore.Add(owner);
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
			owner->barrel->_get_launch_location(), //start location
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
			owner->barrel->_get_launch_location(), //start location
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
