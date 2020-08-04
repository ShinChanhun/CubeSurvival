// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSCharacterAbilityManagement.h"
#include "CSMonsterrAbility.generated.h"

/**
 *
 */
UCLASS()
class CUBESURVIVAL_API UCSMonsterrAbility : public UCSCharacterAbilityManagement
{
	GENERATED_BODY()

public:

	UCSMonsterrAbility();

	UFUNCTION()
	void SetMonsterName(FString InMonsterName);

private:
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	FString MonsterName;
	FCSMonsterStatData* CurrentMonsterStatData;

};
