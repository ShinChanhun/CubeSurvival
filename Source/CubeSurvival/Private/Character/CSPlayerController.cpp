// Fill out your copyright notice in the Description page of Project Settings.

#include "CSPlayerController.h"
#include "CSHUDWidget.h"
#include "CSPlayerState.h"
#include "CSMonsterCharacterBase.h"
#include "CSPlayerAbility.h"
ACSPlayerController::ACSPlayerController()
{
	static ConstructorHelpers::FClassFinder<UCSHUDWidget> UI_HUD_C(TEXT("WidgetBlueprint'/Game/UI/UI_HUD.UI_HUD_C'"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetclass = UI_HUD_C.Class;
	}	
}

void ACSPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
 }

void ACSPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);
 }

void ACSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	HUDWidget = CreateWidget<UCSHUDWidget>(this, HUDWidgetclass);
	HUDWidget->AddToViewport();


	CSPlayerState = Cast<ACSPlayerState>(PlayerState);
	CSCHECK(CSPlayerState != nullptr);
	HUDWidget->BindPlayerState(CSPlayerState);
	CSPlayerState->OnPlayerStateChanged.Broadcast();
}


void ACSPlayerController::MonsterKill(class ACSMonsterCharacterBase* KilledMonster) const
{
	if (CSPlayerState->AddExp(KilledMonster->GetExp()) == true)//레벨업을 했을 경우 true로 반환
	{
		CSCHECK(HUDWidget->GetCharacterAbility() != nullptr);
		HUDWidget->GetCharacterAbility()->SetNewLevel(CSPlayerState->GetCharacterLevel());
		
	}
}