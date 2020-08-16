// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	aiming_component = CreateDefaultSubobject<UAimingComponent>(FName(TEXT("aiming_component")));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::_aiming_at(FVector aiming_vector) const
{
	aiming_component->_aiming_at(aiming_vector);
}

void ATank::_set_barrel_reference(UStaticMeshComponent *barrel_to_set){
	aiming_component->_set_barrel_reference(barrel_to_set);
}