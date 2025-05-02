// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"

#include "GamblerPawn.generated.h"

UCLASS()
class GAMBLINGGLEEB_API AGamblerPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Root, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* FlipbookComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

public:
	// Sets default values for this actor's properties
	AGamblerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Set up enhanced input component
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Interact input event
	void Interact(const FInputActionValue& Value);
};
