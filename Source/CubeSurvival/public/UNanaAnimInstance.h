// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Animation/AnimInstance.h"
#include "UNanaAnimInstance.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDashDelegate);
/**
 *
 */
UCLASS()
class CUBESURVIVAL_API UUNanaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UUNanaAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayeAttackMontage();
	void PlayDashMontage();
	void JumpToAttackMontageSection(int32 newSection);

	inline void SetJumpFinish(bool setFinish) { IsJumpFinish = setFinish; }
	inline bool GetJumpFinish() const { return IsJumpFinish; }

	inline bool GetIsInAir() const { return IsInAir; }

	inline void SetDash(bool Dash) { IsDash = Dash; }
	inline bool GetDash() const { return IsDash; }

	inline void SetDamage(bool isDamaged) { IsDamaged = isDamaged; }
	inline bool GetDamage() const { return IsDamaged; }

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float DashSpeed;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsJumpFinish;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDamaged;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DashMontage;



};
