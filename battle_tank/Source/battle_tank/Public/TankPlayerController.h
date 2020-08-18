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
	float aiming_range = 500000.f;
	ATank *tank_controlled = nullptr;

	//-------------------------------TICK--------------------------------
	void _aiming() const;	

	//-------------------------------GET----------------------------------
	virtual ATank *_get_controlled_tank() const;
	bool _get_screen_aiming_location(FVector &location_screen_aiming) const;

	//-------------------------------PLAY---------------------------------
	//Draw Projectile Path
	void _draw_projectile_path();											//---------------####   Projectile Path

	//SET weapon number : Change Weapon
	UFUNCTION(BlueprintCallable, Category = play)
	virtual void _set_projectile_number(int projectile_number);

	//SET exchange projectile : Exchange Weapon with last time used
	UFUNCTION(BlueprintCallable, Category = play)
	virtual void _exchange_projectile();

	//Fire
	UFUNCTION(BlueprintCallable, Category = play)
	virtual void _fire();

	//Reload
	UFUNCTION(BlueprintCallable, Category = play)
	virtual void _reload();
};
