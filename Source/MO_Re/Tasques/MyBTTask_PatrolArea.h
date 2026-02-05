// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MO_Re/C_SecuritronPilot.h>
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_PatrolArea.generated.h"

/**
 * 
 */
UCLASS()
class MO_RE_API UMyBTTask_PatrolArea : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
		explicit UMyBTTask_PatrolArea(FObjectInitializer const& ObjectInitializer);
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	private:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess="true"))
		float MaximumPatrolArea = 1500.f;
};
