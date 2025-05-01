// Fill out your copyright notice in the Description page of Project Settings.


#include "GamblerPawn.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GamblerController.h"
#include "Interfaces/ClickableInterface.h"


// Sets default values
AGamblerPawn::AGamblerPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	RootComponent = FlipbookComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AGamblerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add default mapping context
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Set up enhanced input component
void AGamblerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AGamblerPawn::Interact);
	}
}

// Interact input event
void AGamblerPawn::Interact(const FInputActionValue& Value)
{
	if (AGamblerController* GamblerController = Cast<AGamblerController>(Controller))
	{
		if (AActor* Hovered = GamblerController->GetHovered())
		{
			// Implements instead of cast for blueprint compatability
			if (Hovered->Implements<UClickableInterface>())
			{
				IClickableInterface::Execute_Clicked(Hovered, GamblerController);
			}
		}
	}
}

