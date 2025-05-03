// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minigame.h"
#include "StrandedMinigame.generated.h"

class AStrandedGleeb;
class AScreenBoundingBox;

UCLASS()
class GAMBLINGGLEEB_API AStrandedMinigame : public AMinigame
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStrandedMinigame();
	
	virtual void Begin() override;
	virtual void End() override;

	UFUNCTION()
	void ShotGleeb();

private:
	UPROPERTY(EditInstanceOnly, Category = "Defaults")
	AScreenBoundingBox* BoundingBox;

	UPROPERTY()
	AStrandedGleeb* StrandedGleeb;

	UPROPERTY(EditInstanceOnly, Category = "Defaults")
	TSubclassOf<AStrandedGleeb> StrandedGleebClass;
};
