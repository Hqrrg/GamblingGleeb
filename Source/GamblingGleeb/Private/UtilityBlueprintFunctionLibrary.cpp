// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityBlueprintFunctionLibrary.h"

#include "Components/ParticipantComponent.h"

UParticipantComponent* UUtilityBlueprintFunctionLibrary::HasParticipantComponent(AActor* Actor, bool& bExecs)
{
	bExecs = false;
	if (!Actor) return nullptr;
	
	if (UParticipantComponent* ParticipantComponent =  Actor->GetComponentByClass<UParticipantComponent>())
	{
		bExecs = true;
		return ParticipantComponent;
	}

	return nullptr;
}
