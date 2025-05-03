// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"

enum class ECamera : uint8;

UCLASS()
class GAMBLINGGLEEB_API ACameraManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACameraManager();

	UFUNCTION(BlueprintCallable)
	void ChangeCamera(ECamera Key);

	FORCEINLINE void SetPlayerController(APlayerController* Controller) { PlayerController = Controller; }

private:
	UPROPERTY(EditInstanceOnly, Category = "Cameras")
	TMap<ECamera, AActor*> Cameras;

	UPROPERTY()
	APlayerController* PlayerController;
};
