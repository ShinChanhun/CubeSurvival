// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UCharacterObject.h"
#include "ACharacterBase.h"
#include "AMonsterCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API AAMonsterCharacterBase : public AACharacterBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AAMonsterCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//void MonsterSetting(class AAMonsterCharacterBase* SetCharacter,FString MonsterName , MonsterSize MSSize );
	
	

	UPROPERTY()
		UUCharacterObject* MonsterCharacter;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UFloatingPawnMovement* Movement;
	
	
};
