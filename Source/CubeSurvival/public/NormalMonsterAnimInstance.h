// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Animation/AnimInstance.h"
#include "NormalMonsterAnimInstance.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitDelegate);
/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UNormalMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UNormalMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	inline void SetIsAttacking(bool InbAttack) { bAttacking = InbAttack; }
	inline bool GetIsAttacking() const { return bAttacking; }
	inline void SetIsDamaged(bool InbDamage) { bDamaged = InbDamage; }
	inline bool GetIsDamaged() const { return bDamaged; }
	inline void SetIsAttackDelayed(bool InbAttackDelay) { bAttackDelayed = InbAttackDelay; }
	inline bool GetIsAttackDelayed() const { return bAttackDelayed; }
	inline void DeadAnim() { bDead = true; }
	inline bool GetIsDead() { return bDead; }
private:
	UFUNCTION()
		void AnimNotify_NomalMonsterAttack();

	UFUNCTION()
		void AnimNotify_MonsterDamaged();


	UFUNCTION()
		void AnimNotify_AttackHit();
public:
	FOnAttackEndDelegate OnAttackEnd;
	FOnAttackHitDelegate AttackHit;
	FTimerHandle DelayTimer;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bAttackDelayed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDead;
	
	
};
