// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SecuritronPilot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C_PlayerCharacter.h"
#include "C_Enemy.h"

AC_SecuritronPilot::AC_SecuritronPilot(FObjectInitializer const& ObjectInitializer)
{
	SenseComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SenseComponent"));
	SightComponent = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightComponent"));
	HearComponent = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearComponent"));
	SightComponent->SightRadius = 800.0f;
	SightComponent->LoseSightRadius = 820.0f;
	SightComponent->PeripheralVisionAngleDegrees = 360.0f;
	SightComponent->DetectionByAffiliation.bDetectEnemies=true;
	SenseComponent->ConfigureSense(*HearComponent);
	SenseComponent->ConfigureSense(*SightComponent);
	SenseComponent->SetDominantSense(SightComponent->GetSenseImplementation());
	SenseComponent->OnPerceptionUpdated.AddDynamic(this, &AC_SecuritronPilot::Startle);
	SenseComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AC_SecuritronPilot::Pursue);
	
}

void AC_SecuritronPilot::BeginPlay()
{
	Super::BeginPlay();
}

void AC_SecuritronPilot::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AC_Enemy* const enemie = Cast<AC_Enemy>(InPawn))
	{
		if (UBehaviorTree* const eTree = enemie->GetBehaviourTree())
		{
			UseBlackboard(eTree->BlackboardAsset, enemie->BlackboardComponent);
			Blackboard = enemie->BlackboardComponent;
			RunBehaviorTree(eTree);
			victimPawn = enemie;	
		}
	}
}

void AC_SecuritronPilot::Startle(const TArray<AActor*>& potentialThreats)
{
	UE_LOG(LogTemp, Warning, TEXT("Detected %d actors!"),potentialThreats.Num());
	if(potentialThreats.Num()>0 && potentialThreats.Find(GetWorld()->GetFirstPlayerController()->GetPawn())==0)
	{
		victimPawn->BlackboardComponent->SetValueAsVector(TEXT("TargetVector"), potentialThreats[0]->GetActorLocation());
		victimPawn->BlackboardComponent->SetValueAsBool(TEXT("IsStartled"), true);
		BrainComponent->RestartLogic();
		RunBehaviorTree(victimPawn->GetBehaviourTree());
	}
	else
	{
		victimPawn->BlackboardComponent->SetValueAsBool(TEXT("IsStartled"), false);
	}

}

void AC_SecuritronPilot::Pursue(AActor *Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed()&&Actor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		UE_LOG(LogTemp, Warning, TEXT("A N G E R Y"));
		victimPawn->BlackboardComponent->SetValueAsBool(TEXT("IsTriggered"), true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ok, bye 4now...."));
		victimPawn->BlackboardComponent->SetValueAsBool(TEXT("IsTriggered"), false);
		BrainComponent->RestartLogic();
	}

}
