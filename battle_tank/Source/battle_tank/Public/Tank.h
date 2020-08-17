// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UAimingComponent;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UTankBarrel *barrel = nullptr;
	UAimingComponent *aiming_component = nullptr;

	virtual float _get_launch_speed() const;
	virtual void _launch() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float launch_speed = 100000.f;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//set barrel
	UFUNCTION(BlueprintCallable, Category = setup)
	virtual void _set_barrel_reference(UTankBarrel *barrel_to_set);
};
