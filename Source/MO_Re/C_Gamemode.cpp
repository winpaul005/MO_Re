// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Gamemode.h"

AC_Gamemode::AC_Gamemode()
{
	bIsPaused = false;
}

void AC_Gamemode::PauseGame()
{
	if (bIsPaused)
	{
		bIsPaused = false;
	}
	else
	{
		bIsPaused = true;
	}
}
