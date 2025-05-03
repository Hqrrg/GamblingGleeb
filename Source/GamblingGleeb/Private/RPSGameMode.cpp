// Fill out your copyright notice in the Description page of Project Settings.


#include "RPSGameMode.h"

#include "CameraManager.h"
#include "GamblerController.h"
#include "ParticipantManager.h"
#include "Enums/CameraEnum.h"
#include "Enums/ParticipantEnum.h"
#include "Kismet/GameplayStatics.h"
#include "Minigames/MinigameManager.h"

ARPSGameMode::ARPSGameMode()
{
	PlayerHand = EHand::None;
	ComputerHand = EHand::None;
	ParticipantManager = nullptr;
	MinigameManager = nullptr;
	CameraManager = nullptr;
}

void ARPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, AParticipantManager::StaticClass()))
		{
			AParticipantManager* FoundParticipantManager = Cast<AParticipantManager>(FoundActor);
			ParticipantManager = FoundParticipantManager;
		}
		if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, AMinigameManager::StaticClass()))
		{
			AMinigameManager* FoundMinigameManager = Cast<AMinigameManager>(FoundActor);
			MinigameManager = FoundMinigameManager;
		}
	}
}

APlayerController* ARPSGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* PlayerController = Super::SpawnPlayerController(InRemoteRole, Options);

	if (AGamblerController* GamblerController = Cast<AGamblerController>(PlayerController))
	{
		GamblerControllerRef = GamblerController;
		
		/* Assign camera manager to the first instance found */
		if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraManager::StaticClass()))
		{
			ACameraManager* FoundCameraManager = Cast<ACameraManager>(FoundActor);
			CameraManager = FoundCameraManager;

			/* Set player's camera to default */
			CameraManager->SetPlayerController(GamblerController);
			CameraManager->ChangeCamera(ECamera::Default);
		}
	}
	
	return PlayerController;
}

void ARPSGameMode::GetWinner(EParticipant& Winner, bool& Tie)
{
	Tie = false;

	const uint8 PlayerHandVal = static_cast<uint8>(PlayerHand);
	const uint8 ComputerHandVal = static_cast<uint8>(ComputerHand);

	// Player didn't play hand
	if (!HasPlayedHand(EParticipant::Player))
	{
		Winner = EParticipant::Computer;
		return;
	}

	// Tie check
	if (PlayerHandVal == ComputerHandVal)
	{
		Tie = true;
		Winner = EParticipant::None;
		return;
	}

	/* Checks if player defeating hand is equal to computer hand (modulo means it wraps around)
	 * Rock+1(1) = Paper(2).... Scissors+1(4) = None(4) %3 = Rock(1) */
	if ((PlayerHandVal + 1) % 3 == ComputerHandVal)
	{
		Winner = EParticipant::Computer;
		return;
	}

	// If not a tie or computer wins, then player wins
	Winner = EParticipant::Player;
}

bool ARPSGameMode::PlayHand(EParticipant Participant, EHand Hand)
{
	bool Success = false;
	
	switch (Participant)
	{
		case EParticipant::Player:
			PlayerHand = Hand;
			Success = true;
			break;
		
		case EParticipant::Computer:
			ComputerHand = Hand;
			Success = true;
			break;
	default:
		break;
	}
	return Success;
}

bool ARPSGameMode::HasPlayedHand(EParticipant Participant)
{
	EHand Hand = Participant ==
		EParticipant::Player ? PlayerHand : Participant == EParticipant::Computer ? ComputerHand : EHand::None;

	return Hand != EHand::None;
}

void ARPSGameMode::ResetHands()
{
	PlayerHand = EHand::None;
	ComputerHand = EHand::None;
}

EHand ARPSGameMode::GetHand(EParticipant Participant)
{
	EHand Hand = Participant ==
		EParticipant::Player ? PlayerHand : Participant == EParticipant::Computer ? ComputerHand : EHand::None;

	return Hand;
}

AParticipantManager* ARPSGameMode::GetParticipantManager(bool& bExecs)
{
	bExecs = false;

	if (ParticipantManager)
	{
		bExecs = true;
		return ParticipantManager;
	}
	return nullptr;
}

AMinigameManager* ARPSGameMode::GetMinigameManager(bool& bExecs)
{
	bExecs = false;

	if (MinigameManager)
	{
		bExecs = true;
		return MinigameManager;
	}
	return nullptr;
}

ACameraManager* ARPSGameMode::GetCameraManager(bool& bExecs)
{
	bExecs = false;

	if (CameraManager)
	{
		bExecs = true;
		return CameraManager;
	}
	return nullptr;
}

AGamblerController* ARPSGameMode::GetGamblerController(bool& bExecs)
{
	bExecs = false;

	if (GamblerControllerRef)
	{
		bExecs = true;
		return GamblerControllerRef;
	}
	return nullptr;
}
