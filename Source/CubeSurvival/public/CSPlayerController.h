// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/PlayerController.h"
#include "CSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACSPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* aPawn) override;
	
	class UCSHUDWidget* GetHUDWidget() const{ return HUDWidget; }
	void MonsterKill(class ACSMonsterCharacterBase* KilledMonster) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UCSHUDWidget> HUDWidgetclass;
	
private:

	UPROPERTY()
	class UCSHUDWidget* HUDWidget;

	UPROPERTY()
	class ACSPlayerState* CSPlayerState;

	UPROPERTY()
	class UCSPlayerAbility* CSPlayerAbility;
	
};
