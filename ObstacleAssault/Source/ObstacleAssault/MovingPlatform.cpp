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

	FString TestString = "This is a test string";

	UE_LOG(LogTemp, Display, TEXT("Message: %s"), *TestString);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime) 
{
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	SetActorLocation(NewLocation);
	
	if (PlatformShouldReturn()) 
	{	
		FVector MovementDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (MovementDirection * MoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//UE_LOG(LogTemp, Display, TEXT("RotatePlatform()"));
	AddActorLocalRotation(RotationVelocity * DeltaTime);

}

bool AMovingPlatform::PlatformShouldReturn() const 
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartLocation, GetActorLocation());
}