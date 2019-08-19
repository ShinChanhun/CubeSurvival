// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"

/**
 * 
 */
class CUBESURVIVAL_API FCharacterDamageComponent
{
public:
	FCharacterDamageComponent();
	virtual ~FCharacterDamageComponent();

	virtual	float GetAttack() = 0;
};
