// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing PressurePlate!"), *Owner->GetName())
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	if (GetTotalMassOfActorsInTriggerVolume() >= TriggerMass) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (LastDoorOpenTime != NULL && GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorClosingDelay)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is missing!"))
		return;
	}

	if (RotationYaw > DoorOpenedAngle) {
		RotationYaw -= DoorSpeed;
		Owner->SetActorRotation(FRotator(0.f, RotationYaw, 0.f));
	}
}

void UOpenDoor::CloseDoor()
{
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is missing!"))
		return;
	}

	if (RotationYaw < DoorClosedAngle) {
		RotationYaw += DoorSpeed;
		Owner->SetActorRotation(FRotator(0.f, RotationYaw, 0.f));
	}
}

float UOpenDoor::GetTotalMassOfActorsInTriggerVolume() 
{
	float TotalMass = 0.f;

	if (!PressurePlate) 
	{
		return TotalMass;
	}

	// find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	// iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		float ActorMass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += ActorMass;
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s | Mass: %s"), *Actor->GetName(), *(FString::SanitizeFloat(ActorMass)))
	}

	UE_LOG(LogTemp, Warning, TEXT("Total mass: %s kg"), *(FString::SanitizeFloat(TotalMass)))

	return TotalMass;
}