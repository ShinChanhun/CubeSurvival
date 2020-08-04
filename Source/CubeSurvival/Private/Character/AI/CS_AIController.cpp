// Fill out your copyright notice in the Description page of Project Settings.

#include "CS_AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree//BlackboardComponent.h"

const FName ACS_AIController::HomePosKey(TEXT("HomePos"));
const FName ACS_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ACS_AIController::TargetKey(TEXT("Target"));

ACS_AIController::ACS_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBMosterObject(TEXT("BlackboardData'/Game/AI/BB_redmusroom.BB_redmusroom'"));
	if (BBMosterObject.Succeeded())
	{
		BBMonsterAsset = BBMosterObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTMonsterObject(TEXT("BehaviorTree'/Game/AI/BT_redmusroom.BT_redmusroom'"));
	if (BTMonsterObject.Succeeded())
	{
		BTMonsterAsset = BTMonsterObject.Object;
	}
}



void ACS_AIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (UseBlackboard(BBMonsterAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTMonsterAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree"));
		}
	}
}