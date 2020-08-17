// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

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
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
void UAimingComponent::_set_owner(ATank *owenr_tank){
	owner = owenr_tank;
};


//Normal aiming_vector : aiming_location - barrel launch point
void UAimingComponent::_aiming_at(FVector aiming_location)
{
	aiming_normal = (aiming_location - owner->barrel->GetSocketLocation(FName(TEXT("launch_socket")))).GetSafeNormal();

	//--------------------------------------------------------------------------------Debug
	UE_LOG(LogTemp, Warning, TEXT("Aiming location is : %s"), *(aiming_location.ToString()));
};

void UAimingComponent::_draw_projectile_path(float launch_speed)
{
	//Initiallize Parameters to _predict path method()
	FPredictProjectilePathParams PredictParams{
		10.f,													 //CollisionRadius
		owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))), //start location
		aiming_normal * launch_speed,							 //-----------------#### get owner->barrel aiming velocity : launch_velocity
		3.0f,													 //MaxSimTime
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
			owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))), //start location
			PredictResult.HitResult.Location,
			FColor::Blue,
			false,
			0.0f,
			0.0f,
			100.0f);
	}else{
		//-----####有效射程外 out of MaxSimTime
		DrawDebugLine(
			GetWorld(),
			owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))), //start location
			PredictResult.LastTraceDestination.Location,
			FColor::Blue,
			false,
			0.0f,
			0.0f,
			100.0f);
	}

	UE_LOG(LogTemp, Error, TEXT("Hit Result is : %s"), *(PredictResult.HitResult.Location.ToString()));
	UE_LOG(LogTemp, Error, TEXT("Last Trace Destnation is : %s"), *(PredictResult.LastTraceDestination.Location.ToString()));
	UE_LOG(LogTemp, Error, TEXT("Barrel location is : %s"), *(owner->barrel->GetSocketLocation(FName(TEXT("launch_socket"))).ToString()));
}

void UAimingComponent::_launch()
{
}
