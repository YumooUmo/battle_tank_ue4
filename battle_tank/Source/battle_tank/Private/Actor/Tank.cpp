// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
//FIRST include
#include "Components/ChildActorComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ Construct "), *name);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//test
	FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ BeginPlay "), *name);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Show Widget : When start being Possessed by Player
}

//----------------------------------		PUBLIC		----------------------------------------
// - Take Damage -
float ATank::TakeDamage(
	float Damage,
	struct FDamageEvent const &DamageEvent,
	AController *EventInstigator,
	AActor *DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	if (DamagePoints >= CurrentHealth)
	{
		CurrentHealth = 0;
		OnDeath.ExecuteIfBound();
	}
	else
	{
		CurrentHealth -= DamagePoints;
	}
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Take Damage %i "), DamagePoints);
	return DamagePoints;
};

TArray<int32> Arr{1, 1, 2, 2, 2, 3, 3, 4, 4};
//去重条件是：数组Arr是有序的
TArray<int32> RemoveDuplicates(TArray<int32> Arr)
{
	int32 index = 0;
	for (int32 i : Arr)
	{
		if (i != Arr[index])
		{
			index++;
			Arr[index] = i;
		}
	}
	Arr.SetNum(index + 1);
	return Arr;
}