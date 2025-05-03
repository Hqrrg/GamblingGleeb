// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticipantManager.h"


// Sets default values
AParticipantManager::AParticipantManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Participants = TMap<EParticipant, AActor*>();
}

AActor* AParticipantManager::GetParticipant(EParticipant Key, bool& bExecs)
{
	bExecs = false;
	
	if (AActor** Participant = Participants.Find(Key))
	{
		bExecs = true;
		return *Participant;
	}
	return nullptr;
}

