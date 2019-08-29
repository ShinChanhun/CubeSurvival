// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CubeSurvival.h"

#include "GameFramework/Character.h"
#include "CharacterDamageState.h"
#include "CSPlayerCharacter.generated.h"


/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API ACSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ACSPlayerCharacter();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;	
	
	void KnockBack(FVector HitLocation);
	void SetCharacterSceneState(ECharacterState NewState);
	ECharacterState GetCharacterState() const {	return CurrentState;}
	
	void SetCharacterDamageState(class FCharacterDamageState* InCharacterDamgeState, int DamgeState,...);

	class UCSPlayerAbility* GetPlayerAbility() const { return PlayerAbility; }
	
	inline bool GetInvincibility() const { return bInvincibility; }
protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);




	void ZoomIn();
	void ZoomOut();
	void Jump();
	void Attatck();
	void Dash();

	void RSlotMove();
	void LSlotMove();
	void ItemSelect();

	

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void PlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void OnCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetControlMode(int32 controlMode);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	void ChangeInvincibility();


public:
	UPROPERTY()
	class UCharacterResourceManager* PlayerResource;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	float CameraZoom;

	UPROPERTY(EditAnywhere, Category = Stat)
	float CharacterSpeed;

	UPROPERTY(EditAnywhere, Category = Stat)
	float DashSpeed;

	UPROPERTY(EditAnywhere, Category = Stat)
	bool bStun;
	

	/*UPROPERTY(VisibleAnywhere, Category = Stat)
		class UCSCharacterStatComponent* PlayerStat;*/

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY()
	class UCSGameInstance* CSGameInstance;
	

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bComboIntpuOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bDash;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Damage, Meta = (AllowPrivateAccess = true))
	bool bDamaged;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Damage, Meta = (AllowPrivateAccess = true))
	bool bInvincibility;

	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovements;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UCSPlayerAbility* PlayerAbility;

	


	//TArray< enum ECharacterDamageState> CharacterStateArry;

	FTimerHandle Timer;

private:
	//TMap<enum ECharacterDamageState, class FDamageDeco* > CharacterStateDamage;
	//TArray<class FCharacterDamageState*> CharacterDamageStateArry;
	//class FCharacterDamageState* CharacterDamageState;

	TMap<enum EDamageState, class FCharacterDamageState*  > CharacterStateDamage;

	UPROPERTY(Transient,VisibleInstanceOnly, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	ECharacterState CurrentState;

	UPROPERTY()
	class ACSPlayerController* CSPlayerController;

};
