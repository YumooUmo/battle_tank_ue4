// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//last generate
#include "Tank.generated.h"

class UWeaponComponent;
class UAimingComponent;
class UForceNavMovementComponent;

// class UTankWidget;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//---------------------	Properties	------------------------
	//	#### TODO : Template for Component create
	UPROPERTY(BlueprintReadWrite, Category = "Component")
	UAimingComponent *aiming_component;

	UPROPERTY(BlueprintReadWrite, Category = "Component")
	UForceNavMovementComponent *move_component;

	UPROPERTY(BlueprintReadWrite, Category = "Component")
	UWeaponComponent *weapon_component;

public:
	// Sets default values for this pawn's properties
	ATank();

	// - SETUP -
	// setup by BP -
	UFUNCTION(BlueprintCallable, Category = Tank_Setup)
	virtual void _setup(UAimingComponent *aiming_component_toset,
						UWeaponComponent *weapon_component_toset,
						UForceNavMovementComponent *move_component_toset);

	// - GET -

	// - Bind Action -
	// - Aiming -
	virtual void _turning_to(FVector aiming_normal);
	UFUNCTION(BlueprintCallable, Category = Aiming)
	void _lock(bool if_lock);
	// - Weapon -
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _set_weapon(uint8 number);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _exchange_weapon();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _fire();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _reload();
	// - Move -
	UFUNCTION(BlueprintCallable, Category = Move)
	void _move_forward(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Move)
	void _move_backward(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Move)
	void _move_left(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Move)
	void _move_right(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Move)
	void _burst(bool if_burst);
	UFUNCTION(BlueprintCallable, Category = Move)
	void _move_stick(float LT_X, float LT_Y);

	// - AI -
	void _aiming_at(FVector location);
};