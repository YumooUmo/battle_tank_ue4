// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttachAnchor.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
//generate last
#include "SpawnAnchor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API USpawnAnchor : public UAttachAnchor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawnAnchor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//Spawn 
	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	AActor *_spawn_actor(TSubclassOf<AActor> SpawnClass, USceneComponent *attach_component);

	//Spawn Weld
	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	AActor *_spawn_weld_actor(TSubclassOf<AActor> SpawnClass, USceneComponent *attach_component);
};