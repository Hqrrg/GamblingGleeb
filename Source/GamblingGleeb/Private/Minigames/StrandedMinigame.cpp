// Fill out your copyright notice in the Description page of Project Settings.


#include "Minigames/StrandedMinigame.h"

#include "Minigames/Stranded/ScreenBoundingBox.h"
#include "Minigames/Stranded/StrandedGleeb.h"


// Sets default values
AStrandedMinigame::AStrandedMinigame()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoundingBox = nullptr;
	StrandedGleeb = nullptr;
}

void AStrandedMinigame::Begin()
{
	Super::Begin();

	// Don't begin if there's no bounding box for gleeb
	if (!BoundingBox) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FTransform SpawnTransform = BoundingBox->GetActorTransform();
	
	StrandedGleeb = World->SpawnActorDeferred<AStrandedGleeb>(StrandedGleebClass, SpawnTransform);

	// Spawn gleeb, set bounding box & bind OnShot delegate
	if (StrandedGleeb)
	{
		StrandedGleeb->BoundingBox = BoundingBox;
		StrandedGleeb->OnShot.AddDynamic(this, &AStrandedMinigame::ShotGleeb);
		StrandedGleeb->FinishSpawning(SpawnTransform);
	}
		
}

void AStrandedMinigame::End()
{
	Super::End();

	// Destroy gleeb when the minigame is over
	if (StrandedGleeb) StrandedGleeb->Destroy();
}

void AStrandedMinigame::ShotGleeb()
{
		// Player wins
		SetWon(true);
		End();
}

