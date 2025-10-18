// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_InventoryComponent.h"

#include "GameFramework/GameStateBase.h"
#include "C_GaymState.generated.h"

/**
 * 
 */
UCLASS()
class MO_RE_API AC_GaymState : public AGameStateBase
{
	GENERATED_BODY()
	AC_GaymState();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	FInventoryItem cacheItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	FGun equippedGun;
};
