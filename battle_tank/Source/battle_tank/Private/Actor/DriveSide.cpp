// Fill out your copyright notice in the Description page of Project Settings.

#include "DriveSide.h"
//include first
#include "Config.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "TankTrack.h"
#include "Wheel.h"

// Sets default values - 	#### TODO : Override Constructor
ADriveSide::ADriveSide()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// _setup_anchors();	-  Set at BP Construct
	// _setup_wheel_class()  -  Set at BP
	UE_LOG(LogTemp, Warning, TEXT("DONKEY : Side C++ Construct "));
}

// Called when the game starts or when spawned
void ADriveSide::BeginPlay()
{
	Super::BeginPlay();
	//Bind Constraint After Spawn Sub Actor
	_bind_constraint();
}

// Called every frame
void ADriveSide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*  - Set Up -  */
//setup wheels
void ADriveSide::_initialize(UTankTrack *track_toset, UPhysicsConstraintComponent *constraint_toset, TArray<UChildActorComponent *> wheels_anchors_toset)
{
	//Attach Track - StaticMesh
	if (track_toset)
	{
		track = track_toset;
	}
	if (constraint_toset)
	{
		track_constraint = constraint_toset;
	}

	//Attach Wheels - Actor
	//reset
	wheels_anchor.Empty();
	wheels.Empty();

	//Check Child Actor is AWheel
	AWheel *temp;
	for (UChildActorComponent *anchor : wheels_anchors_toset)
	{
		if (!anchor)
		{
			wheels.Add(nullptr);
			wheels_anchor.Add(nullptr);
			continue;
		}
		temp = Cast<AWheel>(anchor->GetChildActor());
		wheels.Add(temp);
		if (temp)
			wheels_anchor.Add(anchor);
		else
			wheels_anchor.Add(nullptr);
	}
	//setup
};

//bind constraint
void ADriveSide::_bind_constraint(UPrimitiveComponent *ComponentToBind)
{
	//Bind Constraint to Parent RootComponent
	if (!ComponentToBind)
	{
		if (!GetAttachParentActor())
			return;
		ComponentToBind = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	}
	if (ComponentToBind)
	{
		if (ComponentToBind->IsSimulatingPhysics())
		{
			bConstraintJointComponentSimulatingPhysics = true;
		}
		else
		{
			bConstraintJointComponentSimulatingPhysics = false;
			UE_LOG(LogTemp, Warning, TEXT("DONKEY : Component for Track to Bind is not Simulating Physics."));
		}
		//Simulate Physics before Bind Wheels - # will Dettach from parent,
		track->SetSimulatePhysics(true);
		track->SetCollisionProfileName(FName("VisibleBody"));
		/* */
		//Bind Wheels
		for (AWheel *awheel : wheels)
		{
			if (awheel)
			{
				awheel->_bind_constraint(track);
			}
		}
		//Bind Track
		track_constraint->SetConstrainedComponents(ComponentToBind, NAME_None, track, NAME_None);
		/* - BUG FIXED 1 - */
	}
};

// /*  - Dettach -  */
// void ADriveSide::_dettach()
// {
// 	track_constraint->BreakConstraint();
// };

/* Apply Force */
//PassTo Track
void ADriveSide::_apply_force(float throttle)
{
	if (bBrake || !bConstraintJointComponentSimulatingPhysics || !wheels.IsValidIndex(0))
		return;
	// float force = _max_force / wheels.Num();
	for (AWheel *awheel : wheels)
	{
		if (awheel)
			if (awheel->bGrounded)
			{
				// UE_LOG(LogTemp, Warning, TEXT("DONKEY : Side Apply Force ~! "));
				track->AddForce(track->GetForwardVector() * throttle * _max_force);
				awheel->bGrounded = false;
				return;
			}
	}
};

//Brake
void ADriveSide::_brake(bool if_brake)
{
	bBrake = if_brake;
	for (AWheel *awheel : wheels)
	{
		if (awheel)
		{
			awheel->bBrake = if_brake;
			awheel->_brake();
		}
	}
};