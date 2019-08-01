// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AMonsterCharacterBase.h"
#include "ANormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API AANormalMonster : public AAMonsterCharacterBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AANormalMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void MonsterSetting(FString MonsterName = "NoName", MonsterSize MSSize = MonsterSize::MS_Small, class TSubclassOf<AACharacterBase> SetCharacter ) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	inline void SetTurnRot(FRotator Rot) { TurnRot = Rot; }
	inline void SetIsTurn(bool isturn) { IsTurn = isturn; }

public:
	float timede;

private:
	bool IsTurn;
	FRotator TurnRot;
	
	
};
