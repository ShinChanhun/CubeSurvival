// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_AttackWait.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UBTTask_AttackWait : public UBTTask_Wait
{
	GENERATED_BODY()

	UBTTask_AttackWait(const FObjectInitializer& ObjectInitializer);
		/** wait time in seconds */
	//UPROPERTY(Category = Wait, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	//float WaitTime;

	/** allows adding random time to wait time */
	//UPROPERTY(Category = Wait, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))
	//float RandomDeviation;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
//	virtual uint16 GetInstanceMemorySize() const override;
//	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
//	virtual FString GetStaticDescription() const override;
//
//#if WITH_EDITOR
//	virtual FName GetNodeIconName() const override;
//#endif // WITH_EDITOR

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
