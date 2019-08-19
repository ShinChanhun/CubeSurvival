// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterDamage.h"

FCharacterDamage::FCharacterDamage()
{
}

FCharacterDamage::FCharacterDamage(float InAttack)
{
	Attack = InAttack;
}

FCharacterDamage::~FCharacterDamage()
{
	CSLOG(Warning, TEXT("~CharacterDamage"));
}

float FCharacterDamage::GetAttack()
{
	CSLOG(Warning, TEXT("CharacterDamage"));
	return Attack;
}