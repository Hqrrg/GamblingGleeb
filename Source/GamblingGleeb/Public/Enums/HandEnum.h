// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HandEnum.generated.h"

UENUM(BlueprintType)
enum class EHand : uint8
{
	None,
	Rock,
	Paper,
	Scissors
};