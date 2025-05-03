// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ClickableInterface.h"
#include "StrandedGleeb.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShot);

UCLASS()
class GAMBLINGGLEEB_API AStrandedGleeb : public AActor, public IClickableInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* FlipbookComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent = nullptr;
	
public:
	// Sets default values for this actor's properties
	AStrandedGleeb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when clicked
	virtual void Clicked_Implementation(APlayerController* Player) override;

	virtual void GetCrosshairType_Implementation(ECrosshairType& Type) override;

	UPROPERTY(BlueprintAssignable)
	FShot OnShot;

	// Bounding box (for movement)
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Defaults, meta = (ExposeOnSpawn))
	class AScreenBoundingBox* BoundingBox = nullptr;
	
private:
	// Normalized movement vector
	FVector2D MovementDirection;

	// Absolute velocity
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	FVector2D Velocity;

	// Move condition
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	bool CanMove;
};
