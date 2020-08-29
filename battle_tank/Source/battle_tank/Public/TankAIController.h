// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "battle_tank.h"
#include "AIController.h"
#include "CoreMinimal.h"
//last generate
#include "TankAIController.generated.h"

class ATank;

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

	UPROPERTY(EditAnywhere, Category = "AI_Trace")
	float AcceptanceRadius = 1000.f;
	//						#### TODO : Defact below all method
	//----------------------------------GET : SETUP-----------------------------------------
	virtual ATank *
	_get_controlled_tank() const;
	virtual ATank *_get_player_tank() const;

	//-----------------------------------------------ACTION-------------------------------------------------------

};
