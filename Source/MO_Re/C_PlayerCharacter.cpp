// Fill out your copyright notice in the Description page of Project Settings.
#include "C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "C_UseableItem.h"
#include "CI_Entity.h"

// Sets default values
AC_PlayerCharacter::AC_PlayerCharacter()
{
	PlayerCapsule = GetCapsuleComponent();
	PlayerCapsule->SetSimulatePhysics(true);
	bCanLook = true;
	bOutOfOrder = false;
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(RootComponent);
	MainCamera->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	MainCamera->bUsePawnControlRotation = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	FlashlightLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight Component"));
	FlashlightLight->SetupAttachment(MainCamera);
	FlashlightLight->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	FlashlightLight->SetIntensity(0.0f);
	ViewportGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	ViewportGunMesh->SetupAttachment(MainCamera);
	ViewportGunMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ViewportGunMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	crouchParams.AddObjectTypesToQuery(ECC_WorldStatic);
	crouchCollisionParams.AddIgnoredActor(this);
	InventoryComponent = CreateDefaultSubobject<UC_InventoryComponent>(TEXT("Inventory"));
	currentHealth = maxHealth;
	LeAudioPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	LeAudioPlayer->SetupAttachment(RootComponent);
	AIMarker= CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIMarker"));
	LeAudioPlayer->bAutoActivate = false;
	PrimaryActorTick.bCanEverTick = true;
}


int AC_PlayerCharacter::GetHealth_Implementation()
{
	return currentHealth;
}

void AC_PlayerCharacter::Punch_Implementation(int hitPoints)
{
	currentHealth -= hitPoints;
	if (currentHealth <= 0)
	{
		bOutOfOrder = true;
		Holster();
		AIMarker->UnregisterFromPerceptionSystem();
	}
}

AActor* AC_PlayerCharacter::GetLookedAtItem_Implementation()
{
	return lookedAtActor;
}

void AC_PlayerCharacter::SetHoveredItem_Implementation(FInventoryItem inputItem)
{
	hoveredItem = inputItem;
}

FInventoryItem AC_PlayerCharacter::GetHoveredItem_Implementation()
{
	return hoveredItem;
}



void AC_PlayerCharacter::Chatter_Implementation(const FString &speech, float speechDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("Speaking...."));
	FThoughtBubble = speech;
	timerSpeech = speechDuration;
}

void AC_PlayerCharacter::InitLockPick_Implementation(int32 difficultyLevel)
{
	//asdf
}

void AC_PlayerCharacter::SendMessage_Implementation(const FEmailItem &inMessage)
{
	
}

bool AC_PlayerCharacter::GetIsWeaponHolstred_Implementation()
{
    return bIsUsingCrafts;
}

FString AC_PlayerCharacter::GetThoughtString_Implementation()
{
    return FThoughtBubble;
}

bool AC_PlayerCharacter::GetInventoryOpen()
{
	return bIsInventoryOpen;
}

void AC_PlayerCharacter::Special()
{
	if(specialCooldown <=0.0f)
	{
	
	}
}

void AC_PlayerCharacter::Holster()
{
	//I'm sick of wasting so much space of code soooooo I got insane
	if((InventoryComponent->CurrentGun.bIsItemValid ||bOutOfOrder)&&(!InventoryComponent->CurrentGun.bIsTooHeavy))
	{
		InventoryComponent->CurrentGun.bIsItemValid = false;
		ViewportGunMesh->SetSkeletalMesh(nullptr);
		bIsUsingCrafts = true;
	}
	else
	{
		if(!bOutOfOrder)
		{
			InventoryComponent->CurrentGun.bIsItemValid = true;
			ViewportGunMesh->SetSkeletalMesh(InventoryComponent->CurrentGun.ViewportMesh);
			bIsUsingCrafts = false;
		}
	}
}

void AC_PlayerCharacter::AttemptToJump()
{
	if(bCanLook)
	{
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GM_Instance = Cast<AC_Gamemode>(GetWorld()->GetAuthGameMode());
	GS_Instance = Cast<AC_GaymState>(GetWorld()->GetGameState());
	//------------INPUT SETUP -------------------------------------------------------------
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	if (Player_Widget_Class != nullptr)
	{
		Player_Widget = CreateWidget(GetWorld(), Player_Widget_Class);
		Player_Widget->AddToViewport();
	}
	ICI_Player::Execute_Chatter(this, "Ow, my head....",3.0f );
	//PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerCharacter::OnBeginOverlap);
	//PlayerCapsule->OnComponentEndOverlap.AddDynamic(this, &AC_PlayerCharacter::OnEndOverlap);
	//-----------------------------------------------------------------------------------
}


void AC_PlayerCharacter::Use()
{
	if (bCanLook)
	{
		if (GS_Instance->cacheItemID > -1)
		{
			if (InventoryComponent->InventoryArray[GS_Instance->cacheItemID].bIsInteractable)
			{
				//ICI_Player::Execute_Chatter(this, "What shuddai do?",3.0f );

			}
		}
		else
			if (lookedAtActor != nullptr)
				IC_UseableItem::Execute_UseItem(lookedAtActor, GS_Instance->cacheItemID, InventoryComponent);

		GS_Instance->cacheItemID = -1;
		GS_Instance->SetInventoryOpen(false);
	}


}
void AC_PlayerCharacter::Flashlight()
{
	FlashlightLight->Intensity <= 0.0f&&!bOutOfOrder ? FlashlightLight->SetIntensity(FlashlightMaxIntensity) : FlashlightLight->SetIntensity(0);
}
void AC_PlayerCharacter::Pause()
{
	GM_Instance->PauseGame();
}
void AC_PlayerCharacter::LookAt()
{
	FHitResult OutHit;
	FVector StartLine = MainCamera->GetComponentLocation();
	FVector ForwardLine = MainCamera->GetForwardVector();
	FVector End = ((ForwardLine * 244.0f) + StartLine);
	FCollisionQueryParams CollisionParams;
	//DrawDebugLine(GetWorld(), StartLine, End, FColor::Green, false, 1, 0, 1);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLine, End, ECC_Visibility, CollisionParams))
	{
		if (IsValid(OutHit.GetActor()) && OutHit.GetActor()->Implements<UC_UseableItem>())
		{
			lookedAtActor = OutHit.GetActor();
		}
		else
		{
			lookedAtActor = nullptr;
		}
	}
	else
	{
		lookedAtActor = nullptr;
	}
}
void AC_PlayerCharacter::Inventory()
{
	if(!bOutOfOrder)
	{
	GS_Instance->SwitchInventoryOpen();
	if (GS_Instance->GetInventoryOpen())
	{
		bCanLook = false;
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	}
	else
	{
		bCanLook = true;
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}
	}

}
void AC_PlayerCharacter::Quit()
{
	UE_LOG(LogTemp, Warning, TEXT("Is Paused%s "), bPaused ? TEXT("True") : TEXT("False"));
	if (GM_Instance->bIsPaused)
	{
		GM_Instance->PauseGame();
		FGenericPlatformMisc::RequestExit(false);
	}
}
void AC_PlayerCharacter::Blast()
{
	if (InventoryComponent->CurrentGun.bIsItemValid && GS_Instance->cacheItemID<0 && lookedAtActor == nullptr && bCanLook && !bIsUsingCrafts &&!bOutOfOrder)
	{
		if (InventoryComponent->CurrentGun.currentAmmo > 0)
		{
			ShotEvent.Broadcast();
			LeAudioPlayer->SetSound(InventoryComponent->CurrentGun.PewSound);
			LeAudioPlayer->Play();
			FHitResult ShootHit;
			FVector S_StartLine = MainCamera->GetComponentLocation();
			FVector S_ForwardLine = MainCamera->GetForwardVector();
			FVector S_End = ((S_ForwardLine * 6000.0f) + S_StartLine);
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(this);
			if (GetWorld()->LineTraceSingleByChannel(ShootHit, S_StartLine, S_End, ECC_Camera, CollisionParams))
			{
				DrawDebugLine(GetWorld(), S_StartLine, ShootHit.Location, FColor::Green, false, 2.f, 0, 3.f);
				AActor* victim = ShootHit.GetActor();
				if (IsValid(victim) && victim->Implements<UCI_Entity>())
					ICI_Entity::Execute_Punch(victim, 2);
			}
			//Shooting logic (not 4 now m8)
			InventoryComponent->CurrentGun.currentAmmo -= 1;
		}
	}
}
void AC_PlayerCharacter::ShootStart()
{
	if (InventoryComponent->CurrentGun.bIsItemValid && GS_Instance->cacheItemID<0 && lookedAtActor == nullptr && bCanLook && !bIsUsingCrafts &&!bOutOfOrder)
	{
		switch(InventoryComponent->CurrentGun.shootPattern)
		{
			case(EShootingPattern::Single):
				Blast();
				break;
			case(EShootingPattern::FullAuto):
				warmupTimer = InventoryComponent->CurrentGun.shootWarmup;
				isShootingNow = true;
		}
	}
	else
	{
		if(bOutOfOrder)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetMapName()));
		}
	}
}

void AC_PlayerCharacter::Shoot()
{
	if(isShootingNow)
	{
		if(warmupTimer<=0.0f)
		{
			if(cooldownTimer<=0.0f)
			{
				Blast();
				cooldownTimer = InventoryComponent->CurrentGun.shootCooldown;
			}
		}
	}
}
void AC_PlayerCharacter::UnShoot()
{
	isShootingNow = false;
	warmupTimer = 0.0f;
}
void AC_PlayerCharacter::Move(const FInputActionValue& Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector XDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector YDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector ZDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
	if (bOutOfOrder != true && bCanLook == true) {
		if (Controller != nullptr)
		{
			/*if (!bIsClimbing)

			{*/
			//NOTE: For some reason XDirection and YDirection are f***d up, doing what they're supposed to do vice versa.
			//Keep that in mind.
			//NOTE: Formula for movement: (Y vector * Speed *(1 - (mass / 8)))
			AddMovementInput(XDirection, (MovementVector.Y * 0.6f));
			AddMovementInput(YDirection, (MovementVector.X * 0.6f));
			/* }
			else
			{
				AddMovementInput(ZDirection, (MovementVector.Y * 0.6f));
			}

		}*/
		}

	}
}

void AC_PlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr && bCanLook)
	{
		AddControllerYawInput(LookAxisVector.Y * FLookFactor);
		AddControllerPitchInput(LookAxisVector.X * FLookFactor);
	}
}
void AC_PlayerCharacter::TickCooldowns(float _DeltaTime)
{
	if(warmupTimer >0.0f)
	{
		warmupTimer -= _DeltaTime;
	}
	if(cooldownTimer > 0.0f)
	{
		cooldownTimer -= _DeltaTime;
	}
}

// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAt();
	TickSpeech();
	TickCooldowns(DeltaTime);
}
void AC_PlayerCharacter::TickSpeech()
{
	if(timerSpeech>0.0f && FThoughtBubble != "")
		timerSpeech -= GetWorld()->GetDeltaSeconds();
	else
		FThoughtBubble = "";
}

// Called to bind functionality to input
void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Bind all the Input Actions (TBA)
		//EXAMPLE: EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//And yada yada yada
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_PlayerCharacter::Look);
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Use);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::ShootStart);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AC_PlayerCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AC_PlayerCharacter::UnShoot);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Inventory);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::AttemptToJump);
		EnhancedInputComponent->BindAction(HolsterAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Holster);
		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Flashlight);



	}
}

