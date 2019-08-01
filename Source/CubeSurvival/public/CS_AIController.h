// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "AIController.h"
#include "CS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACS_AIController : public AAIController
{
	GENERATED_BODY()
public:
		ACS_AIController();
	virtual void Possess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:


	UPROPERTY()
	class UBehaviorTree* BTMonsterAsset;
	UPROPERTY()
	class UBlackboardData* BBMonsterAsset;

	
	
};
