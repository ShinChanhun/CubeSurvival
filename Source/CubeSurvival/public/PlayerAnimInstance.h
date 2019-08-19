// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDashDelegate);
/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayeAttackMontage();
	void PlayDashMontage();
	void JumpToAttackMontageSection(int32 newSection);

	inline void SetJumpFinish(bool InbJumpFinish) { bJumpFinish = InbJumpFinish; }
	inline bool GetJumpFinish() const { return bJumpFinish; }

	inline bool GetInAir() const { return bInAir; }

	inline void SetDash(bool InbDash) { bDash = InbDash; }
	inline bool GetDash() const { return bDash; }

	inline void SetDamage(bool InbDamaged) { bDamaged = InbDamaged; }
	inline bool GetDamage() const { return bDamaged; }

	inline void DeadAnim() { bDead = true; }
	inline bool GetDead() { return bDead; }

	inline float GetCurrentPawnSpeed() const { return CurrentPawnSpeed; }
	inline UAnimMontage* GetDashMontage() const { return DashMontage; }

private:
	UFUNCTION()
		void AnimNotify_AttackHitCheck();

	UFUNCTION()
		void AnimNotify_NextAttackCheck();

	UFUNCTION()
		void AnimNotify_DashEnd();

	UFUNCTION()
		void AnimNotify_Damaged();

	FName GetAttackMontageSectionName(int32 Section);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnDashDelegate OnDash;

	UPROPERTY(EditAnywhere,  Category = Pawn, Meta = (AllowPrivateAccess = true))
		float DashSpeed;

private:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bJumpFinish;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DashMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDead;


	
	
	
};
