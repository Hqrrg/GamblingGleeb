// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticipantManager.generated.h"

enum class EParticipant : uint8;

UCLASS()
class GAMBLINGGLEEB_API AParticipantManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParticipantManager();

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bExecs"))
	AActor* GetParticipant(EParticipant Key, bool& bExecs);

private:
	UPROPERTY(EditInstanceOnly, Category = "Participant Manager")
	TMap<EParticipant, AActor*> Participants;
	
};
