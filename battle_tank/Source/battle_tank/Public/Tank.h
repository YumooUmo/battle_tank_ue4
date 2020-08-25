// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//last generate
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurrent;
class UAimingComponent;
class UTankTrack;

class ATankProjectile;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//--------------------------------public : Properties
	UTankBarrel *barrel = nullptr;
	UTankTurrent *turrent = nullptr;
	UTankTrack *left_track = nullptr;
	UTankTrack *right_track = nullptr;


	UAimingComponent *aiming_component = nullptr;
	
	//#### Single digit: 0-9 (project_tile % 10) represents the projectile USED RIGHT NOW; 
	//#### Ten digit: 0-9 represents projectile LAST USED.
	int projectile_number = 0;		

	//--------------------------------public : SELF action
	//GET Launch speed
	virtual float _get_launch_speed();

	//_aiming_at to aiming_direction
	virtual void _aiming_at(FVector aiming_normal);
	
	//--------------------------------public : PLAY action
	//SET weapon number
	virtual void _set_projectile_number(int projectile_number);

	//SET exchange projectile
	virtual void _exchange_projectile();

	//Fire
	virtual void _fire();

	//Reload
	virtual void _reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//---------------------------------------SETUP--------------------------------------------------------
	// ####  Reload Property ---- start with RELOADING  ####
	bool reloaded = true ; 
	float start_reload_time = 0.f;

	//  ####	Set UP
	UFUNCTION(BlueprintCallable, Category = setup)
	virtual void _set_up(UTankBarrel *barrel_to_set,UTankTurrent *turrent_to_set,UTankTrack *left_track_to_set,UTankTrack *right_track_to_set);

	//	####	Add Projectile Type
	//Current Projectile
	virtual TSubclassOf<ATankProjectile> _get_current_projectile();

	//SET projectile_1
	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<ATankProjectile> tank_projectile_0 = nullptr;

	//SET projectile_2
	UPROPERTY(EditAnywhere, Category = setup)
	TSubclassOf<ATankProjectile> tank_projectile_1 = nullptr;
};
