// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	aiming_component = CreateDefaultSubobject<UAimingComponent>(FName(TEXT("aiming_component")));
	aiming_component->_set_owner(this);
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
//--------------------------------------------------------------------------------------------------------------------

//Set Barrel Reference
void ATank::_set_barrel_reference(UStaticMeshComponent *barrel_to_set)
{
	barrel = barrel_to_set;
};

void ATank::_aiming_at(FVector aiming_location) const
{
	aiming_component->_aiming_at(aiming_location);
}

void ATank::_draw_projectile_path() const
{
	aiming_component->_draw_projectile_path(launch_speed);
}