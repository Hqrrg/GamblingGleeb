// Fill out your copyright notice in the Description page of Project Settings.


#include "GamblerController.h"

#include "Interfaces/ClickableInterface.h"

AGamblerController::AGamblerController()
{
	PreviousMousePosition = FVector2D::ZeroVector;
	Hovered = nullptr;

	CrosshairTextures = TMap<ECrosshairType, UTexture2D*>();
}

void AGamblerController::BeginPlay()
{
	Super::BeginPlay();

	UpdateCrosshairTexture(ECrosshairType::Default);
}

void AGamblerController::Tick(float DeltaTime)
{
	UpdateMousePosition();
	
	FHitResult Hit;
	if (LineTraceFromMouse(Hit, 1000.f))
	{
		// Test if hit actor and is not previously hovered
		if (AActor* HitActor = Hit.GetActor(); HitActor != Hovered)
		{
			Hovered = HitActor;
			ECrosshairType CrosshairType = ECrosshairType::Default;
			
			if (Hovered->Implements<UClickableInterface>())
			{
				IClickableInterface::Execute_GetCrosshairType(Hovered, CrosshairType);
			}
			UpdateCrosshairTexture(CrosshairType);
		}
	}
}

bool AGamblerController::LineTraceFromMouse(FHitResult& HitResult, float TraceDistance)
{
	UWorld* World = GetWorld();
	if (!World) return false;
	
	FVector TraceStart, TraceDirection;
	if (DeprojectMousePositionToWorld(TraceStart, TraceDirection)) return false;
	
	FVector TraceEnd = TraceStart + TraceDirection * TraceDistance;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (APawn* ControlledPawn = GetPawn())
	{
		QueryParams.AddIgnoredActor(ControlledPawn);
	}
	
	return World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams);;
}

UTexture2D* AGamblerController::GetCrosshairTexture(const ECrosshairType Type)
{
	UTexture2D* CrosshairTexture = nullptr;
	if (CrosshairTextures.Contains(Type))
	{
		CrosshairTexture = *CrosshairTextures.Find(Type);
	}
	return CrosshairTexture;
}

void AGamblerController::UpdateCrosshairTexture(ECrosshairType Type)
{
	// Ensure texture is valid
	if (UTexture2D* CrosshairTexture = GetCrosshairTexture(Type))
	{
		// Broadcast crosshair updated
		OnCrosshairTextureUpdated.Broadcast(CrosshairTexture);
	}
}

void AGamblerController::UpdateMousePosition()
{
	float MouseX, MouseY; GetMousePosition(MouseX, MouseY);
	if (FVector2D MousePosition = FVector2D(MouseX, MouseY); MousePosition != PreviousMousePosition)
	{
		OnMousePositionUpdated.Broadcast(MousePosition);
		PreviousMousePosition = MousePosition;
	}
}
