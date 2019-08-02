// Fill out your copyright notice in the Description page of Project Settings.

#include "CSNormalMonsterCharacter.h"
#include "APlayerInputController.h"
#include "CS_AIController.h"
#include "UNomalMonsterAnimInstance.h"
#include "DrawDebugHelpers.h"
ACSNormalMonsterCharacter::ACSNormalMonsterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	/*
		if (MonsterCharacter != NULL)
		{
			GetMesh()->SetSkeletalMesh(MonsterCharacter->GetMonsterMesh()[TEXT("02020002_m_redmushroom")]);
			GetMesh()->SetRelativeLocationAndRotation(FVector4(0.0f, 0.0f, -25.0f), FRotator(0.0f, 180.0f, 0.0f));
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(MonsterCharacter->GetNormalMonsterAnim()[TEXT("02020002_m_redmushroom")]);

		}

		GetCapsuleComponent()->SetCapsuleHalfHeight(34.0f);
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);*/
	this->Tags.AddUnique(TEXT("NormalMonster"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CSMonster"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	//GetCapsuleComponent()->ComponentTags.AddUnique(TEXT("NormalMonster"));
	AIControllerClass = ACS_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ACSNormalMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 

}

void ACSNormalMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//랜덤 
	int rndNum = FMath::RandRange(0, MonsterNameArray.Num() - 1);
	MonsterSetting(this, MonsterNameArray[rndNum]);

	NormalMonsterAnim = Cast<UUNomalMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (NormalMonsterAnim == nullptr) return;

	//UE_LOG(LogTemp, Log, TEXT("Null4"));
	NormalMonsterAnim->AttackHit.AddUObject(this, &ACSNormalMonsterCharacter::AttackCheck);
	//NormalMonsterAnim->AttackHit.AddLambda([this]()->void {Attack(); });
//	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACSNormalMonsterCharacter::OnCharacterOverlap);

	//유니티에서는 collison 함수
	//GetCapsuleComponent()->OnComponentHit

}

void ACSNormalMonsterCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Parms(NAME_None, false, this);
	//사이즈를 정해 놓았음 애들 크기에 맞게 충돌 체크 위치 조절
	bool bResult = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation()+FVector(0.0f,0.0f,20.0f), GetActorLocation() + FVector(0.0f, 0.0f, 20.0f) 
		+GetActorForwardVector()*120.0f,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(30.0f), Parms);

	FVector TracVec = FVector(0.0f, 0.0f, 20.0f)+GetActorForwardVector()*120.0f;
	FVector Center = GetActorLocation() + TracVec;
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float LiftTime = 5.0f;
	DrawDebugSphere(GetWorld(), Center, 30.0f, 32.0f, DrawColor, false, LiftTime);

	if (bResult)
	{	

		if (HitResult.Actor.IsValid())
		{
			//UE_LOG(LogTemp, Log, TEXT("%s"), *HitResult.Actor->GetName());
			AAPlayerInputController* Player= Cast<AAPlayerInputController >(HitResult.GetActor());
			if (Player == nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *HitResult.Actor->GetName());
				UE_LOG(LogTemp, Log, TEXT("nop4"));
				return;
			}
			
			//UCapsuleComponent* capsule = Player->GetCapsuleComponent();
			if (Player->GetCapsuleComponent() == nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("nop5"));
				return;
			}

			if (Player->GetCapsuleComponent()->ComponentHasTag(FName(TEXT("Player"))))
			{
				Player->KnockBack(GetActorLocation());
				//넉백 시키기
				//UE_LOG(LogTemp, Log, TEXT("Null3"));
			}

			//UActorComponent
			//UPrimitiveComponent* Primtive = HitResult.Actor->GetComponentByClass(UPrimitiveComponent::StaticClass());
			//HitResult.GetActor()->GetComponents().Find()
		/*	if (HitResult.GetActor()->ActorHasTag(FName(TEXT("Player"))))
			{
				UE_LOG(LogTemp, Log, TEXT("Null2"));
			}*/
		}
	}



	//#if ENABLE_DRAW_DEBUG
	//
		/*FVector TracVec = GetActorForwardVector()*200.0f;
		FVector Center = GetActorLocation() + TracVec * 0.5f;
		FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		float LiftTime = 5.0f;
		DrawDebugSphere(GetWorld(), Center, 50.0f, 32.0f, DrawColor, false, LiftTime);*/

		//FVector TraceVec= GetActorForwardVector()*50.0f;
		//FVector Center = GetActorLocation() + TraceVec * 0.5f;
		//float HalfHeight = 50.0f*0.5f + 50.0f;
		//FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		//FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		//float LiftTime = 5.0f;
		//DrawDebugCapsule(GetWorld(),Center ,HalfHeight, 50.0f, CapsuleRot, DrawColor, false, LiftTime);
	//
	//#endif
	//	if (bResult)
	//	{//if (Target->GrassTrigger->ComponentHasTag(FName(TEXT("Grass"))))
	//		if (HitResult.Actor.IsValid())
	//		{
	//			if (HitResult.GetActor()->ActorHasTag(FName(TEXT("Player"))))
	//			{
	//				UE_LOG(LogTemp, Log, TEXT("Null2"));
	//			}
	//			//{
	//			//	auto Monster = Cast<ACSNormalMonsterCharacter>(HitResult.GetActor());
	//			//	if (Monster == nullptr)
	//			//	{
	//			//		UE_LOG(LogTemp, Log, TEXT("Null2"));
	//			//		return;
	//			//	}
	//			//	auto MonsterAnim = Cast<UUNomalMonsterAnimInstance>(Monster->GetMesh()->GetAnimInstance());
	//			//	if (MonsterAnim == nullptr)
	//			//	{
	//			//		UE_LOG(LogTemp, Log, TEXT("Null"));
	//			//		return;
	//			//	}
	//			//	//GetWorld()->GetTimerManager().SetTimer(MonsterAnim->DelayTimer, this,);
	//
	//			//}
	//			//if()
	//			//if(Hit)
	//		}
	//	}
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
