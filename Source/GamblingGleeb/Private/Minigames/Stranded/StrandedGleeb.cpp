// Fill out your copyright notice in the Description page of Project Settings.


#include "Minigames/Stranded/StrandedGleeb.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Enums/CrosshairTypeEnum.h"
#include "Minigames/Stranded/ScreenBoundingBox.h"


// Sets default values
AStrandedGleeb::AStrandedGleeb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = CollisionComponent;
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetupAttachment(RootComponent);

	// Defaults
	Velocity = FVector2D(100.f, 100.f);
	MovementDirection = FVector2D(1.f, 1.f);
	CanMove = true;
}

// Called when the game starts or when spawned
void AStrandedGleeb::BeginPlay()
{
	Super::BeginPlay();

	if (BoundingBox)
	{
		FVector2D UpperBounds, LowerBounds;
		BoundingBox->CalculateBounds(UpperBounds, LowerBounds);

		constexpr float Buffer = 50.0f;

		// Random position within bounding box
		const float X = FMath::RandRange(LowerBounds.X+Buffer, UpperBounds.X-Buffer);
		const float Y = FMath::RandRange(LowerBounds.Y+Buffer, UpperBounds.Y-Buffer);
		const FVector SpawnLoc = FVector(BoundingBox->GetActorLocation().X, X, Y);

		// Random movement direction
		const float MoveDirX = FMath::RoundToInt(FMath::RandRange(0.f, 1.f)) * 2 - 1;
		const float MoveDirY = FMath::RoundToInt(FMath::RandRange(0.f, 1.f)) * 2 - 1;
		MovementDirection = FVector2D(MoveDirX, MoveDirY);

		// Random speed
		RandomizeVelocity();
		
		// Teleport within bounding box
		SetActorLocation(SpawnLoc);
	}
}

// Called every frame
void AStrandedGleeb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BoundingBox && CanMove)
	{
		// Retrieve bounds of bounding box
		FVector2D UpperBounds, LowerBounds; BoundingBox->CalculateBounds(UpperBounds, LowerBounds);

		// Retrieve actor location & bounds
		const FVector ActorLocation = GetActorLocation();
		FVector Origin, Extent; GetActorBounds(false, Origin, Extent);

		// Remove depth dimension (X)
		const FVector2D ActorLocation2D = FVector2D(ActorLocation.Y, ActorLocation.Z);
		const FVector2D ActorBounds2D = FVector2D(Extent.Y, Extent.Z);

		// If actor is bordering or exceeding bounding box horizontally then invert horizontal direction
		if (ActorLocation2D.X + ActorBounds2D.X >= UpperBounds.X || ActorLocation2D.X - ActorBounds2D.X  <= LowerBounds.X)
		{
			MovementDirection.X = -MovementDirection.X;
			RandomizeVelocity();
		}
		
		// If actor is bordering or exceeding bounding box vertically then invert vertical direction
		if (ActorLocation2D.Y + ActorBounds2D.Y >= UpperBounds.Y || ActorLocation2D.Y - ActorBounds2D.Y <= LowerBounds.Y)
		{
			MovementDirection.Y = -MovementDirection.Y;
			RandomizeVelocity();
		}

		// Target location without depth dimension (X)
		const FVector2D TargetLocation2D = ActorLocation2D + Velocity * MovementDirection * DeltaTime;
		// Target location with depth dimension (X)
		const FVector TargetLocation = FVector(ActorLocation.X, TargetLocation2D.X, TargetLocation2D.Y);

		// Move
		SetActorLocation(TargetLocation);	
	}
}

// Called when clicked
void AStrandedGleeb::Clicked_Implementation(APlayerController* Player)
{
	OnShot.Broadcast();
}

void AStrandedGleeb::GetCrosshairType_Implementation(ECrosshairType& Type)
{
	Type = ECrosshairType::Crosshair;
}

void AStrandedGleeb::RandomizeVelocity()
{
	const float VelocityX = FMath::RandRange(VelocityBoundsX.X, VelocityBoundsX.Y);
	const float VelocityY = FMath::RandRange(VelocityBoundsY.X, VelocityBoundsY.Y);
	Velocity = FVector2D(VelocityX, VelocityY);
}
