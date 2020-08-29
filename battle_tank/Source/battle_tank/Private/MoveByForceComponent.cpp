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
bool UMoveByForceComponent::_should_move()
{
	if (left_throttle == 0.f && right_throttle == 0.f && l_dest == 0.f && r_dest == 0.f)
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
	float l_clamp = FMath::Clamp<float>(l_dest, -1.f, 1.f);
	float r_clamp = FMath::Clamp<float>(r_dest, -1.f, 1.f);

	if (left_throttle < l_clamp)
	{
		left_throttle += GetWorld()->DeltaTimeSeconds * throttle_rate;
		if (left_throttle > l_clamp)
		{
			left_throttle = l_clamp;
		}
	}
	if (left_throttle > l_clamp)
	{
		left_throttle -= GetWorld()->DeltaTimeSeconds * throttle_rate;
		if (left_throttle < l_clamp)
		{
			left_throttle = l_clamp;
		}
	}
	if (right_throttle < r_clamp)
	{
		right_throttle += GetWorld()->DeltaTimeSeconds * throttle_rate;
		if (right_throttle > r_clamp)
		{
			right_throttle = r_clamp;
		}
	}
	if (right_throttle > r_clamp)
	{
		right_throttle -= GetWorld()->DeltaTimeSeconds * throttle_rate;
		if (right_throttle < r_clamp)
		{
			right_throttle = r_clamp;
		}
	}
}

//Output Throttle
float UMoveByForceComponent::_get_left_throttle()
{
	if (burst)
	{
		UE_LOG(LogTemp, Error, TEXT(" Left is %f ~!"), left_throttle * burst_rate);
		UE_LOG(LogTemp, Error, TEXT(" Left Dest is %f ~!"), l_dest * burst_rate);
		return left_throttle * burst_rate;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" Left is %f ~!"), left_throttle);
		UE_LOG(LogTemp, Error, TEXT(" Left Dest is %f ~!"), l_dest);
		return left_throttle;
	}
};
float UMoveByForceComponent::_get_right_throttle()
{
	if (burst)
	{
		UE_LOG(LogTemp, Error, TEXT(" Right is %f ~!"), right_throttle * burst_rate);
		UE_LOG(LogTemp, Error, TEXT(" Right Dest is %f ~!"), r_dest* burst_rate);
		return right_throttle * burst_rate;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" Right is %f ~!"), right_throttle);
		UE_LOG(LogTemp, Error, TEXT(" Right Dest is %f ~!"), r_dest);
		return right_throttle;
	}
};

//Format Input
void UMoveByForceComponent::_move_forward(bool if_move)
{
	if (if_move)
	{
		l_dest += 1.f;
		r_dest += 1.f;
	}
	else
	{
		l_dest -= 1.f;
		r_dest -= 1.f;
	}
};
void UMoveByForceComponent::_move_backward(bool if_move)
{
	if (if_move)
	{
		l_dest -= 1.f;
		r_dest -= 1.f;
	}
	else
	{
		l_dest += 1.f;
		r_dest += 1.f;
	}
};
void UMoveByForceComponent::_move_left(bool if_move)
{
	if (if_move)
	{
		l_dest -= 1.f;
		r_dest += 1.f;
	}
	else
	{
		l_dest += 1.f;
		r_dest -= 1.f;
	}
};
void UMoveByForceComponent::_move_right(bool if_move)
{
	if (if_move)
	{
		l_dest += 1.f;
		r_dest -= 1.f;
	}
	else
	{
		l_dest -= 1.f;
		r_dest += 1.f;
	}
};
void UMoveByForceComponent::_burst(bool if_burst)
{
	burst = if_burst;
};

// void _intend	----------------------------------------------	TODO
void UMoveByForceComponent::_ai_intend(FVector intend_normal)
{
	// GetOwner()
	FVector forward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float dot = FVector::DotProduct(intend_normal, forward);
	float cross = FVector::CrossProduct(intend_normal, forward).Z;
	//when intend on right of forward, cross is +, we should turn right, so left_throttle work, left + cross
	l_dest = FMath::Clamp<float>(dot + cross, -1.f, 1.f);
	r_dest = FMath::Clamp<float>(dot - cross, -1.f, 1.f);
}