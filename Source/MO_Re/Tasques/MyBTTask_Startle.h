// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MO_Re/C_SecuritronPilot.h>
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_Startle.generated.h"

/**
 * 
 */
UCLASS()
class MO_RE_API UMyBTTask_Startle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UMyBTTask_Startle(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	
};
