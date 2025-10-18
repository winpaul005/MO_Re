// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GaymState.h"

AC_GaymState::AC_GaymState()
{

}

void AC_GaymState::SetInventoryOpen(bool bIsOpen)
{
	bIsInventoryOpen = bIsOpen;

}

void AC_GaymState::SwitchInventoryOpen()
{
	if (!bIsInventoryOpen)
	{
		bIsInventoryOpen = true;
	}
	else {
		bIsInventoryOpen = false;
	}
	SwitchDelegate.Broadcast(bIsInventoryOpen);
}

bool AC_GaymState::GetInventoryOpen()
{
	return bIsInventoryOpen;
}
