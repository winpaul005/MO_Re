// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Player.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCI_Player : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MO_RE_API ICI_Player
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Basic")
	int GetHealth();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Basic")
	void Punch(int hitPoints);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Basic")
	void Speak(const FText& speech, float speechDuration);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Basic")
	AActor* GetLookedAtItem();
};
