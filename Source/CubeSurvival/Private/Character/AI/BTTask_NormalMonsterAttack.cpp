// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_NormalMonsterAttack.h"
#include "CS_AIController.h"
#include "NormalMonsterAnimInstance.h"
#include "CSNormalMonsterCharacter.h"
//#include"GameFramework/Actor.h"

UBTTask_NormalMonsterAttack::UBTTask_NormalMonsterAttack()
{
	bNotifyTick = true;
	bAttacking = false;
	
}

EBTNodeResult::Type UBTTask_NormalMonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto NormalMonster = Cast<ACSNormalMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto NormalMonsterAnim = Cast< UNormalMonsterAnimInstance>(NormalMonster->GetMesh()->GetAnimInstance());
	//UUNomalMonsterAnimInstance
	if (NormalMonster == nullptr || NormalMonsterAnim == nullptr)
	{

		return EBTNodeResult::Failed;
	}

	if (NormalMonsterAnim->GetIsAttackDelayed() == true)
	{
		NormalMonsterAnim->SetIsAttacking(false);
		bAttacking = false;
	}
	else
	{
		NormalMonsterAnim->SetIsAttacking(true);
		bAttacking = true;
		//NormalMonster->Attack();
		NormalMonsterAnim->OnAttackEnd.AddLambda([this]()->void
		{
			bAttacking = false;
		});
	}

	return EBTNodeResult::InProgress;

}

void UBTTask_NormalMonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto NormalMonster = Cast<ACSNormalMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto NormalMonsterAnim = Cast< UNormalMonsterAnimInstance>(NormalMonster->GetMesh()->GetAnimInstance());

	if (!bAttacking || NormalMonsterAnim->GetIsAttackDelayed() == true)
	{

		NormalMonsterAnim->SetIsAttacking(false);
		bAttacking = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	//else if ()
	//{
	//	NormalMonsterAnim->SetIsAttackDelayed(false);
	//}

}

