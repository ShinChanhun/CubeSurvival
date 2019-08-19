// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonsterAnimInstance.h"




UNormalMonsterAnimInstance::UNormalMonsterAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	bAttacking = false;
	bDamaged = false;
	bAttackDelayed = false;

}

void UNormalMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!bDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();

	}

}


void UNormalMonsterAnimInstance::AnimNotify_NomalMonsterAttack()
{
	bAttacking = false;
	OnAttackEnd.Broadcast();
}

void UNormalMonsterAnimInstance::AnimNotify_MonsterDamaged()
{
	bDamaged = false;

}

void UNormalMonsterAnimInstance::AnimNotify_AttackHit()
{
	//
	AttackHit.Broadcast();
}