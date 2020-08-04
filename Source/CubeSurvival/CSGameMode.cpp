// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameMode.h"
#include "CSPlayerController.h"
#include "CSPlayerCharacter.h"
ACSGameMode::ACSGameMode()
{
	PlayerControllerClass = ACSPlayerController::StaticClass();
	DefaultPawnClass = ACSPlayerCharacter::StaticClass();
	GameStateClass = ACSGameState::StaticClass();
}

void ACSGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}