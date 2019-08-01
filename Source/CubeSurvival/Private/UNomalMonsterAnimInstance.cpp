// Fill out your copyright notice in the Description page of Project Settings.

#include "UNomalMonsterAnimInstance.h"

UUNomalMonsterAnimInstance::UUNomalMonsterAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsAttacking = false;
	IsDamaged = false;
	AttackDelayed = false;

}

void UUNomalMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	
}


void UUNomalMonsterAnimInstance::AnimNotify_NomalMonsterAttack()
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void UUNomalMonsterAnimInstance::AnimNotify_MonsterDamaged()
{
	IsDamaged = false;

}

void UUNomalMonsterAnimInstance::AnimNotify_AttackHit()
{
	//
	AttackHit.Broadcast();
}