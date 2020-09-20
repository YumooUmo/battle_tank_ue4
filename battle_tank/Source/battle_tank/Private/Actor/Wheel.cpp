// Fill out your copyright notice in the Description page of Project Settings.

#include "Wheel.h"
//include first
#include "Components/SphereComponent.h"
#include "Config.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AWheel::AWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_initialize();
}

// Called when the game starts or when spawned
void AWheel::BeginPlay()
{
	Super::BeginPlay();
	SetTickGroup(ETickingGroup::TG_PostPhysics);

	wheel->SetNotifyRigidBodyCollision(true);
	wheel->OnComponentHit.AddDynamic(this, &AWheel::_grounded);
}

// Called every frame
void AWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bBrake)
	{
		_brake();
	}
}

// - Set Up -
void AWheel::_initialize()
{
	//Axle
	if (axle)
	{
		axle->DestroyComponent();
	}
	axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	SetRootComponent(axle);

	// axle->SetSimulatePhysics(true);
	if (axle_constraint)
	{
		axle_constraint->DestroyComponent();
	}
	axle_constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleConstraint"));
	axle_constraint->SetupAttachment(axle);
	axle_constraint->SetDisableCollision(true);

	//Wheel
	if (wheel)
	{
		wheel->DestroyComponent();
	}
	wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	wheel->SetupAttachment(axle);

	// wheel->SetSimulatePhysics(true);
	if (wheel_constraint)
	{
		wheel_constraint->DestroyComponent();
	}
	wheel_constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	wheel_constraint->SetupAttachment(axle);
	wheel_constraint->SetDisableCollision(true);

	//Collision set
	wheel->SetCollisionProfileName(FName("InvisibleBody"));
	wheel->SetConstraintMode(EDOFMode::SixDOF);
	axle->SetCollisionProfileName(FName("InvisibleBody"));
};

//bind constraint
void AWheel::_bind_constraint(UPrimitiveComponent *ComponentToBind)
{
	// /* - BUG FIX 1- */
	// /* - parent should simulating physics, if so wheel too - */
	// /* - FIX : Before Spawn this AWheel, pass a SimulatingPhysRoot to SpawnAnchor for attach - */
	//Bind Constraint to Parent RootComponent
	if (ComponentToBind)
	{
		if (!ComponentToBind->IsSimulatingPhysics())
		{
			bConstraintJointComponentSimulatingPhysics = false;
			UE_LOG(LogTemp, Warning, TEXT("DONKEY : Component for Wheels to Bind is not Simulating Physics."));
		}
		else
		{
			bConstraintJointComponentSimulatingPhysics = true;
		}
		/* - BUG FIX 1 : DriveSide::_spawn_wheels()- */
		wheel->SetSimulatePhysics(true);
		axle->SetSimulatePhysics(true);
		axle_constraint->SetConstrainedComponents(ComponentToBind, NAME_None, axle, NAME_None);
		wheel_constraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);

		//Collision set
		wheel->SetCollisionProfileName(FName("InvisibleBody"));
		wheel->SetConstraintMode(EDOFMode::SixDOF);
		axle->SetCollisionProfileName(FName("InvisibleBody"));
	}
};

// //Get axle location
// FVector AWheel::_get_axle_location()
// {
// 	if (axle)
// 	{
// 		return axle->GetRelativeLocation();
// 	}
// };

//Brake
void AWheel::_brake()
{
	if (bBrake)
	{
		UE_LOG(LogTemp, Warning, TEXT("DONKEY : Wheel ROTATION %f"), wheel_constraint->GetCurrentSwing2());
		if (FMath::Abs(wheel_constraint->GetCurrentSwing2()) < 10.f)
			wheel_constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	}
	else
	{
		wheel_constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0.f);
	}
};

//Delegate
void AWheel::_grounded(UPrimitiveComponent *HitComponent,
					   AActor *OtherActor,
					   UPrimitiveComponent *OtherComp,
					   FVector NormalImpulse,
					   const FHitResult &Hit)
{
	// UE_LOG(LogTemp, Error, TEXT("DONKEY : Grounded"));
	bGrounded = true;
}
