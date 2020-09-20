// Fill out your copyright notice in the Description page of Project Settings.

#include "AttachAnchor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAttachAnchor::UAttachAnchor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UAttachAnchor::BeginPlay()
{
	_delete_children();
	Super::BeginPlay();

	// ...
}

// Called every frame
void UAttachAnchor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Attach
void UAttachAnchor::_attach(AActor *actor_toattach)
{
	if (!GetNumChildrenComponents() && actor_toattach)
		actor_toattach->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
};

//Delete Children
void UAttachAnchor::_delete_children()
{
	TArray<USceneComponent *> Children;
	GetChildrenComponents(true, Children);
	if (!Children.IsValidIndex(0))
	{
		return;
	}
	else
	{
		for (USceneComponent *temp : Children)
		{
			temp->DestroyComponent();
		}
	}
};