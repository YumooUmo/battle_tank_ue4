// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AimingComponent.generated.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UStaticMeshComponent *barrel = nullptr;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void _aiming_at(FVector aiming_vector);

	virtual void _set_barrel_reference(UStaticMeshComponent *barrel_toset);
};
