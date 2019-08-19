// Fill out your copyright notice in the Description page of Project Settings.

#include "CSNormalMonsterCharacter.h"
#include "CSPlayerCharacter.h"
#include "CS_AIController.h"
#include "NormalMonsterAnimInstance.h"

#include "CSMonsterrAbility.h"

#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "CSMonsterWidget.h"


#include "CharacterDamageComponent.h"
#include "CharacterDamage.h"
#include "DamageDeco.h"
#include "FireDamageDeco.h"
ACSNormalMonsterCharacter::ACSNormalMonsterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	MHPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MHPBARWIDGET"));
	
	
	this->Tags.AddUnique(TEXT("NormalMonster"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CSMonster"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MHPBarWidget->SetupAttachment(GetMesh());
	MHPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	MHPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> MUI_HUD(TEXT("WidgetBlueprint'/Game/UI/UI_MHPBar.UI_MHPBar_C'"));
	if (MUI_HUD.Succeeded())
	{
		MHPBarWidget->SetWidgetClass(MUI_HUD.Class);
		MHPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	AIControllerClass = ACS_AIController::StaticClass();
	
}

void ACSNormalMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ACSNormalMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CSAIController = Cast<ACS_AIController>(GetController());
	//랜덤 
	int rndNum = FMath::RandRange(0, MonsterNameArray.Num() - 1);
	MonsterSetting(this, MonsterNameArray[rndNum]);

	//UE_LOG(LogTemp, Log, TEXT("Null4"));
	NormalMonsterAnim = Cast<UNormalMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (NormalMonsterAnim == nullptr) return;
	NormalMonsterAnim->AttackHit.AddUObject(this, &ACSNormalMonsterCharacter::AttackCheck);

	MonsterAbility->OnHPIsZero.AddLambda([this]()->void {
		CSLOG(Warning, TEXT("OnMHPIsZero"));
		NormalMonsterAnim->DeadAnim();
	
		CSAIController->StopAI();
		SetActorEnableCollision(false);
		MHPBarWidget->SetHiddenInGame(true);
		FTimerHandle deadTimer;
		GetWorld()->GetTimerManager().SetTimer(deadTimer, FTimerDelegate::CreateLambda([this]()->void {
		
			Destroy();
		}), 5.0f, false);
	});
	//NormalMonsterAnim->AttackHit.AddLambda([this]()->void {Attack(); });
//	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACSNormalMonsterCharacter::OnCharacterOverlap);

	//유니티에서는 collison 함수
	//GetCapsuleComponent()->OnComponentHit
	auto MonsterWidget = Cast<UCSMonsterWidget>(MHPBarWidget->GetUserWidgetObject());

	if (MonsterWidget != nullptr)
	{
	
		MonsterWidget->BindMonsterStat(MonsterAbility);
	}

}

void ACSNormalMonsterCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Parms(NAME_None, false, this);

	//사이즈를 정해 놓았음 애들 크기에 맞게 충돌 체크 위치 조절
	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation()+FVector(0.0f,0.0f,20.0f), GetActorLocation() + FVector(0.0f, 0.0f, 20.0f) 
		+GetActorForwardVector()*120.0f,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(30.0f), Parms);

	//색깔 그리기
	FVector TracVec = FVector(0.0f, 0.0f, 20.0f)+GetActorForwardVector()*120.0f;
	FVector Center = GetActorLocation() + TracVec;
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float LiftTime = 5.0f;
	DrawDebugSphere(GetWorld(), Center, 30.0f, 32.0f, DrawColor, false, LiftTime);

	if (bResult)
	{	

		if (HitResult.Actor.IsValid())
		{
			ACSPlayerCharacter* Player= Cast<ACSPlayerCharacter >(HitResult.GetActor());
			if (Player->GetCapsuleComponent() == nullptr||Player == nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *HitResult.Actor->GetName());
				UE_LOG(LogTemp, Log, TEXT("nop4"));
				return;
			}

			if (Player->GetCapsuleComponent()->ComponentHasTag(FName(TEXT("Player"))))
			{
				FDamageEvent DamageEvent;

				if (Player->GetInvincibility() == false)
				{
					class  FFireDamageDeco* Firedag = new FFireDamageDeco();

					//불 도트 데미지 넣는 방법 1
					Player->CharacterState(ECharacterDamageState::FireState, Firedag);
				
					//불 도트 데미지 넣는 방법 2
					
					//Firedag->GetAttack(Player->GetPlayerStat(), Player);

					//일반 데미지 넣는 방법
					//HitResult.Actor->TakeDamage(MonsterStat->GetAttack(), DamageEvent, GetController(), this);
					
					
					Player->KnockBack(GetActorLocation());
				}
			}
		}
	}
}

//스폰 객체 액터, 중심 위치, 제한사이즈 x,y, 몬스터 수, 랜덤방향스폰
void ACSNormalMonsterCharacter::MonsterSpawn(AActor* Owner, FVector Orgin, float LimitSizeX,float LimitSizeY, int MonsterNum,bool bRndRot)
{

	UWorld* const world = GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParms;
		SpawnParms.Owner = Owner;
		SpawnParms.Instigator = Owner->Instigator;
		//FMath::RandRange(0, MonsterNameArray.Num() - 1);
		//중복 코드 함수화 시킬것
		if (bRndRot == false)
		{
			for (int i = 0; i < MonsterNum; ++i)
			{
				FVector SpawnLocation = Orgin + FVector(FMath::FRandRange(-LimitSizeX, LimitSizeX), FMath::FRandRange(-LimitSizeY, LimitSizeY), 0);
				ACSNormalMonsterCharacter* SpawnMonster = world->SpawnActor<ACSNormalMonsterCharacter>(ACSNormalMonsterCharacter::StaticClass(), SpawnLocation, Owner->GetActorRotation(), SpawnParms);
			}
		}
		else
		{
			FRotator RndRot = FRotator::ZeroRotator;
			for (int i = 0; i < MonsterNum; ++i)
			{
				RndRot.Yaw = FMath::FRandRange(10.0f, 350.0f);
				FVector SpawnLocation = Orgin + FVector(FMath::FRandRange(-LimitSizeX, LimitSizeX), FMath::FRandRange(-LimitSizeY, LimitSizeY), 0);
				ACSNormalMonsterCharacter* SpawnMonster = world->SpawnActor<ACSNormalMonsterCharacter>(ACSNormalMonsterCharacter::StaticClass(), SpawnLocation, Owner->GetActorRotation()+ RndRot, SpawnParms);
			}
		}
	}
	//spawnactor

}
float ACSNormalMonsterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	MonsterAbility->SetDamage(FinalDamage);

	return FinalDamage;
}
//void ACSNormalMonsterCharacter::OnCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	auto Target = Cast<AAPlayerInputController>(OtherActor);
//
//			UE_LOG(LogTemp, Log, TEXT("MonsterAnimDamage"));
//	if (Target != nullptr)
//	{
//		MonsterAnim = Cast<UUNomalMonsterAnimInstance>(GetMesh()->GetAnimInstance());
//		if (MonsterAnim->GetIsDamaged() == true)
//		{
//		}
//	}
//
//	//if (nullptr != Target)
//	//{
//
//	//	if (Target->bPaleyr == true)//플레이어 일 경우
//	//	{
//	//		for (auto&grass : GrassArray)
//	//		{
//	//			grass->GetPlayerCheckTrigger()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//모든 Bush 콜루젼 상태 ON
//	//		}
//
//	//		bBushOn = false;// 부시가 다 꺼짐
//
//	//	}
//	//	else//플레이어가 아닐 경우 
//	//	{
//	//		ObjectArray.Add(OtherActor);
//	//	}
//	//}
//
//}


//void ACSNormalMonsterCharacter::EndCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	//auto Player = Cast<AAStanCharacter>(OtherActor);
//
//	//if (GrassArray.Num() == 0)
//	//{
//	//	return;
//	//}
//
//	//if (nullptr != Player)
//	//{
//	//	if (Player->bPaleyr == true)
//	//	{
//
//	//		for (auto&grass : GrassArray)
//	//		{
//	//			grass->GetPlayerCheckTrigger()->SetCollisionEnabled(ECollisionEnabled::NoCollision);//모든 Bush 콜루젼 상태 OFF
//	//			//grass->GetGrassMesh()->SetHiddenInGame(false);
//	//			//grass->GetGrassMeshTranslucent()->SetHiddenInGame(true);
//
//	//			if (grass->bPlayerCheck == true)//이 부분을 바꾸어 보자
//	//			{
//	//				AAGrassActor* grassActor;
//	//				grassActor = grass;
//	//				grassActor->GrassOffBush();
//	//			}
//	//		}
//
//
//	//	}
//	//	else
//	//	{
//	//		ObjectArray.Remove(Player);
//	//	}
//	//}
//}
