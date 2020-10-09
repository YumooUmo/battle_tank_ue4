// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//generate
#include "Wheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API AWheel : public AActor
{
	GENERATED_BODY()

private:
	FVector force{0};

protected:
	// Called when the game starts or when spawned
	virtual void
	BeginPlay() override;

	//Called after the instance of Actor is Construct, and before BeginPlay.
	virtual void OnConstruction(const FTransform &Transform) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	USphereComponent *wheel = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	USphereComponent *axle = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	UPhysicsConstraintComponent *wheel_constraint = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	UPhysicsConstraintComponent *axle_constraint = nullptr;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SetupDriveSide")
	bool bConstraintJointComponentSimulatingPhysics = true;

public:
	// Sets default values for this actor's properties
	AWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// - Brake -
	bool bBrake = false;

	UPROPERTY()
	bool bGrounded = false;

	// - Set Up -
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _initialize(USphereComponent *axle_toset, UPhysicsConstraintComponent *axle_constraint_toset, USphereComponent *wheel_toset, UPhysicsConstraintComponent *wheel_constraint_toset);

	//bind constraint
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _bind_constraint();

	// //Get axle location
	// FVector _get_axle_location();

	//apply force
	void _apply_force(FVector force);

	//Brake
	void _brake();

	//	Grounded
	UFUNCTION()
	void _grounded(UPrimitiveComponent *HitComponent,
				   AActor *OtherActor,
				   UPrimitiveComponent *OtherComp,
				   FVector NormalImpulse,
				   const FHitResult &Hit);
};
