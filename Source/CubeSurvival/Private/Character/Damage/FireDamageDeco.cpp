// Fill out your copyright notice in the Description page of Project Settings.

#include "FireDamageDeco.h"
#include "CSCharacterAbilityManagement.h"

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


float FFireDamageDeco::GetAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget)//노멀 +불+ 지속 데미지 추가
{
	FireAttack(CharacterAbility, FireDamagedTarget);
	return  FDamageDeco::GetAttack() + 5.0f;
}

void FFireDamageDeco::FireDotDamage(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget)
{
	CSLOG(Warning, TEXT("FireDotDamage"));
	CharacterAbility->SetDamage(ContinuousDamage());

	RemainTimer -= 1;
	if (RemainTimer <= 0)
	{
		FireDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
		delete this;

	}
}


void FFireDamageDeco::FireAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget)
{

	FireDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	FTimerDelegate DamageTimerDelegat;
	
	DamageTimerDelegat.BindLambda([this, CharacterAbility, FireDamagedTarget]()->void {
		FireDotDamage(CharacterAbility, FireDamagedTarget);
	});

	FireDamagedTarget->GetWorldTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegat, 0.5f, true, 0.5f);
}


void FFireDamageDeco::DmageRelease(class AActor* FireReleaseTarget)
{
	CSLOG(Warning, TEXT("FireDmageRelease"));
	FireReleaseTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	delete this;
}

