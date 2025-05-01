// Fill out your copyright notice in the Description page of Project Settings.


#include "Minigames/Stranded/ScreenBoundingBox.h"

#include "Components/BoxComponent.h"


// Sets default values
AScreenBoundingBox::AScreenBoundingBox()
{
	// Disable tick
	PrimaryActorTick.bCanEverTick = false;

	BoundingBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundingBox"));
	BoundingBoxComponent->SetupAttachment(RootComponent);
}

// Calculate the upper and lower boundaries
void AScreenBoundingBox::CalculateBounds(FVector2D& UpperBounds, FVector2D& LowerBounds)
{
	FVector Size = BoundingBoxComponent->Bounds.GetBox().GetSize();
	FVector Position = BoundingBoxComponent->GetComponentLocation();

	// Remove depth dimension
	FVector2D Size2D = FVector2D(Size.Y, Size.Z);
	FVector2D Position2D = FVector2D(Position.Y, Position.Z);
	
	LowerBounds = FVector2D(Position2D.X - Size2D.X / 2.f, Position2D.Y - Size2D.Y / 2.f);
	UpperBounds = FVector2D(Position2D.X + Size2D.X / 2.f, Position2D.Y + Size2D.Y / 2.f);
}
