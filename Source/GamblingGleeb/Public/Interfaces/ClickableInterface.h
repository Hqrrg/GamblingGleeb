// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClickableInterface.generated.h"

enum class ECrosshairType : uint8;

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UClickableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMBLINGGLEEB_API IClickableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Clicked(APlayerController* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetCrosshairType(ECrosshairType& Type);
};
