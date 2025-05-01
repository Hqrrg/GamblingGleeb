// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScreenBoundingBox.generated.h"

UCLASS()
class GAMBLINGGLEEB_API AScreenBoundingBox : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoundingBoxComponent;

public:
	// Sets default values for this actor's properties
	AScreenBoundingBox();
	
	// Calculate the upper & lower boundaries
	void CalculateBounds(FVector2D& UpperBounds, FVector2D& LowerBounds);
};
