// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/PlayerState.h"
#include "CSPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACSPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ACSPlayerState();

	int32 GetGameScore() const { return GameScore; }
	int32 GetCharacterLevel() const { return CharacterLevel; }
	float GetExpRatio()const;
	bool AddExp(int32 IncomeExp);

	void InitPlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 Exp;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FCSPlayerStatData* CurrentStatData;
	
};
