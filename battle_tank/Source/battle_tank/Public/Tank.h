// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//last generate
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurrent;
class UTankTrack;

class ATankProjectile;

class UWeaponComponent;
class UAimingComponent;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//---------------------	Properties	------------------------
	UTankBarrel *barrel = nullptr;
	UTankTurrent *turrent = nullptr;
	UTankTrack *left_track = nullptr;
	UTankTrack *right_track = nullptr;
	//																#### TODO : Template for Component create
	UAimingComponent *aiming_component = nullptr;

	// UPROPERTY(EditAnywhere, Category = setup)
	UWeaponComponent *weapon_component = nullptr;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void set_weapon_component(UWeaponComponent *weapon_component);
	//-----------------		PUBLIC : SELF action	--------------------
	//_aiming_at to aiming_direction
	virtual void _aiming_at(FVector aiming_normal);
	//	GO	(Tick)
	virtual void _controller_do(float DeltaTime, FVector aiming_normal);

	//------------------	PUBLIC : GET	----------------------
	virtual FVector _get_launch_normal();
	virtual FVector _get_launch_location();
	virtual float _get_launch_speed();

	//--------------------------		PLAY		----------------------------------
	UFUNCTION(BlueprintCallable,Category = Weapon)
	void _set_weapon(int number);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _exchange_weapon();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _fire();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _reload();
	UFUNCTION(BlueprintCallable, Category = Aiming)
	void _draw();
	UFUNCTION(BlueprintCallable, Category = Aiming)
	void _stop_draw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//-----------------------------		SETUP		------------------------------
	//  	Set UP
	UFUNCTION(BlueprintCallable, Category = setup)
	virtual void _set_up(UTankBarrel *barrel_to_set, UTankTurrent *turrent_to_set, UTankTrack *left_track_to_set, UTankTrack *right_track_to_set);
};
