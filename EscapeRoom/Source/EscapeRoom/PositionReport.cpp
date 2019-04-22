// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	
	float X = GetOwner()->GetTransform().GetLocation().X;
	float Y = GetOwner()->GetTransform().GetLocation().Y;
	float Z = GetOwner()->GetTransform().GetLocation().Z;

	UE_LOG(LogTemp, Warning, TEXT("%s is at X=%s, Y=%s, Z=%s"), *ObjectName, *FString::SanitizeFloat(X), *FString::SanitizeFloat(Y), *FString::SanitizeFloat(Z));
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

