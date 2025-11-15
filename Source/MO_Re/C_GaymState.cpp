// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GaymState.h"
#include "C_PlayerCharacter.h"

AC_GaymState::AC_GaymState()
{

}

void AC_GaymState::BeginPlay()
{
	Super::BeginPlay();
	inventoryInstance = Cast<AC_PlayerCharacter>(GetWorld()->GetWorld()->GetFirstPlayerController()->GetCharacter())->InventoryComponent;

}

void AC_GaymState::SetInventoryOpen(bool bIsOpen)
{
	bIsInventoryOpen = bIsOpen;
	if (bIsInventoryOpen)
	{
		SwitchCursor(true);


	}
	else
	{
		SwitchCursor(false);



	}
	SwitchDelegate.Broadcast(bIsInventoryOpen, cacheItemID);
}

void AC_GaymState::SwitchInventoryOpen()
{
	if (!bIsInventoryOpen)
	{
		bIsInventoryOpen = true;
		SwitchCursor(true);



	}
	else {
		bIsInventoryOpen = false;
		SwitchCursor(false);


	}
	SwitchDelegate.Broadcast(bIsInventoryOpen, cacheItemID);
}

bool AC_GaymState::GetInventoryOpen()
{
	return bIsInventoryOpen;
}

void AC_GaymState::SetCacheItem(int IndexID, bool bSwitchToInventoryClosed)
{
	cacheItemID = IndexID;
	if (bSwitchToInventoryClosed)
	{
		SetInventoryOpen(false);
	}
}

void AC_GaymState::SwitchCursor(bool cursorState)
{
	if (cursorState)
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		Cast<AC_PlayerCharacter>(GetWorld()->GetWorld()->GetFirstPlayerController()->GetCharacter())->bCanLook = false;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		Cast<AC_PlayerCharacter>(GetWorld()->GetWorld()->GetFirstPlayerController()->GetCharacter())->bCanLook = true;

	}
}
