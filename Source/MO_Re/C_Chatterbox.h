// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "C_Chatterbox.generated.h"
USTRUCT(BlueprintType)
struct FCaption
{
	GENERATED_BODY()
	FString speech;
	float Duration;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MO_RE_API UC_Chatterbox : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_Chatterbox();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SubtitleCartridge;
	UFUNCTION(BlueprintCallable)
	virtual void SpeakCaption(TArray<FCaption> inCaption,USoundBase* inCue);
	UFUNCTION(BlueprintCallable)
	virtual void Clean();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float curTime = 0.0f;
	TArray<FCaption> inCaptionCurr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
