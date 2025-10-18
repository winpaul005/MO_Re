// Fill out your copyright notice in the Description page of Project Settings.
#include "LaGameInstance.h"
#include "MoviePlayer.h"
#include "Slate.h"
#include "Runtime/UMG/Public/UMG.h" 

void ULaGameInstance::Init()
{
    Super::Init();

    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ULaGameInstance::BeginLoadingScreen);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ULaGameInstance::EndLoadingScreen);
}

void ULaGameInstance::BeginLoadingScreen(const FString& InMapName)
{
    if (!IsRunningDedicatedServer())
    {
        FLoadingScreenAttributes LoadingScreen;
        LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidget);
        LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();

        GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
    }
}

void ULaGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{

}
