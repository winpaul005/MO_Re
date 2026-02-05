// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>
#include "MyBTTask_Startle.h"
//PROBLEM: for unknown reason, startle behaviour task invokes linker errors (even if there's LITERALLY NOTHING in the method)


UMyBTTask_Startle::UMyBTTask_Startle(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Startle";
}

EBTNodeResult::Type UMyBTTask_Startle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	if (AC_SecuritronPilot* const cont = Cast<AC_SecuritronPilot>(OwnerComp.GetAIOwner()))
	{
		if (APawn* const enemie = cont->GetPawn())
		{
			FVector const selfLocation = enemie->GetActorLocation();

			if (UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FVector plyrLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
				FNavLocation Loc;
				if (NavSys->ProjectPointToNavigation(plyrLoc,Loc))
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

