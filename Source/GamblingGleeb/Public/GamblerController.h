// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CrosshairTypeEnum.h"
#include "GameFramework/PlayerController.h"
#include "GamblerController.generated.h"

enum class ECrosshairType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrosshairTextureUpdated, UTexture2D*, CrosshairTexture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMousePositionUpdated, FVector2D, ScreenPosition);

UCLASS()
class GAMBLINGGLEEB_API AGamblerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGamblerController();
	
protected:
	// Called when actor is spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	bool LineTraceFromMouse(UPARAM(ref) FHitResult& HitResult, float TraceDistance);

	UFUNCTION(BlueprintPure)
	UTexture2D* GetHoverCrosshairTexture(const ECrosshairType Type);

	UFUNCTION(BlueprintPure)
	UTexture2D* GetClickCrosshairTexture(const ECrosshairType Type);

	UFUNCTION(BlueprintPure)
	FORCEINLINE AActor* GetHovered() { return Hovered; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE ECrosshairType GetCurrentCrosshairType() const { return CurrentCrosshairType; }

	UFUNCTION(BlueprintCallable)
	void UpdateCrosshairTexture(ECrosshairType Type);

	UFUNCTION(BlueprintCallable)
	void UpdateMousePosition();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool& GetLeftMouseButtonDown() { return LeftMouseButtonDown; }

	UPROPERTY(BlueprintAssignable)
	FCrosshairTextureUpdated OnCrosshairTextureUpdated;

	UPROPERTY(BlueprintAssignable)
	FMousePositionUpdated OnMousePositionUpdated;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<ECrosshairType, UTexture2D*> HoverCrosshairTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<ECrosshairType, UTexture2D*> ClickCrosshairTextures;

	FVector2D PreviousMousePosition;

	UPROPERTY()
	AActor* Hovered;
	
	bool LeftMouseButtonDown = false;

	ECrosshairType CurrentCrosshairType;
};
