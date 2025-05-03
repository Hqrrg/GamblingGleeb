// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParticipantEnum.generated.h"

UENUM(BlueprintType)
enum class EParticipant : uint8
{
	None,
	Player,
	Computer
};