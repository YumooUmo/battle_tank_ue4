// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
//last generate
#include "ForceNavMovementComponent.generated.h"

class UTankTrack;
/**
 * Move - apply force on two tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UForceNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankTrack *left_track = nullptr;
	// UPROPERTY(BlueprintReadOnly, Category = "Mesh")
	UTankTrack *right_track = nullptr;

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
	UForceNavMovementComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// - Set Up -
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void _setup(UTankTrack *left_track_toset, UTankTrack *right_track_toset);

	// - Move -
	//keyboard
	void _move_keyboard();
	//apply force
	void _apply_force();
	void _stop_apply_force();
	// - BindAction input -
	//keyboard
	void _move_forward(bool if_move);
	void _move_backward(bool if_move);
	void _move_left(bool if_move);
	void _move_right(bool if_move);
	//stick
	void _input_stick(float l_dest, float r_dest);
	//Set Burst
	void _burst(bool if_burst);

	// - Get throttle -
	float _get_left_throttle();
	float _get_right_throttle();

	// - Ai Direct -
	void _ai_direct(FVector intend_normal);

	//AI_director
	void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;
};