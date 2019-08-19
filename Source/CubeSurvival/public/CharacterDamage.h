// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterDamageComponent.h"

/**
 * 
 */
class CUBESURVIVAL_API FCharacterDamage:public FCharacterDamageComponent
{
public:
	FCharacterDamage();
	FCharacterDamage(float InAttack);
	~FCharacterDamage();

	virtual	float GetAttack() override;
	float Attack = 0.0f;
private:
	
};
