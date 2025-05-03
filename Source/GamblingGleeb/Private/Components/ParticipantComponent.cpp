// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ParticipantComponent.h"


// Sets default values for this component's properties
UParticipantComponent::UParticipantComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Balance = 100.f;
	DefaultBalance = Balance;
	ParticipantKey = EParticipant::None;
}


// Called when the game starts
void UParticipantComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultBalance = Balance;
}

EParticipant UParticipantComponent::GetParticipantKey()
{
	return ParticipantKey;
}

float UParticipantComponent::GetBalance() const
{
	return Balance;
}

float UParticipantComponent::AddBalance(float Amount)
{
	Balance+=Amount;
	OnBalanceUpdated.Broadcast(Balance);
	return Balance;
}

float UParticipantComponent::SubtractBalance(float Amount)
{
	Balance-=Amount;
	OnBalanceUpdated.Broadcast(Balance);
	return Balance;
}

float UParticipantComponent::ResetBalance()
{
	Balance=DefaultBalance;
	OnBalanceUpdated.Broadcast(Balance);
	return Balance;
}

