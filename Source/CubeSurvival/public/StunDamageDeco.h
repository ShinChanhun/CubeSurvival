// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageDeco.h"


/**
 * 
 */
class CUBESURVIVAL_API FStunDamageDeco :public FDamageDeco
{
public:
	FStunDamageDeco();
	FStunDamageDeco(class FCharacterDamageComponent* InDamageComponent) :FDamageDeco(InDamageComponent) { RemainTimer = 10; }
	~FStunDamageDeco();

	virtual	float GetAttack() override;

	virtual float ContinuousDamage() override;

	UFUNCTION()
	void StunAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* StunDamagedTarget, class FCharacterDamageState* DamageState);

	UFUNCTION()
	void DmageDelete(class AActor* StunReleaseTarget);

private:

private:
	float StunDamage;
	int RemainTimer;
};
