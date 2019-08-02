// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

#define CUBE_SIZE 150

DECLARE_LOG_CATEGORY_EXTERN(CubeSurvival, Log, All);
#define CSLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define CSLOG_S(Verbosity) UE_LOG(CubeSurvival, Verbosity, TEXT("%s"), *CSLOG_CALLINFO)
#define CSLOG(Verbosity, Format, ...) UE_LOG(CubeSurvival, Verbosity, TEXT("%s %s"), *CSLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))