// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Animation/AnimInstance.h"
#include "UNomalMonsterAnimInstance.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitDelegate);
/**
 *
 */


UCLASS()
class CUBESURVIVAL_API UUNomalMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UUNomalMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	inline void SetIsAttacking(bool IsAttack) { IsAttacking = IsAttack;}
	inline bool GetIsAttacking() { return IsAttacking; }
	inline void SetIsDamaged(bool isdamage) { IsDamaged = isdamage; }
	inline bool GetIsDamaged() { return IsDamaged; }
	inline void SetIsAttackDelayed(bool isDelay) { AttackDelayed = isDelay; }
	inline bool GetIsAttackDelayed() { return AttackDelayed ; }
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
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool AttackDelayed;


};
