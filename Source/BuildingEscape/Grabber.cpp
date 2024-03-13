// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) return;

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTracePoints().v2);
	}
	// ...
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else {
		BELOG(Error, TEXT("%s missing input component"), *GetOwner()->GetActorLabel());
	}
}

FTwoVectors UGrabber::GetLineTracePoints() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * Reach;

	return FTwoVectors(PlayerViewPointLocation, LineTraceEnd);
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		BELOG(Error, TEXT("%s missing physics handle component"),
			*GetOwner()->GetName());
	}
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	//FVector PlayerViewPointLocation;
	//FRotator PlayerViewPointRotation;

	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	////BELOG(Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	//FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	////DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0, 0, 10);

	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FTwoVectors TracePoints = GetLineTracePoints();

	//GetWorld()->LineTraceSingleByChannel(
	//	OUT Hit,
	//	PlayerViewPointLocation,
	//	LineTraceEnd,
	//	ECollisionChannel::ECC_PhysicsBody,
	//	TraceParameters
	//);

	GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		TracePoints.v1,
		TracePoints.v2,
		ECollisionChannel::ECC_PhysicsBody,
		TraceParameters
	);

	return Hit;

	//AActor* ActorHit = Hit.GetActor();
	//if (ActorHit) {
	//	BELOG(Warning, TEXT("Line trace hit: %s"), *ActorHit->GetActorLabel());
	//}

	//return Hit;
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab,
			NAME_None, ActorHit->GetActorLocation(), ActorHit->GetActorRotation());
	}
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}
