// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Blueprint/UserWidget.h"
#include "CSMonsterWidget.generated.h"

/**
 *
 */
 ///////////////////���߿� CSCharacterWidget�� ��� �޾Ƽ� ���
UCLASS()
class CUBESURVIVAL_API UCSMonsterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindMonsterStat(class UCSMonsterrAbility* MonsterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	UPROPERTY()
	class UCSMonsterrAbility* CurrenMonsterStat;

	UPROPERTY()
	class UProgressBar* HPProgerssBar;
};
