// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

#include "C_SecuritronPilot.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UBehaviourTree;
class AC_Enemy;

UCLASS()
class MO_RE_API AC_SecuritronPilot : public AAIController
{
	GENERATED_BODY()
	public:
		explicit AC_SecuritronPilot(FObjectInitializer const& ObjectInitializer);
	protected:
		virtual void BeginPlay() override;
		virtual void OnPossess(APawn* InPawn) override;
	
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UAIPerceptionComponent* SenseComponent;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UAISenseConfig_Sight *SightComponent;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UAISenseConfig_Hearing *HearComponent;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent{ nullptr };

		UFUNCTION(Category = "AI")
		void Startle(const TArray<AActor*>& potentialThreats);
		UFUNCTION(BlueprintCallable)
		void StartleTo(const TArray<AActor*>& victims);
		UFUNCTION(Category = "AI")
		void Pursue(AActor* Actor, FAIStimulus Stimulus);
	private:
		UPROPERTY()
		TObjectPtr<UBehaviorTree> BehaviorTree;
		AC_Enemy* victimPawn;
};
