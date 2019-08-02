// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameMode.h"

ACSGameMode::ACSGameMode()
{
	GameStateClass = ACSGameState::StaticClass();
}

void ACSGameMode::BeginPlay()
{
	Super::BeginPlay();
}