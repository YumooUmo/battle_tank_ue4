// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
	if (aiming_normal != owner->barrel->_get_launch_normal())
	{
		_move_turrent_barrel();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Elevation stop"));
	}
}

//-----------------------------------------------------------private-------------------------------------------------------------------------------
void UAimingComponent::_set_owner(ATank *owenr_tank)
{
	owner = owenr_tank;
};

//------------------------------------------------------public----------------------------------------------------------
//Normal aiming_vector : aiming_location - barrel launch point
void UAimingComponent::_aiming_at(FVector aiming_location)
{
	aiming_normal = (aiming_location - owner->barrel->_get_launch_location()).GetSafeNormal();
	//Elevate Barrel

	//Rotate Turrent
};

void UAimingComponent::_draw_projectile_path()
{
	//Initiallize Parameters to _predict path method()
	FPredictProjectilePathParams PredictParams{
		10.f,															  //CollisionRadius
		owner->barrel->_get_launch_location(),							  //start location
		owner->barrel->_get_launch_normal() * owner->_get_launch_speed(), //-----------------#### get owner->barrel aiming velocity : launch_velocity
		3.0f,															  //MaxSimTime
		ECollisionChannel::ECC_Visibility,
		nullptr};
	PredictParams.ActorsToIgnore.Add(owner);
	PredictParams.OverrideGravityZ = -5000.f;

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
	//------------------------------------Debug
	UE_LOG(LogTemp, Error, TEXT("Hit Result is : %s"), *(PredictResult.HitResult.Location.ToString()));
	UE_LOG(LogTemp, Error, TEXT("Last Trace Destnation is : %s"), *(PredictResult.LastTraceDestination.Location.ToString()));
	UE_LOG(LogTemp, Error, TEXT("Barrel location is : %s"), *(owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))).ToString()));
}

void UAimingComponent::_move_turrent_barrel()
{
	//Caculate rotation speed : by using ----   aiming_normal & launch velocity
	FRotator delta_rotator = aiming_normal.Rotation() - owner->barrel->_get_launch_normal().Rotation();

	//call _elevate_barrel   and   _rotate_turrent
	owner->barrel->_elevate_barrel(delta_rotator.Pitch);
};
