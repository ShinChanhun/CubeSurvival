// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/GameMode.h"
#include "CSGameState.h"
#include "CSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACSGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	ACSGameMode();

public:

	void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	
public:
	UPROPERTY()
	TWeakObjectPtr<ACSGameState> gs;
};
