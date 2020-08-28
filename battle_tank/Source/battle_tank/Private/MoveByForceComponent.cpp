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

//		---		SETUP
//Set Sockets that Force Applied
void UMoveByForceComponent::_set_force_sockets_pointer(FVector *left, unsigned short l_amount_toset,
													   FVector *right, unsigned short r_amount_toset)
{
	left_sockets = left;
	l_amount = l_amount_toset;
	right_sockets = right;
	r_amount = r_amount_toset; //	BUG
};

//		---		PRIVATE : self action
//Throttle
void UMoveByForceComponent::_apply_force()
{
	if (burst)
	{
		left_throttle *= burst_rate;
		right_throttle *= burst_rate;
	}
	UE_LOG(LogTemp, Error, TEXT(" Root is : %s ~!"), *(GetOwner()->GetRootComponent()->GetName()));

	//Applly Force To Left Track
	for (int i = 0; i < l_amount; i++) //------------TODO
	{
		Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())
			->AddForceAtLocation(
				left_throttle * (_max_force / l_amount) * left_sockets[i * 2],
				left_sockets[i * 2 + 1]);
		UE_LOG(LogTemp, Warning, TEXT("Left Location is : %s ~!"), *(left_sockets[i * 2 + 1].ToString()));
	}

	//Applly Force To Right Track
	for (int i = 0; i < r_amount; i++)
	{
		Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())
			->AddForceAtLocation(
				right_throttle * (_max_force / r_amount) * right_sockets[i * 2],
				right_sockets[i * 2 + 1]);
	}
};

//		---		PUBLIC : Move
bool UMoveByForceComponent::_should_tick()
{
	if (left_throttle == 0.f && right_throttle == 0.f && !move_f && !move_b && !move_l && !move_r)
	{
		return false;
	}
	else
	{
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

	_apply_force();
}

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
