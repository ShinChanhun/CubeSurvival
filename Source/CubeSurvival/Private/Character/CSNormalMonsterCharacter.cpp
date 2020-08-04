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
	//���� 
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

	//����Ƽ������ collison �Լ�
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

	//����� ���� ������ �ֵ� ũ�⿡ �°� �浹 üũ ��ġ ����
	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation()+FVector(0.0f,0.0f,20.0f), GetActorLocation() + FVector(0.0f, 0.0f, 20.0f) 
		+GetActorForwardVector()*120.0f,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(30.0f), Parms);

	//���� �׸���
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

					//�� ��Ʈ ������ �ִ� ��� 1
					Player->CharacterState(ECharacterDamageState::FireState, Firedag);
				
					//�� ��Ʈ ������ �ִ� ��� 2
					
					//Firedag->GetAttack(Player->GetPlayerStat(), Player);

					//�Ϲ� ������ �ִ� ���
					//HitResult.Actor->TakeDamage(MonsterStat->GetAttack(), DamageEvent, GetController(), this);
					
					
					Player->KnockBack(GetActorLocation());
				}
			}
		}
	}
}

//���� ��ü ����, �߽� ��ġ, ���ѻ����� x,y, ���� ��, �������⽺��
void ACSNormalMonsterCharacter::MonsterSpawn(AActor* Owner, FVector Orgin, float LimitSizeX,float LimitSizeY, int MonsterNum,bool bRndRot)
{

	UWorld* const world = GetWorld();
	if (world)
	{
		FActorSpawnParameters SpawnParms;
		SpawnParms.Owner = Owner;
		SpawnParms.Instigator = Owner->Instigator;
		//FMath::RandRange(0, MonsterNameArray.Num() - 1);
		//�ߺ� �ڵ� �Լ�ȭ ��ų��
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
//	//	if (Target->bPaleyr == true)//�÷��̾� �� ���
//	//	{
//	//		for (auto&grass : GrassArray)
//	//		{
//	//			grass->GetPlayerCheckTrigger()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//��� Bush �ݷ��� ���� ON
//	//		}
//
//	//		bBushOn = false;// �νð� �� ����
//
//	//	}
//	//	else//�÷��̾ �ƴ� ��� 
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
//	//			grass->GetPlayerCheckTrigger()->SetCollisionEnabled(ECollisionEnabled::NoCollision);//��� Bush �ݷ��� ���� OFF
//	//			//grass->GetGrassMesh()->SetHiddenInGame(false);
//	//			//grass->GetGrassMeshTranslucent()->SetHiddenInGame(true);
//
//	//			if (grass->bPlayerCheck == true)//�� �κ��� �ٲپ� ����
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
