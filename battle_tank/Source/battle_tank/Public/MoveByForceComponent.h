// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MoveByForceComponent.generated.h"
/**
 *MoveByForceComonent : For Two Throttle Drive. Transfer W A S D to axis value. Return Left and Right throttle value.
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UMoveByForceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMoveByForceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float left_throttle = 0.f;
	float right_throttle = 0.f;

	float l_dest = 0.f;
	float r_dest = 0.f;

	bool burst = false;

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float burst_rate = 1.2; //when press set to 1,or higher

	// UPROPERTY(EditAnywhere, Category = "Steer")
	// float turn_rate = 1.5; //turning speed

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float throttle_rate = 2.f; //accelerate time

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//tick
	bool _should_move();
	void _do_move();
	//	GET
	float _get_left_throttle();
	float _get_right_throttle();

	//Move	---	KeyBoard
	void _move_forward(bool if_move);
	void _move_backward(bool if_move);
	void _move_left(bool if_move);
	void _move_right(bool if_move);
	void _burst(bool if_burst);
	void _ai_intend(FVector intend_normal);
};
