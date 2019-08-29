// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{

	CurrentPawnSpeed = 0.0f;

	AnimationSpeed = 1.0f;
	bInAir = false;
	bJumpFinish = false;
	bDash = false;
	bDamaged = false;
	bDead = false;

	//리소스가 더 많아지면 관리할것 2개가지고는 굳이 만들 필요는 없다고 봄. int로 만들어진 다른 2개의 변수가 있다고 해서 map이나 vector로 관리 안하는 것 처럼
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Model/Player/Nana/Animations/Attack_Montage.Attack_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Dash_MONTAGE(TEXT("AnimMontage'/Game/Model/Player/Nana/Animations/Nana_Dash_Montage.Nana_Dash_Montage'"));
	if (Dash_MONTAGE.Succeeded())
	{
		DashMontage = Dash_MONTAGE.Object;
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!bDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			bInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}


void UPlayerAnimInstance::PlayeAttackMontage()
{
	CSCHECK(!bDead);

	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, AnimationSpeed);
	}
}

void UPlayerAnimInstance::PlayDashMontage()
{
	CSCHECK(!bDead);
	if (!Montage_IsPlaying(DashMontage))
	{
		Montage_Play(DashMontage, AnimationSpeed+0.5f);
	}
}


void UPlayerAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_DashEnd()
{
	OnDash.Broadcast();
}


void UPlayerAnimInstance::AnimNotify_Damaged()
{
	//UE_LOG(LogTemp, Log, TEXT("Null3"));
	CSCHECK(!bDead);
	bDamaged = false;
}

FName UPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	CSCHECK(FMath::IsWithinInclusive(Section, 1, 4), NAME_None);

	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void  UPlayerAnimInstance::JumpToAttackMontageSection(int32 newSection)
{
	CSCHECK(Montage_IsPlaying(AttackMontage));

	Montage_JumpToSection(GetAttackMontageSectionName(newSection), AttackMontage);

}




