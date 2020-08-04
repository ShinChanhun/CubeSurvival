

#include "CSPlayerCharacter.h"


#include "CharacterResourceManager.h"
#include "PlayerAnimInstance.h"
#include "SwordActor.h"
#include "DrawDebugHelpers.h"
#include "NormalMonsterAnimInstance.h"
#include "CSNormalMonsterCharacter.h"

#include "CSPlayerAbility.h"
//#include "CSPlayerDamage.h"
#include "Components/WidgetComponent.h"
#include "CSPlayerWidget.h"


#include "CharacterDamageComponent.h"
#include "CharacterDamage.h"
#include "DamageDeco.h"
#include "FireDamageDeco.h"

#include "CSPlayerController.h"

#include "CSGameInstance.h"

ACSPlayerCharacter::ACSPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//static으로 바꿔도 (비쥬얼로 에디터를 켰을 때)생성자를 두번 호출하기 때문에  한번은 불러 올 수 있지만 두번째는 값이 사라져 있다.
	//(싱글톤을 따로 만들어야 할거 같다. 근데 될지 안될지 잘 모르겠다;;) Uworld가 생성하기전에 불러와서 getworld값은 null로 바뀐다.  싱글톤으로 해도 안됨
	//UCharacterResourceManager* PlayerResource = UCSGameInstance::GetCharacterResourceManager();//static으로 만들었을 때
	//auto* PlayerResource = Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));//getworld로 받아왔을때 null

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//auto testsssss = UCSGameInstance::GetInstance()->GetCharacterResourceManager();

	  //PlayerResource = UCSGameInstance::GetGameInstance()->GetCharacterResourceManager();
		//UCSGameInstance::GetCharacterResourceManager();

	PlayerResource = CreateDefaultSubobject<UCharacterResourceManager>(TEXT("PlayerResource"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	CharacterMovements = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	PlayerAbility = CreateDefaultSubobject<UCSPlayerAbility>(TEXT("PlAYERABILITY"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));


	SpringArm->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(GetMesh());

	CameraZoom = 700.0f;
	SetControlMode(0);
	SpringArm->TargetArmLength = CameraZoom;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

	if (PlayerResource != NULL)
	{
		GetMesh()->SetSkeletalMesh(PlayerResource-> GetPlayerMesh());
		GetMesh()->SetRelativeLocationAndRotation(FVector4(0.0f, 0.0f, -88.0f), FRotator(0.0f, 270.0f, 0.0f));
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(PlayerResource->GetPlayerAnimClass());
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	}

	GetCapsuleComponent()->ComponentTags.AddUnique(TEXT("Player"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CSCharacter"));

	GetCharacterMovement()->JumpZVelocity = 600.0f;
	CharacterSpeed = 600.0f;
	CharacterDashSpeed = 1.0f;
	MaxCombo = 4;

	bAttacking = false;
	bInvincibility = false;
	AttackEndComboState();
	SetActorHiddenInGame(true);
	HPBarWidget->SetHiddenInGame(true);
	bCanBeDamaged = false;
}

void ACSPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnim == nullptr) return;

	PlayerAnim->OnMontageEnded.AddDynamic(this, &ACSPlayerCharacter::OnAttackMontageEnded);

	PlayerAnim->OnNextAttackCheck.AddLambda([this]()->void 
	{
		bCanNextCombo = false;
		if (bComboIntpuOn == true)
		{
			AttackStartComboState();
			PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});

	PlayerAnim->OnDash.AddLambda([this]()->void {
		PlayerAnim->SetDash(false);
		PlayerAnim->Montage_Stop(0.3f, PlayerAnim->GetDashMontage());
		PlayerAnim->DashSpeed = 1.0f;
	});

	//AddUObject UObject 기반 멤버 함수 델리게이트를 추가합니다. UObject 델리게이트는 자신의 오브젝트에 대한 약 레퍼런스를 유지합니다.
	PlayerAnim->OnAttackHitCheck.AddUObject(this, &ACSPlayerCharacter::AttackCheck);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACSPlayerCharacter::PlayerHit);;

	PlayerAbility->SetNewLevel(1);

	/*PlayerAbility->OnHPIsZero.AddLambda([this]()->void {
		CSLOG(Warning, TEXT("OnHPIsZero"));
		PlayerAnim->DeadAnim();
		SetActorEnableCollision(false);
	});*/




}

// Called when the game starts or when spawned
void ACSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovements->MaxWalkSpeed = CharacterSpeed;
	//무기 소켓
	FName WeaponSocket(TEXT("hand_socket_R"));

	auto weapon = GetWorld()->SpawnActor<ASwordActor>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != weapon)
	{
		weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}

	CSPlayerController = Cast<ACSPlayerController>(GetController());
	CSCHECK(CSPlayerController != nullptr);

	//구분해서 사용하기
	SetCharacterState(ECharacterState::LOADING);
	
	SetCharacterState(ECharacterState::READY);
}

// Called every frame
void ACSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerAnim->GetDash() == true)//속도 끊김을 방지하기 위해
	{

		AddMovementInput(GetActorRotation().Vector(), 1.0f);
	}

	CharacterMovements->MaxWalkSpeed = CharacterSpeed * PlayerAnim->DashSpeed;
}

// Called to bind functionality to input
void ACSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ACSPlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ACSPlayerCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACSPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACSPlayerCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACSPlayerCharacter::Attatck);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &ACSPlayerCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomOut"), EInputEvent::IE_Pressed, this, &ACSPlayerCharacter::ZoomOut);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &ACSPlayerCharacter::Dash);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

}


void ACSPlayerCharacter::UpDown(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);

}

void ACSPlayerCharacter::LeftRight(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void ACSPlayerCharacter::LookUp(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddControllerPitchInput(NewAxisValue);
}

void ACSPlayerCharacter::Turn(float NewAxisValue)
{
	if (PlayerAnim->GetDamage() == true)
	{
		return;
	}
	AddControllerYawInput(NewAxisValue);
}

void ACSPlayerCharacter::Jump()
{

	if (PlayerAnim->GetJumpFinish() == true || PlayerAnim->GetDamage() == true || PlayerAnim->GetDead() == true)
	{
		return;
	}

	ACharacter::Jump();
}

void ACSPlayerCharacter::ZoomIn()
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

void ACSPlayerCharacter::ZoomOut()
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

void ACSPlayerCharacter::Dash()
{
	if (PlayerAnim->GetDash() == true || bAttacking == true || PlayerAnim->GetCurrentPawnSpeed() == 0.0f || PlayerAnim->GetInAir() == true || PlayerAnim->GetDamage() == true || PlayerAnim->GetDead() == true)
		return;

	PlayerAnim->PlayDashMontage();
	PlayerAnim->DashSpeed = 2.0f;
	PlayerAnim->SetJumpFinish(false);
	PlayerAnim->SetDash(true);
}


void ACSPlayerCharacter::Attatck()
{
	if (PlayerAnim->GetDash() == true)
		return;

	if (bAttacking == true)
	{
		if (bCanNextCombo)
		{
			bComboIntpuOn = true;
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(Timer);
		CSCHECK(CurrentCombo == 0);
		AttackStartComboState();
		PlayerAnim->PlayeAttackMontage();
		PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		bAttacking = true;

		//TODO:데미지 해제 역할 코드
		/*FDamageDeco* adss = *CharacterStateDamage.Find(ECharacterDamageState::FireState);
		adss->DmageRelease(this);
		CharacterStateDamage.Remove(ECharacterDamageState::FireState);*/
		//adss 해제가 되는지 확인할것
		
	}
}

void ACSPlayerCharacter::AttackCheck()
{

	FHitResult HitResult;
	FCollisionQueryParams Parms(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector()*200.0f,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(50.0f), Parms);




#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector()* 200.0f;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = 200.0f*0.5f + 50.0f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float LiftTime = 5.0f;
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, 50.0f, CapsuleRot, DrawColor, false, LiftTime);

#endif
	if (bResult)
	{
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
				auto MonsterAnim = Cast<UNormalMonsterAnimInstance>(Monster->GetMesh()->GetAnimInstance());
				if (MonsterAnim == nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("Null"));
					return;
				}
				FDamageEvent DamageEvent;

				HitResult.Actor->TakeDamage(PlayerAbility->GetAttack(), DamageEvent, GetController(), this);
				MonsterAnim->SetIsAttackDelayed(true);
				MonsterAnim->SetIsDamaged(true);
				MonsterAnim->SetIsAttacking(false);
			}
		}
	}
}

void ACSPlayerCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bAttacking || CurrentCombo < 0) return;

	if (PlayerAnim->GetDash() == true)
		return;

	bAttacking = false;
	AttackEndComboState();
}

void ACSPlayerCharacter::AttackStartComboState()
{
	bCanNextCombo = true;
	bComboIntpuOn = false;
	CSCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));

	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);

}

void ACSPlayerCharacter::AttackEndComboState()
{
	bComboIntpuOn = false;
	bCanNextCombo = false;
	CurrentCombo = 0;
}

void ACSPlayerCharacter::SetControlMode(int32 controlMode)
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

void ACSPlayerCharacter::KnockBack(FVector HitLocation)
{
	PlayerAnim->SetJumpFinish(false);

	bInvincibility = true;

	FVector KnockBackDirection = GetActorLocation() - HitLocation;
	KnockBackDirection.Z = 0;

	PlayerAnim->SetDamage(true);
	KnockBackDirection.Normalize();

	if (PlayerAnim->GetInAir())//공중에 있을 때
	{
		GetCharacterMovement()->Launch(KnockBackDirection*700.0f);
	}
	else
	{
		GetCharacterMovement()->Launch(KnockBackDirection*1500.0f);
	}

	GetWorldTimerManager().SetTimer(Timer, this, &ACSPlayerCharacter::ChangeInvincibility, 3.0f, false);//무적 카운트 들어감
}

//몬스터와 부딪혔을 때 넉백
void ACSPlayerCharacter::PlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("NormalMonster"))
	{
		if (bInvincibility == false)
		{
			auto controller = Cast< AController>(OtherActor);
			FDamageEvent DamageEvent;
			this->TakeDamage(10.0f, DamageEvent, controller, OtherActor);
			KnockBack(OtherActor->GetActorLocation());
		}

	}
}

void ACSPlayerCharacter::ChangeInvincibility()
{
	PlayerAnim->SetDamage(false);
	bInvincibility = false;
}

float ACSPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	PlayerAbility->SetDamage(FinalDamage);

	return FinalDamage;
}

//TODO:아래 함수들 상태 데미지 클래스 따로 만들기

void ACSPlayerCharacter::CharacterState(enum ECharacterDamageState PlayerState, class FDamageDeco* DamageClass)
{
	if (CharacterStateArry.Num() != 0)
	{
		if (CharacterStateArry.Find(PlayerState))
		{
			return;
		}
	}

	CharacterStateArry.Add(PlayerState);

	UpdateStateDamage(PlayerState);

}

void ACSPlayerCharacter::UpdateStateDamage(enum ECharacterDamageState PlayerState)//오브젝트들 도트데미지 넣을 때 사용
{
	ECharacterDamageState EPlayerState = PlayerState;

	switch (EPlayerState)
	{
	case ECharacterDamageState::FireState:
	{
		UE_LOG(LogTemp, Log, TEXT("fire"));
		FFireDamageDeco* Firedag = new FFireDamageDeco();
	
		Firedag->FireAttack(PlayerAbility,this);

		//TODO:상태값 및 데미지 클래스 넣는 코드
		CharacterStateDamage.Add(PlayerState, Firedag);
		break;
	}
	case ECharacterDamageState::IceState:
	{	UE_LOG(LogTemp, Log, TEXT("Ice"));
		break;
	}
	case ECharacterDamageState::PoisonState:
	{//PlayerStat->SetDamage(FinalDamage);
		UE_LOG(LogTemp, Log, TEXT("Poison"));
		break;
	}
	case ECharacterDamageState::StunState:
	{
		UE_LOG(LogTemp, Log, TEXT("Stun"));
		break;
	}
	case ECharacterDamageState::NormalState:
	{
		UE_LOG(LogTemp, Log, TEXT("Stun"));
		break;
	}

	default:
	{
		break;
	}
	}
}
void ACSPlayerCharacter::SetCharacterState(ECharacterState NewState)
{
	CSCHECK(CurrentState != NewState);
	CurrentState = NewState;

	switch (CurrentState)
	{
	case ECharacterState::LOADING:
	{
		SetActorHiddenInGame(true);
		HPBarWidget->SetHiddenInGame(true);
		bCanBeDamaged = false;
		break;
		

	}
	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(false);
		bCanBeDamaged = true;

		PlayerAbility->OnHPIsZero.AddLambda([this]()->void
		{
			SetCharacterState(ECharacterState::DEAD);
		}
		);

		auto CharacterWidget = Cast<UCSPlayerWidget>(HPBarWidget->GetUserWidgetObject());
		CSCHECK(CharacterWidget != nullptr);
		CharacterWidget->BindCharacterStat(PlayerAbility);
		break;
	}
	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		PlayerAnim->DeadAnim();
		bCanBeDamaged = false;
		break;
		//HPBarWidget->SetHiddenInGame(false);
		//GetMesh()->SetHiddenInGame(false);
	}
	default:
		break;
	}
}
ECharacterState ACSPlayerCharacter::GetCharacterState() const
{
	return CurrentState;
}



//델리게이트
//UFUNCTION()
//void OnTimer(int32 x, float y);
//
//FTimerDelegate delegate;
//int32 param1 = 1;
//float param2 = 2.f;
//delegate.BindUFunction(this, FName("OnTimer"), param1, param2);
//
//GetTimerManager().SetTimer(handle, delegate, delay);
//[출처] 안녕하세요~타이머에 관한 질문입니다. (언리얼 엔진 공식 카페(Unreal Engine)) | 작성자 얌생