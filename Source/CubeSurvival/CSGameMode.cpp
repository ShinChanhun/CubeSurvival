// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameMode.h"
#include "CSPlayerController.h"
#include "CSPlayerCharacter.h"
#include "CSPlayerState.h"
ACSGameMode::ACSGameMode()
{
	PlayerControllerClass = ACSPlayerController::StaticClass();//�÷��̾� ��Ʈ�� ACSPlayerController�� ����
	DefaultPawnClass = ACSPlayerCharacter::StaticClass();//����Ʈ �� ACSPlayerCharacter�� ����
	PlayerStateClass = ACSPlayerState::StaticClass();//�÷��̾� ������Ʈ ACSPlayerState�� ����

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