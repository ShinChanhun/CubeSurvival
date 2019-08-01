// Fill out your copyright notice in the Description page of Project Settings.

#include "APlayerInputController.h"
#include "UCharacterObject.h"
#include "UNanaAnimInstance.h"
#include "AWeaponActor.h"
#include "DrawDebugHelpers.h"
#include "UNomalMonsterAnimInstance.h"
#include "CSNormalMonsterCharacter.h"
// Sets default values
AAPlayerInputController::AAPlayerInputController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCharacter = CreateDefaultSubobject<UUCharacterObject>(TEXT("PlayerModel"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterMovements = Cast<UCharacterMovementComponent>(GetCharacterMovement());

	SpringArm->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	CameraZoom = 700.0f;
	SetControlMode(0);
	SpringArm->TargetArmLength = CameraZoom;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	//PlayerCharacter->GetMonsterMesh()[TEXT("02020002_m_redmushroom")];

	if (PlayerCharacter != NULL)
	{
		GetMesh()->SetSkeletalMesh(PlayerCharacter->GetPlayerMesh());
		GetMesh()->SetRelativeLocationAndRotation(FVector4(0.0f, 0.0f, -88.0f), FRotator(0.0f, 270.0f, 0.0f));
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(PlayerCharacter->GetPlayerAnimClass());
	}
	//test = PlayerCharacter->Weapon;
	//this->Tags.AddUnique(TEXT("Player"));
	GetCapsuleComponent()->ComponentTags.AddUnique(TEXT("Player"));
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CSCharacter"));
	CharacterSpeed = 600.0f;
	CharacterDashSpeed = 1.0f;
	IsAttacking = false;

	MaxCombo = 4;
	AttackEndComboState();
}

// Called when the game starts or when spawned
void AAPlayerInputController::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovements->MaxWalkSpeed = CharacterSpeed;
	//무기 소켓
	FName WeaponSocket(TEXT("hand_socket_R"));

	auto weapon = GetWorld()->SpawnActor<AAWeaponActor >(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != weapon)
	{
		weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}

}

void AAPlayerInputController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PlayerAnim = Cast<UUNanaAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnim == nullptr) return;

	PlayerAnim->OnMontageEnded.AddDynamic(this, &AAPlayerInputController::OnAttackMontageEnded);

	PlayerAnim->OnNextAttackCheck.AddLambda([this]()->void {CanNextCombo = false;
	if (IsComboIntpuOn)
	{
		AttackStartComboState();
		PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
	}
	});

	PlayerAnim->OnDash.AddLambda([this]()->void {PlayerAnim->SetDash(false);
	PlayerAnim->Montage_Stop(0.3f, PlayerAnim->GetDashMontage());
	PlayerAnim->DashSpeed = 1.0f;
	});

	//AddUObject UObject 기반 멤버 함수 델리게이트를 추가합니다. UObject 델리게이트는 자신의 오브젝트에 대한 약 레퍼런스를 유지합니다.
	PlayerAnim->OnAttackHitCheck.AddUObject(this, &AAPlayerInputController::AttackCheck);
}

// Called every frame
void AAPlayerInputController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerAnim->GetDash() == true)//속도 끊김을 방지하기 위해
	{
		AddMovementInput(GetActorRotation().Vector(), 1.0f);
	}

	CharacterMovements->MaxWalkSpeed = CharacterSpeed * PlayerAnim->DashSpeed;
}

// Called to bind functionality to input
void AAPlayerInputController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AAPlayerInputController::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AAPlayerInputController::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AAPlayerInputController::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AAPlayerInputController::Turn);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AAPlayerInputController::Attatck);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &AAPlayerInputController::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomOut"), EInputEvent::IE_Pressed, this, &AAPlayerInputController::ZoomOut);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &AAPlayerInputController::Dash);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

}


void AAPlayerInputController::UpDown(float NewAxisValue)
{
	if(PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AAPlayerInputController::LeftRight(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AAPlayerInputController::LookUp(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddControllerPitchInput(NewAxisValue);
}

void AAPlayerInputController::Turn(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddControllerYawInput(NewAxisValue);
}

void AAPlayerInputController::Jump()
{

	if (PlayerAnim->GetJumpFinish() == true|| PlayerAnim->GetDamage() == true)
	{
		return;
	}

	ACharacter::Jump();
}

void AAPlayerInputController::ZoomIn()
{
	if (SpringArm->TargetArmLength - 30 < 200.0f) return;

	if (SpringArm->TargetArmLength <= 800.f&&SpringArm->TargetArmLength >= 200.f)
	{
		SpringArm->TargetArmLength -= 30;
	}
	else if (SpringArm->TargetArmLength < 200.0f)
	{
		SpringArm->TargetArmLength = 200.0f;
	}
}

void AAPlayerInputController::ZoomOut()
{
	if (SpringArm->TargetArmLength + 30 > 800.0f) return;

	if (SpringArm->TargetArmLength <= 800.f)
	{
		SpringArm->TargetArmLength += 30;
	}
	else
	{
		SpringArm->TargetArmLength = 800.0f;
	}
}

void AAPlayerInputController::Dash()
{
	if (PlayerAnim->GetDash() == true || IsAttacking == true || PlayerAnim->GetCurrentPawnSpeed() == 0.0f || PlayerAnim->GetIsInAir() == true|| PlayerAnim->GetDamage()==true)
		return;


	PlayerAnim->SetJumpFinish(false);
	PlayerAnim->SetDash(true);
	PlayerAnim->DashSpeed = 2.0f;
	PlayerAnim->PlayDashMontage();

}


void AAPlayerInputController::Attatck()
{
	if (PlayerAnim->GetDash() == true)
		return;

	if (IsAttacking == true)
	{
		if (CanNextCombo)
		{
			IsComboIntpuOn = true;
		}
	}
	else
	{
		CSCHECK(CurrentCombo == 0);


		AttackStartComboState();
		PlayerAnim->PlayeAttackMontage();
		//UE_LOG(LogTemp, Log, TEXT("PlayeAttackMontage"));
		PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void AAPlayerInputController::AttackCheck()
{

	FHitResult HitResult;
	FCollisionQueryParams Parms(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector()*200.0f,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12, FCollisionShape::MakeSphere(50.0f), Parms);




#if ENABLE_DRAW_DEBUG

	//FVector TracVec = GetActorForwardVector()*200.0f;
	//FVector Center = GetActorLocation() + TracVec * 0.5f;
	//FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	//float LiftTime = 5.0f;
	//DrawDebugSphere(GetWorld(), Center, 50.0f, 32.0f, DrawColor, false, LiftTime);

	FVector TraceVec = GetActorForwardVector()* 200.0f;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = 200.0f*0.5f + 50.0f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float LiftTime = 5.0f;
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, 50.0f, CapsuleRot, DrawColor, false, LiftTime);

#endif
	if (bResult)
	{//if (Target->GrassTrigger->ComponentHasTag(FName(TEXT("Grass"))))
		if (HitResult.Actor.IsValid())
		{
			if (HitResult.GetActor()->ActorHasTag(FName(TEXT("NormalMonster"))))
			{
				auto Monster = Cast<ACSNormalMonsterCharacter>(HitResult.GetActor());
				if (Monster == nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("Null2"));
					return;
				}
				auto MonsterAnim = Cast<UUNomalMonsterAnimInstance>(Monster->GetMesh()->GetAnimInstance());
				if (MonsterAnim == nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("Null"));
					return;
				}

				MonsterAnim->SetIsAttackDelayed(true);
				MonsterAnim->SetIsDamaged(true);
				MonsterAnim->SetIsAttacking(false);
				//GetWorld()->GetTimerManager().SetTimer(MonsterAnim->DelayTimer, this,);

			}
			//if()
			//if(Hit)
		}
	}
}

void AAPlayerInputController::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!IsAttacking || CurrentCombo < 0) return;
	//if(IsAttacking==false||)
	if (PlayerAnim->GetDash() == true)
		return;

	//CSCHECK(IsAttacking);
	//CSCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}

void AAPlayerInputController::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboIntpuOn = false;
	CSCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));

	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);

}

void AAPlayerInputController::AttackEndComboState()
{
	IsComboIntpuOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AAPlayerInputController::SetControlMode(int32 controlMode)
{
	//3인칭 회전 모드
	if (controlMode == 0)
	{
		SpringArm->TargetArmLength = CameraZoom;
		SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);


	}
}

void AAPlayerInputController::KnockBack(FVector HitLocation)
{
	FVector KnockBackDirection = GetActorLocation() - HitLocation;

	//KnockBackDirection.GetSafeNormal();
	//무적 타임 만들기
	PlayerAnim->SetDamage(true);
	KnockBackDirection.Normalize();
	KnockBackDirection.Z = 0;
	LaunchCharacter(KnockBackDirection*1500.0f, false, true);
	//FVector out = KnockBackDirection;
	//KnockBackDirection = KnockBackDirection.Normalize;
	//SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation()*(KnockBackDirection*5.0f), GetWorld()->GetDeltaSeconds(), 5.0f));

	//GetCharacterMovement()->AddImpulse(KnockBackDirection*10.0f, true);

}

