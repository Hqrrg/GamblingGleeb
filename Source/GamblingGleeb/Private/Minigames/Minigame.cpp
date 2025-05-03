// Fill out your copyright notice in the Description page of Project Settings.


#include "Minigames/Minigame.h"


// Sets default values
AMinigame::AMinigame()
{
	PrimaryActorTick.bCanEverTick = false;

	Duration = 60.f;
	Active = false;
	Win = false;
}

void AMinigame::Begin()
{
	// Don't begin if already active
	if (Active) return;
	
	UWorld* World = GetWorld();
	if (!World) return;

	// Start timer to call End()
	MinigameTimerDelegate.BindUFunction(this, FName("End"));
	World->GetTimerManager().SetTimer(MinigameTimerHandle, MinigameTimerDelegate, Duration, false);

	// Set active
	Active = true;
}

void AMinigame::End()
{
	OnMinigameEnd.Broadcast(Win);
	// Reset vars
	Active = false;
	Win = false;
}

// Get the time remaining on the minigame timer
float AMinigame::GetTimeRemaining()
{
	UWorld* World = GetWorld();
	if (!World) return 0.f;

	FTimerManager& TimerManager = World->GetTimerManager();
	return TimerManager.GetTimerRemaining(MinigameTimerHandle);
}

