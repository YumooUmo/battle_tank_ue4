// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
//last generate
#include "TrackForceAdapterComponent.generated.h"

class ADriveSide;

/**
 * Move - apply force on two tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTrackForceAdapterComponent : public UNavMovementComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// - Child Actor -
	UPROPERTY(EditAnywhere, Category = "ChildActor")
	UChildActorComponent *left_child_component;

	UPROPERTY(EditAnywhere, Category = "ChildActor")
	UChildActorComponent *right_child_component;

	ADriveSide *left_driveside = nullptr;
	ADriveSide *right_driveside = nullptr;

	//DEBUG
	AActor *test_left;
	AActor *test_right;

	float left_throttle = 0.f;
	float right_throttle = 0.f;

	float l_dest = 0.f;
	float r_dest = 0.f;

	bool burst = false;

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float burst_rate = 1.3f; //when press set to 1,or higher

	// UPROPERTY(EditAnywhere, Category = "Steer")
	// float turn_rate = 1.5; //turning speed

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float throttle_rate = 4.f; //Force increass time

	FTimerHandle move_timer;

public:
	// Sets default values for this component's properties
	UTrackForceAdapterComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// - Set Up -
	//Setup
	UFUNCTION(BlueprintCallable, Category = "Setup")
	bool _setup_left(UChildActorComponent *left_child_component_toset = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	bool _setup_right(UChildActorComponent *right_child_component_toset = nullptr);
	//Attach
	UFUNCTION(BlueprintCallable, Category = "Bind")
	bool _attach_left(AActor *child_actor);
	UFUNCTION(BlueprintCallable, Category = "Bind")
	bool _attach_right(AActor *child_actor);

	//Get
	UFUNCTION(BlueprintCallable, Category = "Attach")
	void _detach_left_driveside();
	UFUNCTION(BlueprintCallable, Category = "Attach")
	void _detach_right_driveside();

	UFUNCTION(BlueprintCallable, Category = "Attach")
	void _attach_test();

	// - Move -
	//keyboard
	void _move_keyboard();
	//apply force
	void _apply_force();
	void _stop_apply_force();


	// - BindAction input -
	//keyboard
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _move_forward(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _move_backward(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _move_left(bool if_move);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _move_right(bool if_move);
	//stick
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _input_stick(float l_dest, float r_dest);
	//Set Burst
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void _burst(bool if_burst);
	//Brake
	UFUNCTION(BlueprintCallable, Category = "Brake")
	void _brake(bool if_brake);

	// - Ai Direct -
	void _ai_direct(FVector intend_normal);

	//AI_director
	void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;
};