// Fill out your copyright notice in the Description page of Project Settings.

#include "Minigames/MinigameManager.h"
#include "Minigames/Minigame.h"


// Sets default values
AMinigameManager::AMinigameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActiveMinigame = nullptr;
}

AMinigame* AMinigameManager::BeginMinigame(EMinigame Key, bool& Success)
{
	Success = false;

	// Don't allow a minigame to be started if one is active
	bool IsActiveMinigame; GetActiveMinigame(IsActiveMinigame);
	if (IsActiveMinigame) return nullptr;

	if (AMinigame** MinigamePtr = Minigames.Find(Key))
	{
		// Update active minigame
		AMinigame* Minigame = *MinigamePtr;
		ActiveMinigame = Minigame;

		// Bind minigame end delegate to clear active minigame
		Minigame->OnMinigameEnd.AddDynamic(this, &AMinigameManager::MinigameEnd);
		// Begin the minigame
		Minigame->Begin();

		Success = true;
		return Minigame;
	}

	return nullptr;
}

AMinigame* AMinigameManager::GetActiveMinigame(bool& bReturn)
{
	if (ActiveMinigame)
	{
		bReturn = true;
		return ActiveMinigame;
	}
	bReturn = false;
	return nullptr;
}

void AMinigameManager::MinigameEnd(bool bWin)
{
	// Reset active minigame
	ActiveMinigame->OnMinigameEnd.Clear();
	ActiveMinigame = nullptr;
}

