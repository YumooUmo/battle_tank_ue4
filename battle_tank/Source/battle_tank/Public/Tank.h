// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//last generate
#include "Tank.generated.h"

class UStraightWeaponComponent;
class UTrackForceAdapterComponent;
class UChildActorComponent;
class UBodyMesh;

DECLARE_DELEGATE(FTankDelegate)
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

	UPROPERTY(EditAnywhere, Category = "Health")
	int32 Health = 100;
	int32 CurrentHealth = Health;

	UPROPERTY(EditAnywhere, Category = "ChildActor")
	UChildActorComponent *turrent;

	// - Actor Component -
	UPROPERTY(BlueprintReadWrite, Category = "ActorComponent")
	UTrackForceAdapterComponent *move_component;

	UPROPERTY(BlueprintReadWrite, Category = "ActorComponent")
	UStraightWeaponComponent *weapon_component;

public:
	// Sets default values for this pawn's properties
	ATank();

	FTankDelegate OnDeath;

	virtual float TakeDamage(
		float Damage,
		struct FDamageEvent const &DamageEvent,
		AController *EventInstigator,
		AActor *DamageCauser) override;

};