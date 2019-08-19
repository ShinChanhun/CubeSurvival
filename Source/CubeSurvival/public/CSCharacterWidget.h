// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Blueprint/UserWidget.h"
#include "CSCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	void BindCharacterStat(class UCSCharacterAbilityManagement* CharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	UPROPERTY()
	class UCSCharacterAbilityManagement* CurrentCharacerStat;

	UPROPERTY()
	class UProgressBar* HPProgerssBar;
	
};
