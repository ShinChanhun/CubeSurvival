// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSMonsterCharacterBase.h"
#include "CSNormalMonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACSNormalMonsterCharacter : public ACSMonsterCharacterBase
{
	GENERATED_BODY()
public:
		ACSNormalMonsterCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	/*UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*UPROPERTY()
		class UUNomalMonsterAnimInstance* MonsterAnim;*/

	void AttackCheck();


	virtual void MonsterSpawn(AActor* Owner, FVector Orgin, float LimitSizeX, float LimitSizeY, int MonsterNum, bool bRndRot) override;
public:

private:
	
	UPROPERTY()
	class UUNomalMonsterAnimInstance* NormalMonsterAnim;
};
