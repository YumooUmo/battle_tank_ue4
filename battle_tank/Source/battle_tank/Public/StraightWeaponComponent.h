// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "AimingComponent.h"
#include "AimingState.h"
#include "CoreMinimal.h"
#include "WeaponState.h"
//last generate

#include "StraightWeaponComponent.generated.h"

// class AWeapon;
class ATankProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UStraightWeaponComponent : public UAimingComponent
{
	GENERATED_BODY()

private:
	//(projectile_number % 10) = current weapon
	//(projectile_number / 10) = last weapon used
	uint8 projectile_number = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//Weapons
	UPROPERTY(EditAnywhere, Category = "setup")
	TSubclassOf<ATankProjectile> projectile_token[10]{nullptr};
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	WeaponState weapon_state = WeaponState::out_of_ammo;
	UPROPERTY(EditAnywhere, Category = "setup")
	float launch_force = 1000000.f;
	//Ammo
	UPROPERTY(EditAnywhere, Category = "AmmoAmount")
	uint8 ammo_amount[10] = {0};

	// - Lock -
	//property
	UPROPERTY(BlueprintReadOnly, Category = "Lock")
	AimingState aiming_state = AimingState::usable;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float max_buffer = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float lock_buffer = max_buffer;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float cool_rate = 0.8f;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float recover_value = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	float overheat_lag = 2.f;

	FTimerHandle lock_timer;
	FTimerHandle reload_timer;

public:
	// Sets default values for this component's properties
	UStraightWeaponComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// - Ammo -
	//add ammo
	void _add_ammo(uint8 number_toset, uint8 ammo_toset);
	void _add_ammo(uint8 ammo_toset);
	//minus ammo
	void _minus_ammo(uint8 ammo_tominus);

	// - SET UP -
	UFUNCTION(BlueprintCallable, Category = "SetupProjectile")
	void _setup_projectile(uint8 num_toset,
						   TSubclassOf<ATankProjectile> projectile_toset,
						   uint8 ammo_toset);

	UFUNCTION(BlueprintCallable, Category = "SetupProjectile")
	//add projectile
	void _add_projectile(TSubclassOf<ATankProjectile> projectile_toset,
						 uint8 ammo_toset);

	// - GET -
	// Ammo
	uint8 _get_ammo();
	uint8 _get_ammo(uint8 num);
	// Get Weapon
	uint8 _get_current_number();	
	TSubclassOf<ATankProjectile> _get_current_projectile();
	// Launch speed
	float _get_launch_speed();
	// Reload TIme
	float _get_reload_time();
	//UI Image
	UTexture2D *_get_image();
	// State
	WeaponState _get_weapon_state();

	// - LOCK -
	virtual void _should_lock();
	
	//CALL : Draw Projectile Path
	void _draw_projectile_path();

	// - Bind Action -
	//SET weapon by number
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual bool _set_projectile(uint8 projectile_number);

	//Exchange projectile
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual bool _exchange_projectile();

	//Fire	- return bool for UI
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void _fire();

	//Reload - return float for UI - need timer handler set Ready
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void _reload();
	virtual void _reload_ready();

	//Lock - draw projectile path
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void _lock(bool flag);
};
