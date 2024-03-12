// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReporter.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetActorLabel();
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();;
	BELOG_S(Warning);
	BELOG(Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
	// ...
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

