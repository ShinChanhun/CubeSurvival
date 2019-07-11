// Fill out your copyright notice in the Description page of Project Settings.

#include "UNanaAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

UUNanaAnimInstance::UUNanaAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsJumpFinish = false;
	IsDash = false;
	DashSpeed = 1.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Model/Player/Nana/Animations/Attack_Montage.Attack_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
	//DashMontage

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Dash_MONTAGE(TEXT("AnimMontage'/Game/Model/Player/Nana/Animations/Nana_Dash_Montage.Nana_Dash_Montage'"));
	if (Dash_MONTAGE.Succeeded())
	{
		DashMontage = Dash_MONTAGE.Object;
	}
}

void UUNanaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

float UUNanaAnimInstance::GetCurrentPawnSpeed() const
{
	return CurrentPawnSpeed;
}

void UUNanaAnimInstance::PlayeAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UUNanaAnimInstance::PlayDashMontage()
{
	if (!Montage_IsPlaying(DashMontage))
	{
		Montage_Play(DashMontage, 1.5f);
	}
}

bool UUNanaAnimInstance::GetIsInAir() const
{
	return IsInAir;
}

void UUNanaAnimInstance::SetJumpFinish(bool setFinish)
{
	IsJumpFinish = setFinish;
}


bool UUNanaAnimInstance::GetJumpFinish() const
{
	return IsJumpFinish;
}

void UUNanaAnimInstance::SetDash(bool Dash)
{
	IsDash = Dash;
}

bool UUNanaAnimInstance::GetDash() const
{
	return IsDash;
}

UAnimMontage* UUNanaAnimInstance::GetDashMontage() const
{
	return DashMontage;
}


void UUNanaAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UUNanaAnimInstance::AnimNotify_NextAttackCheck()
{
	//UE_LOG(LogTemp, Log, TEXT("AnimNoftify_NextAttackCheck"));
	OnNextAttackCheck.Broadcast();
}


void UUNanaAnimInstance::AnimNotify_DashEnd()
{
	OnDash.Broadcast();
}


FName UUNanaAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	CSCHECK(FMath::IsWithinInclusive(Section, 1, 4), NAME_None);

	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void  UUNanaAnimInstance::JumpToAttackMontageSection(int32 newSection)
{
	CSCHECK(Montage_IsPlaying(AttackMontage));
	//if (!Montage_IsPlaying(AttackMontage))
	{
		//UE_LOG(LogTemp, Log, TEXT("%s"), *GetAttackMontageSectionName(newSection).ToString());
		// FName(*FString::Printf(TEXT("Attack%d")
		//	Montage_JumpToSection(GetAttackMontageSectionName(newSection), AttackMontage);
		Montage_JumpToSection(GetAttackMontageSectionName(newSection), AttackMontage);
	}
}
