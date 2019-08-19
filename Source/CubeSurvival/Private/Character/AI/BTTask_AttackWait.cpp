// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackWait.h"
#include "CS_AIController.h"
#include "NormalMonsterAnimInstance.h"
#include "CSNormalMonsterCharacter.h"

UBTTask_AttackWait::UBTTask_AttackWait(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "AttackWait";
	WaitTime = 5.0f;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AttackWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	//UE_LOG(LogTemp, Log, TEXT("%f"), MyMemory->RemainingWaitTime);
	return EBTNodeResult::InProgress;
}

void UBTTask_AttackWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto NormalMonster = Cast<ACSNormalMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto NormalMonsterAnim = Cast< UNormalMonsterAnimInstance>(NormalMonster->GetMesh()->GetAnimInstance());
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;
	if (NormalMonsterAnim->GetIsAttackDelayed() == true)
	{
		NormalMonsterAnim->SetIsAttacking(false);
		NormalMonsterAnim->SetIsAttackDelayed(false);
		MyMemory->RemainingWaitTime= FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
		//UE_LOG(LogTemp, Log, TEXT("%f"), MyMemory->RemainingWaitTime);
	}
	if (MyMemory->RemainingWaitTime <= 0.0f)
	{
		// continue execution from this node
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
//
//FString UBTTask_AttackWait::GetStaticDescription() const
//{
//	if (FMath::IsNearlyZero(RandomDeviation))
//	{
//		return FString::Printf(TEXT("%s: %.1fs"), *Super::GetStaticDescription(), WaitTime);
//	}
//	else
//	{
//		return FString::Printf(TEXT("%s: %.1f+-%.1fs"), *Super::GetStaticDescription(), WaitTime, RandomDeviation);
//	}
//}
//
//void UBTTask_AttackWait::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
//{
//	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
//
//	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
//	if (MyMemory->RemainingWaitTime)
//	{
//		Values.Add(FString::Printf(TEXT("remaining: %ss"), *FString::SanitizeFloat(MyMemory->RemainingWaitTime)));
//	}
//}
//
//uint16 UBTTask_AttackWait::GetInstanceMemorySize() const
//{
//	return sizeof(FBTWaitTaskMemory);
//}
//
//#if WITH_EDITOR
//
//FName UBTTask_AttackWait::GetNodeIconName() const
//{
//	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
//}
//
//
//#endif	// WITH_EDITOR

