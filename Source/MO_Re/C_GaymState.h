// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_InventoryComponent.h"

#include "GameFramework/GameStateBase.h"
#include "C_GaymState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryStateSwitched, bool, bSwitchState,int,CacheIID);
/**
 * 
 */
UCLASS()
class MO_RE_API AC_GaymState : public AGameStateBase
{
	GENERATED_BODY()
	AC_GaymState();
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryStateSwitched SwitchDelegate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	int cacheItemID = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UC_InventoryComponent* inventoryInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	FGun equippedGun;
	UFUNCTION(BlueprintCallable)
	void SetInventoryOpen(bool bIsOpen);
	UFUNCTION(BlueprintCallable)
	void SwitchInventoryOpen();
	UFUNCTION(BlueprintCallable)
	bool GetInventoryOpen();
	UFUNCTION(BlueprintCallable)
	void SetCacheItem(int IndexID, bool bSwitchToInventoryClosed);
protected:
	bool bIsInventoryOpen;
	bool bIsPaused;
	void SwitchCursor(bool cursorState);
};
