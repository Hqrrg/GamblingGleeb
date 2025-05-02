// Fill out your copyright notice in the Description page of Project Settings.


#include "GamblerController.h"

#include "Interfaces/ClickableInterface.h"

AGamblerController::AGamblerController()
{
	PreviousMousePosition = FVector2D::ZeroVector;
	Hovered = nullptr;
	LeftMouseButtonDown = false;

	HoverCrosshairTextures = TMap<ECrosshairType, UTexture2D*>();
	ClickCrosshairTextures = TMap<ECrosshairType, UTexture2D*>();

	CurrentCrosshairType = ECrosshairType::Default;
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
	
	float MouseX, MouseY; GetMousePosition(MouseX, MouseY);
	
	FRotator CameraRotation = PlayerCameraManager->GetCameraRotation();
	FVector CameraDirection = CameraRotation.Vector().GetSafeNormal();
	
	FVector TraceStart;
	DeprojectScreenPositionToWorld(MouseX, MouseY, TraceStart, CameraDirection);
	
	FVector TraceEnd = TraceStart + CameraDirection * TraceDistance;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (APawn* ControlledPawn = GetPawn())
	{
		QueryParams.AddIgnoredActor(ControlledPawn);
	}

	DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, true, -1, 0, 10.f);
	
	return World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams);;
}

UTexture2D* AGamblerController::GetClickCrosshairTexture(const ECrosshairType Type)
{
	UTexture2D* CrosshairTexture = nullptr;
	if (ClickCrosshairTextures.Contains(Type))
	{
		CrosshairTexture = *ClickCrosshairTextures.Find(Type);
	}
	return CrosshairTexture;
}

UTexture2D* AGamblerController::GetHoverCrosshairTexture(const ECrosshairType Type)
{
	UTexture2D* CrosshairTexture = nullptr;
	if (HoverCrosshairTextures.Contains(Type))
	{
		CrosshairTexture = *HoverCrosshairTextures.Find(Type);
	}
	return CrosshairTexture;
}

void AGamblerController::UpdateCrosshairTexture(ECrosshairType Type)
{
	CurrentCrosshairType = Type;
	UTexture2D* CrosshairTexture = GetHoverCrosshairTexture(Type);
	
	if (GetLeftMouseButtonDown())
	{
		CrosshairTexture = GetClickCrosshairTexture(Type);
	}
	// Ensure texture is valid
	if (CrosshairTexture)
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
