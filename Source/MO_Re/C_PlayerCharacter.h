// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneCaptureComponent2D.h" 
#include "EnhancedInputComponent.h"
#include "Components/AudioComponent.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "C_Gamemode.h"
#include "C_Marker.h"
#include "Blueprint/UserWidget.h"
#include "CI_Player.h"
#include "C_GaymState.h"
#include "C_InventoryComponent.h"
#include <Camera/CameraComponent.h>
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/SpotLightComponent.h>
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ViewportItemMesh;
	float curDist;
	float holdingWeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsClimbing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsUsingCrafts;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	UC_InventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	UAIPerceptionStimuliSourceComponent* AIMarker;
	
	UCapsuleComponent* PlayerCapsule;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	USkeletalMeshComponent* ViewportGunMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float FlashlightMaxIntensity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* MainCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UAudioComponent* LeAudioPlayer;
	bool bCanLook;
	bool bOutOfOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = "true"))
	float FLookFactor = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = "true"))
	float FThoughtDuration = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = "true"))
	FString FThoughtBubble;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* HolsterAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* FlashlightAction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* Player_Widget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Player_Widget_Class;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Misc")
	USpotLightComponent* FlashlightLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Misc")
	AC_Marker* targetMarker;

	virtual int GetHealth_Implementation() override;
	virtual void Punch_Implementation(int hitPoints) override;
	virtual AActor* GetLookedAtItem_Implementation() override;
	virtual void SetHoveredItem_Implementation(FInventoryItem inputItem) override;
	virtual FInventoryItem GetHoveredItem_Implementation() override;
	virtual void Chatter_Implementation(const FString& speech, float speechDuration);
	virtual void InitLockPick_Implementation(int32 difficultyLevel);
	virtual void SendMessage_Implementation(const FEmailItem& inMessage);


	virtual FString GetThoughtString_Implementation();

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
	void TickSpeech();
	void Grab();
	void Special();
	void Holster();
	void AttemptToJump();
	FHitResult crouchHit;
	FCollisionObjectQueryParams crouchParams;
	FCollisionQueryParams crouchCollisionParams;
	bool bIsHolding;
	bool bIsReading;
	bool bIsInventoryOpen;
	bool bPaused;
	FInventoryItem hoveredItem;
	int currentHealth;
	int maxHealth = 100;
	float timerSpeech = 0.0f;
	float specialCooldown = 40.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
