// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameMode.h"
#include "CSPlayerController.h"
#include "CSPlayerCharacter.h"
#include "CSPlayerState.h"
ACSGameMode::ACSGameMode()
{
	PlayerControllerClass = ACSPlayerController::StaticClass();//플레이어 컨트롤 ACSPlayerController로 설정
	DefaultPawnClass = ACSPlayerCharacter::StaticClass();//디폴트 폰 ACSPlayerCharacter로 설정
	PlayerStateClass = ACSPlayerState::StaticClass();//플레이어 스테이트 ACSPlayerState로 설정

	GameStateClass = ACSGameState::StaticClass();
	
	
}

void ACSGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto CSPlayerState = Cast<ACSPlayerState>(NewPlayer->PlayerState);
	CSCHECK(CSPlayerState != nullptr);
	CSPlayerState->InitPlayerData();
}