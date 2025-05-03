// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/HandEnum.h"
#include "Enums/ParticipantEnum.h"
#include "GameFramework/GameModeBase.h"
#include "RPSGameMode.generated.h"

class AGamblerController;
class AMinigameManager;
class ACameraManager;
class AParticipantManager;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FManagersLoaded);

/**
 * 
 */
UCLASS()
class GAMBLINGGLEEB_API ARPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARPSGameMode();

protected:
	virtual void BeginPlay() override;

	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
	
public:
	UFUNCTION(BlueprintCallable)
	void GetWinner(EParticipant& Winner, bool& Tie);

	UFUNCTION(BlueprintCallable)
	bool PlayHand(EParticipant Participant, EHand Hand);

	UFUNCTION(BlueprintPure)
	bool HasPlayedHand(EParticipant Participant);

	UFUNCTION(BlueprintCallable)
	void ResetHands();

	UFUNCTION(BlueprintPure)
	FORCEINLINE EHand GetHand(EParticipant Participant);

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bExecs"))
	AParticipantManager* GetParticipantManager(bool& bExecs);

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bExecs"))
	AMinigameManager* GetMinigameManager(bool& bExecs);

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bExecs"))
	ACameraManager* GetCameraManager(bool& bExecs);

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bExecs"))
	AGamblerController* GetGamblerController(bool& bExecs);

	UPROPERTY(BlueprintAssignable)
	FManagersLoaded OnManagersLoaded;

private:
	EHand ComputerHand;
	EHand PlayerHand;

	UPROPERTY()
	AParticipantManager* ParticipantManager;

	UPROPERTY()
	ACameraManager* CameraManager;

	UPROPERTY()
	AMinigameManager* MinigameManager;

	UPROPERTY()
	AGamblerController* GamblerControllerRef;
};
