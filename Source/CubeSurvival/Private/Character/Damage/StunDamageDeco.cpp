// Fill out your copyright notice in the Description page of Project Settings.

#include "StunDamageDeco.h"
#include "CSCharacterAbilityManagement.h"
#include "CharacterDamageState.h"
#include "PlayerAnimInstance.h"
#include "CSPlayerCharacter.h"

FStunDamageDeco::FStunDamageDeco()
{
	StunDamage = 2.0f;
}

FStunDamageDeco::~FStunDamageDeco()
{
}
float FStunDamageDeco::GetAttack()
{
	return  FDamageDeco::GetAttack() + 5.0f;
}

float FStunDamageDeco::ContinuousDamage()
{
	return  StunDamage;
}

void FStunDamageDeco::StunAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* StunDamagedTarget, class FCharacterDamageState* DamageState)
{
	ACSPlayerCharacter* Player = Cast<ACSPlayerCharacter >(StunDamagedTarget);
	Player->bStun = true;

	FTimerDelegate DamageTimerDelegat;
	CSLOG(Warning, TEXT("StunAttack"));

	DamageTimerDelegat.BindLambda([this, StunDamagedTarget, DamageState, Player ]()->void {
		Player->bStun = false;
		DamageState->ReleaseDamage(EDamageState::StunState);
		//StunDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);	
		DmageDelete(StunDamagedTarget);
	});

	//TODO: 비율 확인
	StunDamagedTarget->GetWorldTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegat, 1.5f, false);
	
}

void FStunDamageDeco::DmageDelete(class AActor* StunReleaseTarget)
{
	StunReleaseTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	delete this;
}

