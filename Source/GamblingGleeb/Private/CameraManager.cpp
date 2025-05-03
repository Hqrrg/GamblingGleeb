// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"


// Sets default values
ACameraManager::ACameraManager()
{
	PrimaryActorTick.bCanEverTick = false;
	Cameras = TMap<ECamera, AActor*>();
	PlayerController = nullptr;
}

void ACameraManager::ChangeCamera(ECamera Key)
{
	if (!PlayerController) return;
	
	if (AActor** ActorPtr = Cameras.Find(Key))
	{
		AActor* Actor = *ActorPtr;
		PlayerController->SetViewTarget(Actor);
	}
}

