// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageDeco.h"

/**
 * 
 */
class CUBESURVIVAL_API FFireDamageDeco :public FDamageDeco
{
public:
	FFireDamageDeco();
	FFireDamageDeco(class FCharacterDamageComponent* InDamageComponent) :FDamageDeco(InDamageComponent) { RemainTimer = 10; }
	~FFireDamageDeco();

	virtual	float GetAttack() override;

	virtual float ContinuousDamage() override;

	UFUNCTION()
	float GetAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget);	

	UFUNCTION()
	void FireAttack(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget);

	UFUNCTION()
	void DmageRelease(class AActor* FireReleaseTarget);

private:
	UFUNCTION()
	void FireDotDamage(class UCSCharacterAbilityManagement* CharacterAbility, class AActor* FireDamagedTarget);
	
private:
	float FireDamage;
	int RemainTimer;
};
