// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityBlueprintFunctionLibrary.generated.h"

class UParticipantComponent;
/**
 * 
 */
UCLASS()
class GAMBLINGGLEEB_API UUtilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "bExecs"))
	static UParticipantComponent* HasParticipantComponent(AActor* Actor, bool& bExecs);
};
