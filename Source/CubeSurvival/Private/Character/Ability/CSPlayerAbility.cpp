// Fill out your copyright notice in the Description page of Project Settings.

#include "CSPlayerAbility.h"
#include "CSGameInstance.h"
#include "CSCharacterStatDataManager.h"



UCSPlayerAbility::UCSPlayerAbility()
{

}

void UCSPlayerAbility::SetNewLevel(int32 NewLevel)
{

	auto CSGameInstance = Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CSCHECK(CSGameInstance != nullptr);

	CurrentPlayerStatData = CSGameInstance->GetCharacterStatDataManager()->GetCSPlayerData(NewLevel);
		//UCSGameInstance::GetGameInstance()->GetCharacterStatDataManager()->GetCSPlayerData(NewLevel);
		//

	if (CurrentPlayerStatData != nullptr)
	{
		Level = NewLevel;
		MaxHP = CurrentPlayerStatData->MaxHP;
		Attack = CurrentPlayerStatData->Attack;
		SetHP(CurrentPlayerStatData->MaxHP);
	}
	else
	{
		CSLOG(Error, TEXT("LEVEL (%d) data donsn't exist"), NewLevel);
	}
	
}