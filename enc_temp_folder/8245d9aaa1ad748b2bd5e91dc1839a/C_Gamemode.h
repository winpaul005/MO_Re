// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_Gamemode.generated.h"

/**
 * 
 */
UCLASS()
class MO_RE_API AC_Gamemode : public AGameModeBase
{
	GENERATED_BODY()
	AC_Gamemode();
	public:
		UFUNCTION()
		void PauseGame();
	protected:
		bool bIsPaused;

};
