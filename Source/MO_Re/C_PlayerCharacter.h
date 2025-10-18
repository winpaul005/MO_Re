// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "C_Gamemode.h"
#include "Blueprint/UserWidget.h"
#include "CI_Player.h"
#include "C_GaymState.h"
#include "C_InventoryComponent.h"
#include <Camera/CameraComponent.h>
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "C_PlayerCharacter.generated.h"

//Using this comment section to remind you that every AI 'artist' should
//eat 1.678 tones of battery acid the moment the game compiles 



UCLASS()
class MO_RE_API AC_PlayerCharacter : public ACharacter, public ICI_Player
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_PlayerCharacter();
	UPROPERTY(EditDefaultsOnly)
	UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmC;
	float curDist;
	float holdingWeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsClimbing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	UC_InventoryComponent* InventoryComponent;
	UCapsuleComponent* PlayerCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* MainCamera;
	bool bCanLook;
	bool bOutOfOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = "true"))
	float FLookFactor = 10.f;
	AC_GaymState* GS_Instance;
	AC_Gamemode* GM_Instance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* UseAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* Player_Widget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Player_Widget_Class;
	virtual int GetHealth_Implementation() override;
	virtual void Punch_Implementation(int hitPoints) override;
	virtual AActor* GetLookedAtItem_Implementation() override;
	UFUNCTION(BlueprintCallable)
	bool GetInventoryOpen();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* lookedAtActor;



	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//void Jump();
	void Use();
	void Flashlight();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Discard();
	void Inventory();
	void Quit();
	void Shoot();
	void Pause();
	void LookAt();
	void Grab();
	void AttemptToJump();
	FHitResult crouchHit;
	FCollisionObjectQueryParams crouchParams;
	FCollisionQueryParams crouchCollisionParams;
	bool bIsHolding;
	bool bIsReading;
	bool bIsInventoryOpen;
	bool bPaused;
	int currentHealth;
	int maxHealth = 40;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
