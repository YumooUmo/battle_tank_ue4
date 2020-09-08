// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "WeaponState.h"
//last generate
#include "WeaponComponent.generated.h"

// class AWeapon;
class ATankProjectile;
class ATankPlayerController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//SET projectile_1
	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<ATankProjectile> tank_projectile_0 = nullptr;

	//SET projectile_2
	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<ATankProjectile> tank_projectile_1 = nullptr;

	//Single digit: 0-9 (project_tile % 10) represents the projectile USED RIGHT NOW;
	//Ten digit: 0-9 represents projectile LAST USED.
	uint8 weapon_number = 0;

	ATankPlayerController *player_controller;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	WeaponState weapon_state = WeaponState::empty;

	FTimerHandle reload_timer;

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// - SET UP -
	UFUNCTION(BlueprintCallable, Category = "State")
	void _set_projectile(TSubclassOf<ATankProjectile> projectile_Subclass_0,
						 TSubclassOf<ATankProjectile> projectile_Subclass_1);

	// - GET -
	UFUNCTION(BlueprintCallable, Category = "State")
	WeaponState _get_weapon_state();

	//Get Launch speed
	virtual float _get_launch_speed();
	//Get Projectile
	virtual TSubclassOf<ATankProjectile> _get_current_projectile();
	//Get Reload TIme
	float _get_reload_time();
	//Get Image
	UTexture2D *_get_image();

	// - Bind Action -
	//SET weapon by number
	virtual void _set_weapon(uint8 projectile_number);

	//Exchange projectile
	virtual void _exchange_weapon();

	//Fire	- return bool for UI
	virtual void _fire(FVector launch_normal, FVector launch_location);

	//Reload - return float for UI - need timer handler set Ready
	virtual void _reload();

	virtual void _reload_ready();
};
