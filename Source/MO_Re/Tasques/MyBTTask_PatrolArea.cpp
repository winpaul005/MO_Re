// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_PatrolArea.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>

UMyBTTask_PatrolArea::UMyBTTask_PatrolArea(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Patrol Area";
}

EBTNodeResult::Type UMyBTTask_PatrolArea::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AC_SecuritronPilot* const cont = Cast<AC_SecuritronPilot>(OwnerComp.GetAIOwner()))
	{
		if (APawn* const enemie = cont->GetPawn())
		{
			FVector const selfLocation = enemie->GetActorLocation();

			if (UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(selfLocation, MaximumPatrolArea, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;

}

