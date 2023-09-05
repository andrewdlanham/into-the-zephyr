// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime) 
{
	// Move platform forwards
		// Get current platform location
		FVector CurrentLocation = GetActorLocation();
		// Add vector to location
		FVector NewLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		// Set the location
		SetActorLocation(NewLocation);
	// Reverse direction of platform if needed
		// Check distance
		float DistanceFromStart = FVector::Distance(StartLocation, CurrentLocation);
		// Reverse direction if needed
		if (DistanceFromStart > MoveDistance) 
		{	
			FVector MovementDirection = PlatformVelocity.GetSafeNormal();
			StartLocation = StartLocation + (MovementDirection * MoveDistance);
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity;
		}

		UE_LOG(LogTemp, Display, TEXT("Your message"));
}

