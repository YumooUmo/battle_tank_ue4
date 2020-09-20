// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAnchor.h"
//include first
#include "DriveSide.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnAnchor::USpawnAnchor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USpawnAnchor::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

// Called every frame
void USpawnAnchor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//Spawn
AActor *USpawnAnchor::_spawn_actor(TSubclassOf<AActor> SpawnClass, USceneComponent *attach_component)
{
	if (GetNumChildrenComponents() > 0 || !SpawnClass)
		return nullptr;

	AActor *NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!NewActor)
		return nullptr;
	NewActor->AttachToComponent(attach_component, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
	// NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	/*  BUG FIXED */
	return NewActor;
};
//Spawn Weld
AActor *USpawnAnchor::_spawn_weld_actor(TSubclassOf<AActor> SpawnClass, USceneComponent *attach_component)
{
	if (GetNumChildrenComponents() > 0 || !SpawnClass)
		return nullptr;
	AActor *NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (!NewActor)
		return nullptr;
	NewActor->AttachToComponent(attach_component, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
	// NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	/*  BUG FIXED */
	return NewActor;
};