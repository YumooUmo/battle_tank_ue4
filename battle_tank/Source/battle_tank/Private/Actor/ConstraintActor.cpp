// Fill out your copyright notice in the Description page of Project Settings.

#include "ConstraintActor.h"
//first

// Sets default values
AConstraintActor::AConstraintActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConstraintActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AConstraintActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AConstraintActor::_set_bind_component(UPrimitiveComponent *parent_toset)
{
	parent = parent_toset;
};
//
