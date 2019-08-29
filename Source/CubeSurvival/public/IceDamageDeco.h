// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageDeco.h"

/**
 * 
 */
class CUBESURVIVAL_API FIceDamageDeco :public FDamageDeco
{
public:
	FIceDamageDeco();
	FIceDamageDeco(class FCharacterDamageComponent* InDamageComponent) :FDamageDeco(InDamageComponent) { RemainTimer = 10; }
	~FIceDamageDeco();

	virtual	float GetAttack() override;

	virtual float ContinuousDamage() override;

	UFUNCTION()
	void IceAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* IceDamagedTarget, class FCharacterDamageState* DamageState);

	UFUNCTION()
	void DmageDelete(class AActor* IceReleaseTarget);


private:
	UFUNCTION()
	void IceSlowRelease(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* IceDamagedTarget, class FCharacterDamageState* DamageState);
	/*UFUNCTION()
		void FireDotDamage(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget, class FCharacterDamageState* DamageState);*/

private:
	float IceDamage;
	float OrginSpeed;
	int RemainTimer;
};
