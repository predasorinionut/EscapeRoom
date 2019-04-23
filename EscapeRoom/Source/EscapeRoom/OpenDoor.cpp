// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorClosingDelay) {
			CloseDoor();
		}
	}

	// Poll if the chair is overlapping the actor that opens
		// If true, grab the chair
}

void UOpenDoor::OpenDoor()
{
	if (RotationYaw > DoorOpenedAngle) {
		RotationYaw -= DoorSpeed;
		Owner->SetActorRotation(FRotator(0.f, RotationYaw, 0.f));
	}
}

void UOpenDoor::CloseDoor()
{
	if (RotationYaw < DoorClosedAngle) {
		RotationYaw += DoorSpeed;
		Owner->SetActorRotation(FRotator(0.f, RotationYaw, 0.f));
	}
}