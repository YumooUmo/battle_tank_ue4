// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveByForceComponent.h"

// Sets default values for this component's properties
UMoveByForceComponent::UMoveByForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UMoveByForceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UMoveByForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//		---		PRIVATE : self action
//Throttle

//		---		PUBLIC : Move
bool UMoveByForceComponent::_should_tick()
{
	if (left_throttle == 0.f && right_throttle == 0.f && !move_f && !move_b && !move_l && !move_r)
	{
		return false;
	}
	else
	{
		_do_move();
		return true;
	}
};

void UMoveByForceComponent::_do_move()
{
	if (move_f)
	{
		if (left_throttle < throttle_rate)
		{
			left_throttle += GetWorld()->DeltaTimeSeconds;
		}
		else if (left_throttle > throttle_rate)
		{
			left_throttle = throttle_rate;
		}
		if (right_throttle < throttle_rate)
		{
			right_throttle += GetWorld()->DeltaTimeSeconds;
		}
		else if (right_throttle > throttle_rate)
		{
			right_throttle = throttle_rate;
		}
	}
	else
	{
		if (left_throttle > 0)
		{
			left_throttle -= GetWorld()->DeltaTimeSeconds;
			if (left_throttle < 0)
			{
				left_throttle = 0;
			}
		}
		if (right_throttle > 0)
		{
			right_throttle -= GetWorld()->DeltaTimeSeconds;
			if (right_throttle < 0)
			{
				right_throttle = 0;
			}
		}
	}

	if (move_b)
	{
		if (left_throttle > -throttle_rate)
		{
			left_throttle -= GetWorld()->DeltaTimeSeconds;
		}
		else if (left_throttle < -throttle_rate)
		{
			left_throttle = -throttle_rate;
		}
		if (right_throttle > -throttle_rate)
		{
			right_throttle -= GetWorld()->DeltaTimeSeconds;
		}
		else if (right_throttle < -throttle_rate)
		{
			right_throttle = -throttle_rate;
		}
	}
	else
	{
		if (left_throttle < 0)
		{
			left_throttle += GetWorld()->DeltaTimeSeconds;
			if (left_throttle > 0)
			{
				left_throttle = 0;
			}
		}
		if (right_throttle < 0)
		{
			right_throttle += GetWorld()->DeltaTimeSeconds;
			if (right_throttle > 0)
			{
				right_throttle = 0;
			}
		}
	}

	if (move_l)
	{
		if (left_throttle > -throttle_rate)
		{
			left_throttle -= GetWorld()->DeltaTimeSeconds * turn_rate;
		}
		else if (left_throttle < -throttle_rate)
		{
			left_throttle = -throttle_rate;
		}
		if (right_throttle < throttle_rate)
		{
			right_throttle += GetWorld()->DeltaTimeSeconds * turn_rate;
		}
		else if (right_throttle > throttle_rate)
		{
			right_throttle = throttle_rate;
		}
	}

	if (move_r)
	{
		if (left_throttle < throttle_rate)
		{
			left_throttle += GetWorld()->DeltaTimeSeconds * turn_rate;
		}
		else if (left_throttle > throttle_rate)
		{
			left_throttle = throttle_rate;
		}
		if (right_throttle > -throttle_rate)
		{
			right_throttle -= GetWorld()->DeltaTimeSeconds * turn_rate;
		}
		else if (right_throttle < -throttle_rate)
		{
			right_throttle = -throttle_rate;
		}
	}
}

float UMoveByForceComponent::_get_left_throttle()
{
	if (burst)
	{
		return left_throttle * burst_rate;
	}
	else
	{
		return left_throttle;
	}
};
float UMoveByForceComponent::_get_right_throttle()
{
	if (burst)
	{
		return right_throttle *= burst_rate;
	}
	else
	{
		return right_throttle;
	}
};

void UMoveByForceComponent::_move_forward(bool if_move)
{
	move_f = if_move;
};
void UMoveByForceComponent::_move_backward(bool if_move)
{
	move_b = if_move;
};
void UMoveByForceComponent::_move_left(bool if_move)
{
	move_l = if_move;
};
void UMoveByForceComponent::_move_right(bool if_move)
{
	move_r = if_move;
};
void UMoveByForceComponent::_burst(bool if_burst)
{
	burst = if_burst;
};
