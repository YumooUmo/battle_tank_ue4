// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//--------------------------------PUBLIC : GET
	//GET Launch speed
	virtual float _get_launch_speed();
	//GET Projectile
	virtual TSubclassOf<ATankProjectile> _get_current_projectile();

	//--------------------------------		PUBLIC : PLAY action
	//SET weapon number
	virtual void _exchange_weapon(int projectile_number);

	//SET exchange projectile
	virtual void _exchange_weapon();

	//Fire
	virtual void _fire(FVector launch_normal,FVector launch_location);

	//Reload
	virtual void _reload();

private:
	//SET projectile_1
	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<ATankProjectile> tank_projectile_0 = nullptr;

	//SET projectile_2
	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<ATankProjectile> tank_projectile_1 = nullptr;

	//Single digit: 0-9 (project_tile % 10) represents the projectile USED RIGHT NOW;
	//Ten digit: 0-9 represents projectile LAST USED.
	int weapon_number = 0;

	//   Reload Property ---- start with RELOADING
	bool reloaded = true;
	float start_reload_time = 0.f;
};
