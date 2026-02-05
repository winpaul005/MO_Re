// Fill out your copyright notice in the Description page of Project Settings.


#include "C_InventoryComponent.h"
#include "C_PlayerCharacter.h"

AC_PlayerCharacter* PlayerCharacter;
// Sets default values for this component's properties
UC_InventoryComponent::UC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PlayerCharacter = Cast<AC_PlayerCharacter>(GetOwner());
	// ...
}

void UC_InventoryComponent::AddItem(FInventoryItem item)
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to add Item...."));

	if (InventoryArray.Num() >= maxItems)
	{
		// nope
		UE_LOG(LogTemp, Warning, TEXT("Could not add...."));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Added successfully...."));

		InventoryArray.Add(item);
		InventoryArray[InventoryArray.Num() - 1].rowIndex = ((InventoryArray.Num() - 1) / 3);
		InventoryArray[InventoryArray.Num() - 1].colIndex = ((InventoryArray.Num() - 1) % 3);
		InventoryArray[InventoryArray.Num() - 1].bIsItemValid = true;
	}
}

void UC_InventoryComponent::MoveItem(int x_old, int y_old, int x_new, int y_new)
{
	// 2 lazy to implement
}

void UC_InventoryComponent::RemoveItem(int x, int y)
{
	if ((x * y)<InventoryArray.Num())
	{
		InventoryArray.RemoveAt(((x * y) - 1));
	}
}

TArray<FInventoryItem> UC_InventoryComponent::GetInventoryArray()
{
	return InventoryArray;
}


void UC_InventoryComponent::AddGun(FGun SourceGun)
{
	if (CurrentGun.bIsItemValid)
	{
		//Here spawn the gun in front of us
	}
	CurrentGun = SourceGun;
	CurrentGun.bIsItemValid = true;
	PlayerCharacter->ViewportGunMesh->SetSkeletalMesh(CurrentGun.ViewportMesh);
}

void UC_InventoryComponent::AddAmmo(int AmmoDelta)
{
	if (CurrentGun.bIsItemValid)
	{
		if ((CurrentGun.currentAmmo + AmmoDelta) <= CurrentGun.MaxAmmo)
		{
			CurrentGun.currentAmmo += AmmoDelta;
		}
	}
}

// Called when the game starts
void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}