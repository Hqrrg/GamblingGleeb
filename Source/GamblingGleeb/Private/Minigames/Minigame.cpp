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
	if (Active) return;
	
	UWorld* World = GetWorld();
	if (!World) return;

	MinigameTimerDelegate.BindUFunction(this, FName("End"));
	World->GetTimerManager().SetTimer(MinigameTimerHandle, MinigameTimerDelegate, Duration, false);

	Active = true;
}

void AMinigame::End()
{
	OnMinigameEnd.Broadcast(Win);

	Active = false;
	Win = false;
}

float AMinigame::GetTimeRemaining()
{
	UWorld* World = GetWorld();
	if (!World) return 0.f;

	FTimerManager& TimerManager = World->GetTimerManager();
	return TimerManager.GetTimerRemaining(MinigameTimerHandle);
}

