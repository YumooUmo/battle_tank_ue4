// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectile.h"
//FIRST include
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATankProjectile::ATankProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SET move_component
	projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("projectile_movement_component")));
	projectile_movement_component->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//------------------------------------------------------public-----------------------------------------------------------------
//Launch
void ATankProjectile::_launch()
{
	projectile_movement_component->SetVelocityInLocalSpace(FVector::ForwardVector * launch_speed);
	projectile_movement_component->Activate();
};