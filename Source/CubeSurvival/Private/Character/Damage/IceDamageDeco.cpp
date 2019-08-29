// Fill out your copyright notice in the Description page of Project Settings.

#include "IceDamageDeco.h"
#include "CSCharacterAbilityManagement.h"
#include "CharacterDamageState.h"
#include "PlayerAnimInstance.h"
#include "CSPlayerCharacter.h"

FIceDamageDeco::FIceDamageDeco()
{
	IceDamage = 100.0f;
}

FIceDamageDeco::~FIceDamageDeco()
{
}
float FIceDamageDeco::GetAttack()
{
	return  FDamageDeco::GetAttack() + 5.0f;
}

float FIceDamageDeco::ContinuousDamage()
{
	return  IceDamage;
}
void FIceDamageDeco::IceSlowRelease(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* IceDamagedTarget, class FCharacterDamageState* DamageState)
{
	CharacterAbility->SetSpeed(OrginSpeed);
	DamageState->ReleaseDamage(EDamageState::IceState);
	CSLOG(Warning, TEXT("IceSlow"));
	DmageDelete(IceDamagedTarget);
/*	IceDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);

	delete this;*/	
}
//TODO: 아이스 데미지 확인
void FIceDamageDeco::IceAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* IceDamagedTarget, class FCharacterDamageState* DamageState)
{
	IceDamagedTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	OrginSpeed = CharacterAbility->GetSpeed();
	CharacterAbility->SetSpeed(ContinuousDamage());

	ACSPlayerCharacter* Player = Cast<ACSPlayerCharacter >(IceDamagedTarget);
	auto PlayerAnim = Cast<UPlayerAnimInstance>(Player->GetMesh()->GetAnimInstance());
	PlayerAnim->SetAnimationSpeed(0.2f);

	FTimerDelegate DamageTimerDelegat;
	CSLOG(Warning, TEXT("IceDamage"));

	DamageTimerDelegat.BindLambda([this, CharacterAbility, IceDamagedTarget, DamageState, PlayerAnim]()->void {
		PlayerAnim->SetAnimationSpeed(1.0f);
		IceSlowRelease(CharacterAbility, IceDamagedTarget, DamageState);
	});
	//TODO: 비율 확인
	IceDamagedTarget->GetWorldTimerManager().SetTimer(DamageTimerHandle, DamageTimerDelegat, 4.0f,false);
}


void FIceDamageDeco::DmageDelete(class AActor* IceReleaseTarget)
{
	CSLOG(Warning, TEXT("IceDmageRelease"));
	IceReleaseTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	delete this;
}