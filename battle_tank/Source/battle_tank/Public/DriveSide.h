// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//generate last
#include "DriveSide.generated.h"

class UPhysicsConstraintComponent;
class UTankTrack;
class AWheel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API ADriveSide : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADriveSide();

protected:
	//Called after the instance of Actor is Construct, and before BeginPlay.
	virtual void OnConstruction(const FTransform &Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// - Set Up -
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	UPhysicsConstraintComponent *track_constraint;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	UTankTrack *track;
	//Wheels array
	TArray<AWheel *> wheels;
	TArray<UChildActorComponent *> wheels_anchor;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "SetupDriveSide")
	bool bConstraintJointComponentSimulatingPhysics = true;

	// - Move -
	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float _max_force = 4000000.f;

	// - Brake -
	bool bBrake = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*  - Set Up - BP-  */
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _initialize(UTankTrack *track_toset, UPhysicsConstraintComponent *constraint_toset, TArray<UChildActorComponent *> wheels_toset);
	
	/*  - Set Up - BeginPlay-  */
	//bind constraint
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _bind_constraint();

	// /*  - detach -  */
	// UFUNCTION(BlueprintCallable, Category = "detach")
	// void _detach();

	/*  - Move Apply Force -  */

	//apply_force
	void _apply_force(float throttle);

	//Brake
	UFUNCTION(BlueprintCallable, Category = "Brake")
	void _brake(bool if_brake);
};
