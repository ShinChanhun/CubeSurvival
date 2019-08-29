// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"
#include"CS_AIController.h"
#include "CSPlayerCharacter.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"DrawDebugHelpers.h"
#include "CSNormalMonsterCharacter.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn==nullptr)
	{
		return;
	}

	auto NormalMonster = Cast<ACSNormalMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (NormalMonster == nullptr)
	{
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;

	if (World==nullptr)
	{
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(DetectRadius), 
		CollisionQueryParam);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			ACSPlayerCharacter* Player = Cast< ACSPlayerCharacter>(OverlapResult.GetActor());

			if (Player&&Player->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACS_AIController::TargetKey, Player);
				
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				//NormalMonster->Jump(); ����~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				return;
			}
		}
	}
	else
	{
		
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACS_AIController::TargetKey, nullptr);
		//UE_LOG(LogTemp, Log, TEXT("PlayeAttackMontage"));
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}