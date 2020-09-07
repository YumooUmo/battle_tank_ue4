// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "WeaponState.h"
//last generate
#include "WeaponComponent.generated.h"

// class AWeapon;
class ATankProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	//   Reload Property ---- start with reloaded
	UFUNCTION(BlueprintCallable, Category = "State")
	WeaponState _get_weapon_state();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool reloaded = true;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//		SET UP
	UFUNCTION(BlueprintCallable, Category = "State")
	void _set_projectile(TSubclassOf<ATankProjectile> projectile_Subclass_0,
						 TSubclassOf<ATankProjectile> projectile_Subclass_1);

	//		GET

	//GET Launch speed
	virtual float _get_launch_speed();
	//GET Projectile
	virtual TSubclassOf<ATankProjectile> _get_current_projectile();
	//GET Reload TIme
	float _get_reload_time();
	//Get Image
	UTexture2D *_get_image();

	//		PLAY action
	//SET weapon number
	virtual bool _exchange_weapon(uint8 projectile_number);

	//Exchange projectile
	virtual bool _exchange_weapon();

	//Fire	- return bool for UI
	virtual bool _fire(FVector launch_normal, FVector launch_location);

	//Reload - return float for UI - need timer handler set Ready
	virtual bool _reload();

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
	float end_reload_time = 0.f;
};
