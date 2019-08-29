// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterDamageComponent.h"

/**
 * 
 */
class CUBESURVIVAL_API FDamageDeco :public FCharacterDamageComponent
{
public:
	FDamageDeco();
	FDamageDeco(FCharacterDamageComponent* InDamageComponent):DamgeComponent(InDamageComponent){}
	~FDamageDeco();

	virtual float GetAttack()override;

	virtual float ContinuousDamage();//지속 데미지 도트, 슬로우, 스턴

	UFUNCTION()
	virtual	void DmageRelease(class AActor* FireReleaseTarget);

public:

protected:
	FTimerHandle DamageTimerHandle;
private:
	FCharacterDamageComponent* DamgeComponent=nullptr;
};
