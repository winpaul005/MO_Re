// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MO_RE_API ULaGameInstance : public UGameInstance
{
	GENERATED_BODY()
    public:
        virtual void Init() override;
    
        UFUNCTION()
        virtual void BeginLoadingScreen(const FString& MapName);
        UFUNCTION()
        virtual void EndLoadingScreen(UWorld* InLoadedWorld);
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loading Screen")
        TSubclassOf<class UUserWidget> LoadingScreenWidget;
};
