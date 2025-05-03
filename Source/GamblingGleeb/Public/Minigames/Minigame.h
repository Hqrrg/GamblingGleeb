// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minigame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMinigameEnd, bool, bWin);

UCLASS()
class GAMBLINGGLEEB_API AMinigame : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMinigame();

	UFUNCTION()
	virtual void Begin();

	UFUNCTION()
	virtual void End();

	UPROPERTY(BlueprintAssignable)
	FMinigameEnd OnMinigameEnd;

	UFUNCTION(BlueprintCallable)
	float GetTimeRemaining();

	FORCEINLINE void SetWon(const bool bWin) { Win = bWin; }

private:
	UPROPERTY(EditAnywhere, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	float Duration;
	
	bool Active;
	bool Win;

	FTimerHandle MinigameTimerHandle;
	FTimerDelegate MinigameTimerDelegate;
};
