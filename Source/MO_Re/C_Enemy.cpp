// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Enemy.h"
#include "C_SecuritronPilot.h"

// Sets default values
AC_Enemy::AC_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}
int AC_Enemy::GetHealth_Implementation()
{
	return currentHealth;
}

void AC_Enemy::Punch_Implementation(int hitPoints)
{
	currentHealth -= hitPoints;
	UE_LOG(LogTemp, Warning, TEXT("Ow!"));

	if (currentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("I'm already DEAD!"));

		bOutOfOrder = true;
		//Play some edgy death animation but for now just go to die
		Destroy();
		

	}
}
UBehaviorTree* AC_Enemy::GetBehaviourTree() const
{
	return Tree;
}
void AC_Enemy::SwitchIsEnabled(bool bIsEnabled)
{
	if (bOutOfOrder)
	{
		bOutOfOrder = false;
		
	}
		
	else
		bOutOfOrder = true;
}
// Called every frame
void AC_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AC_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

