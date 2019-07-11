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

	void SetJumpFinish(bool setFinish);
	bool GetJumpFinish() const;
	bool GetIsInAir() const;
	bool GetDash() const;
	float GetCurrentPawnSpeed() const;
	void JumpToAttackMontageSection(int32 newSection);

	void SetDash(bool Dash);
	UAnimMontage* GetDashMontage() const;
private:
	UFUNCTION()
		void AnimNotify_AttackHitCheck();

	UFUNCTION()
		void AnimNotify_NextAttackCheck();

	UFUNCTION()
		void AnimNotify_DashEnd();

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



	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DashMontage;



};
