// Fill out your copyright notice in the Description page of Project Settings.
#include "C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_UseableItem.h"

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
	PrimaryActorTick.bCanEverTick = true;
	crouchParams.AddObjectTypesToQuery(ECC_WorldStatic);
	crouchCollisionParams.AddIgnoredActor(this);
	InventoryComponent = CreateDefaultSubobject<UC_InventoryComponent>(TEXT("Inventory"));
	currentHealth = maxHealth;

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



bool AC_PlayerCharacter::GetInventoryOpen()
{
	return bIsInventoryOpen;
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
	//PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerCharacter::OnBeginOverlap);
	//PlayerCapsule->OnComponentEndOverlap.AddDynamic(this, &AC_PlayerCharacter::OnEndOverlap);
	//-----------------------------------------------------------------------------------
}

void AC_PlayerCharacter::Use()
{

}
void AC_PlayerCharacter::Flashlight()
{
	//
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
void AC_PlayerCharacter::Quit()
{
	UE_LOG(LogTemp, Warning, TEXT("Is Paused%s "), bPaused ? TEXT("True") : TEXT("False"));
	if (GM_Instance->bIsPaused)
	{
		GM_Instance->PauseGame();
		FGenericPlatformMisc::RequestExit(false);
	}
}
void AC_PlayerCharacter::Shoot()
{
	FGun bufferGun = GS_Instance->equippedGun;
	if (bufferGun.bIsItemValid)
	{
		if (bufferGun.currentAmmo > 0)
		{
			//Shooting logic (not 4 now m8)
			bufferGun.currentAmmo -= 1;
		}
	}


	
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

// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAt();
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
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::Inventory);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AC_PlayerCharacter::AttemptToJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AC_PlayerCharacter::AttemptToJump);


	}
}

