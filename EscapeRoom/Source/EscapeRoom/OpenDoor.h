// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor();
	void CloseDoor();

private:
	float RotationYaw = 0.f;
	
	UPROPERTY(EditAnywhere)
	float DoorSpeed = 1.f;
	
	UPROPERTY(EditAnywhere)
	float DoorClosingDelay = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float DoorOpenedAngle = -90.f;
	
	float DoorClosedAngle = 0.f;
	
	float LastDoorOpenTime;

	AActor* Owner;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnywhere)
	float TriggerMass = 90.f;

	float GetTotalMassOfActorsInTriggerVolume();
};
