// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MoveByForceComponent.generated.h"

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

	FVector **left_array;
	FVector **right_array;

	float left_throttle = 0.f;
	float right_throttle = 0.f;

	bool move_f = false;
	bool move_b = false;
	bool move_l = false;
	bool move_r = false;

	bool burst = false;

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float burst_rate = 2; //when press set to 1,or higher

	UPROPERTY(EditAnywhere, Category = "Steer")
	float turn_rate = 1.2; //turning speed

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float throttle_rate = 1; //accelerate time

	void _apply_force();

	UPROPERTY(EditAnywhere, Category = "Accelerate")
	float _max_force = 4000000.f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//SetUp
	void _set_force_sockets_pointer(FVector **left_array, FVector **right_array);

	//tick
	bool _should_tick();
	void _do_move();

	//Move	---	KeyBoard
	void _move_forward(bool if_move);
	void _move_backward(bool if_move);
	void _move_left(bool if_move);
	void _move_right(bool if_move);
	void _burst(bool if_burst);
};
