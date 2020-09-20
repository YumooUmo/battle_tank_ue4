// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//last
#include "ConstraintActor.generated.h"

UCLASS()
class BATTLE_TANK_API AConstraintActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConstraintActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPrimitiveComponent *parent = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void _set_bind_component(UPrimitiveComponent *parent_toset);
};
