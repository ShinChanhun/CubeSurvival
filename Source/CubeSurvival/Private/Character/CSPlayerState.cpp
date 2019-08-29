// Fill out your copyright notice in the Description page of Project Settings.

#include "CSPlayerState.h"
#include "CSGameInstance.h"
#include "CSCharacterStatDataManager.h"

ACSPlayerState::ACSPlayerState()
{
	//CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}


void ACSPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("NANA"));
	SetCharacterLevel(5);
	//CharacterLevel = 5;
	GameScore = 0;
}

float ACSPlayerState::GetExpRatio()const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	float Result = (float)Exp / (float)CurrentStatData->NextExp;

	return Result;
}

bool ACSPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
	{
		return false;
	}

	bool DidLevelUp = false;
	Exp = Exp + IncomeExp;
	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}
	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}

void ACSPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto CSGameInstance = Cast<UCSGameInstance>(GetGameInstance());
	CSCHECK(CSGameInstance != nullptr);

	CurrentStatData = CSGameInstance->GetCharacterStatDataManager()->GetCSPlayerData(NewCharacterLevel);
	CSCHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}