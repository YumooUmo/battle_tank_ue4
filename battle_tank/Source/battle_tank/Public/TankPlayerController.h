// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "battle_tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//last generate
#include "TankPlayerController.generated.h"

class ATank;
class UAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	//Begin play initialize
	ATank *tank_controlled = nullptr;
	UAimingComponent *aiming_component;

	// -Aiming -
	FVector aiming_normal{0.f, 0.f, 0.f};

	UPROPERTY(VisibleAnywhere)
	float aiming_range = 100000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_x = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_y = 0.35;

public:
	virtual void SetPawn(APawn *InPawn) override;
	virtual void PossessBack();

	// - aiming -
	void _get_aiming_normal();

	// - Paus Menu -
	void _open_pause_menu();
};