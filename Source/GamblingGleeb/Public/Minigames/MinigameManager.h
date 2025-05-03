// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/MinigameEnum.h"
#include "GameFramework/Actor.h"
#include "MinigameManager.generated.h"

class AMinigame;
class AStrandedMinigame;
enum class EMinigame : uint8;

UCLASS()
class GAMBLINGGLEEB_API AMinigameManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMinigameManager();

	UFUNCTION(BlueprintCallable)
	AMinigame* BeginMinigame(EMinigame Key, bool& Success);

	UFUNCTION(BlueprintCallable)
	AMinigame* GetActiveMinigame(bool& bReturn);

private:
	UPROPERTY()
	AMinigame* ActiveMinigame;
	
	UPROPERTY(EditInstanceOnly, Category = "Minigames")
	TMap<EMinigame, AMinigame*> Minigames;

	UFUNCTION()
	void MinigameEnd(bool bWin);
};
