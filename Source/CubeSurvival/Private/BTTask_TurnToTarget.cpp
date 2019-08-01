// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_TurnToTarget.h"
#include "CS_AIController.h"
#include "UNomalMonsterAnimInstance.h"
#include "CSNormalMonsterCharacter.h"
#include "APlayerInputController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto NormalMonster = Cast<ACSNormalMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (NormalMonster == nullptr)
	{

		return EBTNodeResult::Failed;
	}

	auto Target = Cast<AAPlayerInputController>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACS_AIController::TargetKey));
	if (Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - NormalMonster->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	NormalMonster->SetActorRotation(FMath::RInterpTo(NormalMonster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 5.0f));

	return EBTNodeResult::Succeeded;
}