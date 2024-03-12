// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(BuildingEscape, Log, All);

#define BELOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define BELOG_S(Verbosity) UE_LOG(BuildingEscape, Verbosity, TEXT("%s"), *BELOG_CALLINFO)
#define BELOG(Verbosity, Format, ...) UE_LOG(BuildingEscape, Verbosity, TEXT("%s %s"), *BELOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))