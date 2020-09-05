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
class ATankPlayerController;

class UWeaponComponent;
class UAimingComponent;
class UForceNavMovementComponent;

class UTankHandlerComponent;
class UTankUIComponent;

// class UTankWidget;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//---------------------	Properties	------------------------
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankBarrel *barrel = nullptr;
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankTurrent *turrent = nullptr;
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankTrack *left_track = nullptr;
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankTrack *right_track = nullptr;
	//													#### TODO : Template for Component create

	UPROPERTY(BlueprintReadWrite, Category = "Component")
	UAimingComponent *aiming_component = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Component")
	UForceNavMovementComponent *move_component = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Component")
	UWeaponComponent *weapon_component = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Handler")
	UTankHandlerComponent *handler_component = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UTankUIComponent *UI_component = nullptr;

	//-----------------------------		GET		------------------------------
	FVector _get_launch_normal();

	//Get Current Launch location
	FVector _get_launch_location();

	//Get Current Projectile's Launch Speed
	float _get_launch_speed();

	//	UI
	// ATankHUD = nullptr;
	// UWidget widget = nullptr;

	void _show_aiming_box();
	void _reload_projectile();
	void _change_projectile();
	void _update_lock_buffer();
	void _show_lock_buffer();

	//-----------------		PUBLIC : SELF action	--------------------
	//_turning_to to aiming_direction
	virtual void _turning_to(FVector aiming_normal);
	//	GO	(Tick)
	virtual void _controller_tick(FVector aiming_normal);

	//--------------------------		PLAY		----------------------------------
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _set_weapon(uint8 number);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _exchange_weapon();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _fire();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _reload();
	UFUNCTION(BlueprintCallable, Category = Aiming)
	void _lock(bool if_lock);
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool turning = true;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UnPossessed();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//-----------------------------		SETUP		------------------------------
	//  	Set UP
	//STATIC MESH
	UFUNCTION(BlueprintCallable, Category = Mesh_Setup)
	virtual void _set_up(UTankBarrel *barrel_to_set, UTankTurrent *turrent_to_set,
						 UTankTrack *left_track_to_set, UTankTrack *right_track_to_set,
						 UAimingComponent *aiming_component_toset,
						 UWeaponComponent *weapon_component_toset,
						 UForceNavMovementComponent *move_component_toset,
						 UTankHandlerComponent *handler_component_toset,
						 UTankUIComponent *UI_component_toset);
};