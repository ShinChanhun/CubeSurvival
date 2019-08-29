// Fill out your copyright notice in the Description page of Project Settings.

#include "CSHUDWidget.h"
#include"Components/ProgressBar.h"
#include"Components/TextBlock.h"
#include"Components/Image.h"
#include"CSPlayerState.h"
#include"CSPlayerAbility.h"
#include "Components/PanelWidget.h"
#include "Styling/SlateBrush.h"

void UCSHUDWidget::BindCharacterStat(UCSPlayerAbility* NewCharacterStat)
{
	CSCHECK(NewCharacterStat != nullptr);
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChange.AddUObject(this, &UCSHUDWidget::UpdateCharacterState);
}
void UCSHUDWidget::BindPlayerState(ACSPlayerState* PlayerState)
{
	CSCHECK(PlayerState != nullptr);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UCSHUDWidget::UpdatePlayerState);
}

void UCSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	CSCHECK(HPBar != nullptr);

	ExpBar= Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	CSCHECK(ExpBar != nullptr);

	PlayerName= Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	CSCHECK(PlayerName != nullptr);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	CSCHECK(PlayerLevel != nullptr);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	CSCHECK(CurrentScore != nullptr);

	HightScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	CSCHECK(HightScore != nullptr);

	SlotNum = 0;
	bSelect = false;
	//Äü ½½·Ô 
	for (int i = 0; i < 15; i++)
	{
		int ImageNum = i+1;
		FString ImageNumStr = FString::FromInt(ImageNum);
		FString ImageName = FString(TEXT("ItemImage_")) + ImageNumStr;
		FName ConvertedFString = FName(*ImageName);	
		class UImage* ItemImage = Cast<UImage>(GetWidgetFromName(ConvertedFString));
		
		CSCHECK(ItemImage != nullptr);
		ItemImageArray.Add(ItemImage);
	
		if (ItemImageArray[i]->Brush.GetResourceName() != NAME_None)
		{
			ItemImageArray[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemImageArray[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	SelectImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemSelectImage")));
	CSCHECK(SelectImage != nullptr);

}

void UCSHUDWidget::LMoveQuickSlot()
{
	SlotNum--;
	if (SlotNum <= -1)
	{
		SlotNum = 14;
	}

	RenderQuickSlot(SlotNum);
}

void UCSHUDWidget::RMoveQuickSlot()
{
	SlotNum++;
	if (SlotNum >= 15)
	{
		SlotNum = 0;
	}
	RenderQuickSlot(SlotNum);
}

void UCSHUDWidget::RenderQuickSlot(int32 InSlotNum)
{
	if (ItemImageArray[InSlotNum]->Brush.GetResourceName() != NAME_None)
	{
		ItemImageArray[InSlotNum]->SetVisibility(ESlateVisibility::Visible);
	}
	SelectImage->SetVisibility(ESlateVisibility::Visible);

	auto PanelWidget = ItemImageArray[InSlotNum]->GetParent();
	PanelWidget->AddChild(SelectImage);
	PanelWidget->AddChild(ItemImageArray[InSlotNum]);
}

void UCSHUDWidget::SelectItem()
{
	if (bSelect == true)
	{
		UImage* Temp = ItemImageArray[SlotNum];
		ItemImageArray[SlotNum] = ItemImageArray[PrevNum];
		ItemImageArray[PrevNum] = Temp;

		auto PrevParent = ItemImageArray[PrevNum]->GetParent();
		auto CurrentParent = ItemImageArray[SlotNum]->GetParent();

		PrevParent->AddChild(ItemImageArray[SlotNum]);
		CurrentParent->AddChild(ItemImageArray[PrevNum]);

		RenderQuickSlot(SlotNum);
		bSelect = false;

	}
	else
	{
		bSelect = true;
		PrevNum = SlotNum;
	}
}

void UCSHUDWidget::UpdateCharacterState()
{
	CSCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void UCSHUDWidget::UpdatePlayerState()
{
	CSCHECK(CurrentPlayerState.IsValid());
	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));

}
