// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "battle_tank.h"
#include "AIController.h"
#include "CoreMinimal.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	ATank *tank_controlled = nullptr;
	ATank *tank_of_player = nullptr;

	virtual ATank *_get_controlled_tank() const;

	virtual ATank *_get_player_tank() const;

	void _aiming() const;
};
