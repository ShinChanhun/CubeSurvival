// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/GameState.h"
#include "MapManager.h"
#include "CSGameState.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACSGameState : public AGameState
{
	GENERATED_BODY()
	ACSGameState();
	
	
	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<UMapManager> MapManager;
};
