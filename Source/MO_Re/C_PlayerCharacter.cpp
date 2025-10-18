// Fill out your copyright notice in the Description page of Project Settings.
#include "C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

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


}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	//PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerCharacter::OnBeginOverlap);
	//PlayerCapsule->OnComponentEndOverlap.AddDynamic(this, &AC_PlayerCharacter::OnEndOverlap);
	//-----------------------------------------------------------------------------------
}

void AC_PlayerCharacter::Use()
{

}
void AC_PlayerCharacter::Pause()
{
	GM_Instance->PauseGame();
	
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
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.Y * FLookFactor);
		AddControllerPitchInput(LookAxisVector.X * FLookFactor);
	}
}

// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::Jump);


	}
}

