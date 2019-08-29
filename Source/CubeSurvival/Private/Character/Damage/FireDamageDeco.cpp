// Fill out your copyright notice in the Description page of Project Settings.

#include "FireDamageDeco.h"
#include "CSCharacterAbilityManagement.h"
#include "CharacterDamageState.h"
FFireDamageDeco::FFireDamageDeco()
{
	CSLOG(Warning, TEXT("FireDamageDeco"));
	FireDamage = 2.0f;
	RemainTimer = 30;
}

FFireDamageDeco::~FFireDamageDeco()
{
	CSLOG(Warning, TEXT("~FireDamageDeco"));
}

float FFireDamageDeco::ContinuousDamage()
{
	CSLOG(Warning, TEXT("FireDamageDecoContinuousDamage"));
	return FireDamage;
}

float FFireDamageDeco::GetAttack()//노멀 +불 데미지
{
	//데미지 지속 데미지 추가
	CSLOG(Warning, TEXT("SFireDamageDeco GetAttack"));
	return  FDamageDeco::GetAttack() + 5.0f;
}

//
//float FFireDamageDeco::GetAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget)//노멀 +불+ 지속 데미지 추가
//{
//	FireAttack(CharacterAbility, FireDamagedTarget);
//	return  FDamageDeco::GetAttack() + 5.0f;
//}

void FFireDamageDeco::FireDotDamage(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget, class FCharacterDamageState* DamageState)
{
	CSLOG(Warning, TEXT("FireDotDamage"));
	CharacterAbility->SetDamage(ContinuousDamage());

	RemainTimer -= 1;
	if (RemainTimer <= 0)
	{
		DamageState->ReleaseDamage(EDamageState::FireState);
		DmageDelete(FireDamagedTarget);
		/*FireDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);	
		delete this;*/

	}
}


void FFireDamageDeco::FireAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget, class FCharacterDamageState* DamageState)
{

	FireDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	FTimerDelegate DamageTimerDelegat;
	
	DamageTimerDelegat.BindLambda([this, CharacterAbility, FireDamagedTarget, DamageState]()->void {
		FireDotDamage(CharacterAbility, FireDamagedTarget, DamageState);
	});

	FireDamagedTarget->GetWorldTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegat, 0.5f, true, 0.5f);//0.5초 마다 불려온다. 총 불려오는 수는 30번.(RemainTimer=30)
}


void FFireDamageDeco::DmageDelete(class AActor* FireReleaseTarget)
{
	CSLOG(Warning, TEXT("FireDmageRelease"));
	FireReleaseTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	delete this;
}
