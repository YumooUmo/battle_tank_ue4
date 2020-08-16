// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"

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

//set barrel reference
void UAimingComponent::_set_barrel_reference(UStaticMeshComponent *barrel_to_set)
{
	barrel = barrel_to_set;
};

//aiming at
void UAimingComponent::_aiming_at(FVector aiming_vector)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Is Aiming At : %s"), *(GetOwner()->GetName()), *(aiming_vector.ToString()));
};
