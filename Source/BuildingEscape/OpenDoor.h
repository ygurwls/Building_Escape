// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingEscape.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

private:
	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts
	// Called when the game starts
	virtual void BeginPlay() override;
	float GetTotalMassOfActorOnPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	AActor* Owner;
	//float LastDoorOpenTime;

	//UPROPERTY(EditAnywhere)
	//float DoorCloseDelay = 1.0f;

	//UPROPERTY(EditAnywhere)
	//float OpenAngle = 90.0f;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 50.0f;

	//UPROPERTY(EditAnywhere)
	//AActor* ActorThatOpens;

};
