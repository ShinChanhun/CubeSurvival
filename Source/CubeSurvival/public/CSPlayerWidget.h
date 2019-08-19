// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Blueprint/UserWidget.h"
#include "CSPlayerWidget.generated.h"

/**
 * 
 */
///////////////////���߿� CSCharacterWidget�� ��� �޾Ƽ� ���
UCLASS()
class CUBESURVIVAL_API UCSPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	void BindCharacterStat(class UCSPlayerAbility* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();


private:
	TWeakObjectPtr< class UCSPlayerAbility> CurrentCharacterStat;

	
	UPROPERTY()
	class UProgressBar* HPProgerssBar;

};
