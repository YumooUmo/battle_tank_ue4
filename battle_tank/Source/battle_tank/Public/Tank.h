// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AimingComponent.h"
#include "Tank.generated.h"

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void _aiming_at(FVector aiming_vector) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAimingComponent *aiming_component = nullptr;

private:
	UFUNCTION(BlueprintCallable, Category = setup)
	virtual void _set_barrel_reference(UStaticMeshComponent *barrel_to_set);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
