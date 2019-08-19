// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSCharacterAbilityManagement.h"
#include "CSPlayerAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSPlayerAbility : public UCSCharacterAbilityManagement
{
	GENERATED_BODY()
	
	
public:
	UCSPlayerAbility();
	void SetNewLevel(int32 NewLevel);

private:
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	FCSPlayerStatData* CurrentPlayerStatData;
	
};
