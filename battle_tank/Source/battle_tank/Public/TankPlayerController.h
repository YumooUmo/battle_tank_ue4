// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "battle_tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

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

	virtual ATank *_get_controlled_tank() const;
	void _aiming() const;
	bool _get_screen_aiming_location(FVector &location_screen_aiming) const;

	void _draw_projectile_path();											//---------------####   Projectile Path

	UPROPERTY(VisibleAnywhere)
	float aiming_range = 500000.f;

	ATank *tank_controlled = nullptr;
	
};
