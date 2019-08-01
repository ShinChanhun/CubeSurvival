// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindPatrol.h"
#include "CSNormalMonsterCharacter.h"
//#include "ANormalMonster.h"
#include "CS_AIController.h"
#include"BehaviorTree/BlackboardComponent.h"


UBTTask_FindPatrol::UBTTask_FindPatrol()
{
	NodeName = TEXT("PatrolPos");
	
}

EBTNodeResult::Type UBTTask_FindPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Resut = Super::ExecuteTask(OwnerComp, NodeMemory);
	// Cast<ACSNormalMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	//auto Monster =OwnerComp.GetAIOwner()->GetPawn();
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		
		return EBTNodeResult::Failed;
	}

	UNavigationSystem* NavSystem = UNavigationSystem::GetNavigationSystem(ControllingPawn->GetWorld());
	//UNavMovementComponent* tes=Cast<
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FVector Orgin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ACS_AIController::HomePosKey);
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(ControllingPawn->GetActorLocation(), 700.0f, NextPatrol))
	{
		//FVector forword = (Monster->GetActorLocation() - NextPatrol.Location);
		//forword.Z = 0.0f;
		//FRotator rot = FRotationMatrix::MakeFromX(forword).Rotator();
		//Monster->SetActorRotation(rot);
		//Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(), rot, GetWorld()->GetDeltaSeconds(), 2.0f));


		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ACS_AIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
 }