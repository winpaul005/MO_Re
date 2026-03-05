// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

#include "BehaviorTree/BehaviorTree.h"
#include "CI_Entity.h"
#include "C_Enemy.generated.h"

UCLASS()
class MO_RE_API AC_Enemy : public ACharacter, public ICI_Entity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"));
	int currentHealth;
	bool bOutOfOrder;
	virtual int GetHealth_Implementation() override;
	virtual void Punch_Implementation(int hitPoints) override;
	virtual void ScenarioStartle_Implementation(const TArray<AActor*>& victims) override;
	UBehaviorTree* GetBehaviourTree() const;
	UBlackboardComponent* BlackboardComponent;
	UFUNCTION(BlueprintCallable)
	void SwitchIsEnabled(bool bIsEnabled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess="true"))
	
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
