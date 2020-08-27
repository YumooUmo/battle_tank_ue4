// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "battle_tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//last generate
#include "TankPlayerController.generated.h"

class ATank;

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
	//-------------------------------Property-------------------------
	UPROPERTY(VisibleAnywhere)
	float aiming_range = 100000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_x = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float crosshair_y = 0.35;

	FVector aiming_normal{0};

	ATank *tank_controlled = nullptr;

	//-------------------------------TICK--------------------------------
	void _get_aiming_normal();

	//-------By Location
	// void _aiming() const;

	//-------------------------------GET----------------------------------
	virtual ATank *_get_controlled_tank() const;

	// bool _get_screen_aiming_location(FVector &location_screen_aiming) const;

	//-------------------------------PLAY---------------------------------
	//Draw Projectile Path
};
