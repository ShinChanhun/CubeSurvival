// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Blueprint/UserWidget.h"
#include "CSHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UCSPlayerAbility* NewCharacterStat);
	void BindPlayerState(class ACSPlayerState* PlayerState);
	
	void LMoveQuickSlot();
	void RMoveQuickSlot();
	void RenderQuickSlot(int32 InSlotNum);
	void SelectItem();

	TWeakObjectPtr<class UCSPlayerAbility> GetCharacterAbility() const { return CurrentCharacterStat; }

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterState();
	void UpdatePlayerState();



private:
	TWeakObjectPtr<class UCSPlayerAbility> CurrentCharacterStat;
	TWeakObjectPtr<class ACSPlayerState> CurrentPlayerState;

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* ExpBar;

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* PlayerLevel;

	UPROPERTY()
	class UTextBlock* CurrentScore;

	UPROPERTY()
	class UTextBlock* HightScore;

	UPROPERTY()
	TArray<	class UImage*> ItemImageArray;
	
	UPROPERTY()
	class UImage* SelectImage;

	int32 SlotNum;

	int32 PrevNum;

	bool bSelect;
};
