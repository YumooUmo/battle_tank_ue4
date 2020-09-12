// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "WeaponState.h"
//last generate
#include "WeaponComponent.generated.h"

// class AWeapon;
class ATankProjectile;
class ATankHUD;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//(weapon_number % 10) = current weapon
	//(weapon_number / 10) = last weapon used
	uint8 weapon_number = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//Weapons
	UPROPERTY(EditAnywhere, Category = "setup")
	TSubclassOf<ATankProjectile> weapons_token[10]{nullptr};

	//Ammo
	UPROPERTY(EditAnywhere, Category = "AmmoAmount")
	uint8 ammo_amount[10] = {0};

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	WeaponState weapon_state = WeaponState::out_of_ammo;

	UPROPERTY(EditAnywhere, Category = "setup")
	float launch_force = 1000000.f;

	FTimerHandle reload_timer;

	// - UI -
	ATankHUD *tank_hud;

public:
	// Sets default values for this component's properties
	UWeaponComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// - Ammo -
	//add ammo
	void _add_ammo(uint8 ammo_toset, uint8 number_toset);
	void _add_ammo(uint8 ammo_toset);
	//minus ammo
	void _minus_ammo(uint8 ammo_tominus);

	// - SET UP -
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _setup_weapon(TSubclassOf<ATankProjectile> weapon_toset,
					   uint8 num_toset);
	//Initialize Weapon
	UFUNCTION(BlueprintCallable, Category = "WeaponInitialize")
	void _initialize_weapon(uint8 ammo_0, TSubclassOf<ATankProjectile> weapon_0,
							uint8 ammo_1, TSubclassOf<ATankProjectile> weapon_1,
							uint8 ammo_2, TSubclassOf<ATankProjectile> weapon_2,
							uint8 ammo_3, TSubclassOf<ATankProjectile> weapon_3,
							uint8 ammo_4, TSubclassOf<ATankProjectile> weapon_4,
							uint8 ammo_5, TSubclassOf<ATankProjectile> weapon_5,
							uint8 ammo_6, TSubclassOf<ATankProjectile> weapon_6,
							uint8 ammo_7, TSubclassOf<ATankProjectile> weapon_7,
							uint8 ammo_8, TSubclassOf<ATankProjectile> weapon_8,
							uint8 ammo_9, TSubclassOf<ATankProjectile> weapon_9);
	//set HUD
	void _set_hud();

	// - GET -
	// Get Weapon
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual TSubclassOf<ATankProjectile> _get_current_weapon();
	// get current number
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	uint8 _get_current_number();
	// Ammo
	uint8 _get_ammo();
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	uint8 _get_ammo(uint8 num);
	// State
	UFUNCTION(BlueprintCallable, Category = "State")
	WeaponState _get_weapon_state();
	// Launch speed
	virtual float _get_launch_speed();
	// Reload TIme
	float _get_reload_time();
	//UI Image
	UTexture2D *_get_image();

	// - Bind Action -
	//SET weapon by number
	virtual bool _set_weapon(uint8 projectile_number);

	//Exchange projectile
	virtual bool _exchange_weapon();

	//Fire	- return bool for UI
	virtual void _fire(FVector launch_normal, FVector launch_location);

	//Reload - return float for UI - need timer handler set Ready
	virtual void _reload();

	virtual void _reload_ready();
};
