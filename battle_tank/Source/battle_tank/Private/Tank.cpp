// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	aiming_component = CreateDefaultSubobject<UAimingComponent>(FName(TEXT("aiming_component")));
	aiming_component->_set_owner(this);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
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
}
//-----------------------------------------------------private--------------------------------------------------------
//Set Barrel Reference
void ATank::_set_barrel_reference(UTankBarrel *barrel_to_set)
{
	barrel = barrel_to_set;
};

//Set Turrent Reference
void ATank::_set_turrent_reference(UTankTurrent *turrent_to_set)
{
	turrent = turrent_to_set;
};
//------------------------------------------------------public----------------------------------------------------------
//Get Launch Speed
float ATank::_get_launch_speed() const
{
	return launch_speed;
}
//----Launch()
void ATank::_launch() const {

};
