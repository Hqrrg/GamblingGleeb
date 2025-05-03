// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/ParticipantEnum.h"
#include "ParticipantComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBalanceUpdated, float, Balance);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMBLINGGLEEB_API UParticipantComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UParticipantComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
	EParticipant GetParticipantKey();
	
	UFUNCTION(BlueprintPure)
	float GetBalance() const;

	UFUNCTION(BlueprintCallable)
	float AddBalance(float Amount);

	UFUNCTION(BlueprintCallable)
	float SubtractBalance(float Amount);

	UFUNCTION(BlueprintCallable)
	float ResetBalance();
	
	UPROPERTY(BlueprintAssignable)
	FBalanceUpdated OnBalanceUpdated;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	EParticipant ParticipantKey;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float Balance;

	float DefaultBalance;
};
