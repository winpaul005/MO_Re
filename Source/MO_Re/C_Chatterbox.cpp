// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Chatterbox.h"

// Sets default values for this component's properties
UC_Chatterbox::UC_Chatterbox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->OnAudioFinished.AddDynamic(this,&UC_Chatterbox::Clean);
	Clean();
	// ...
}

void UC_Chatterbox::SpeakCaption(TArray<FCaption> inCaption,USoundBase* inCue)
{
	AudioComponent->SetSound(inCue);
	AudioComponent->Play();
	inCaptionCurr = inCaption;
}

void UC_Chatterbox::Clean()
{
	AudioComponent->Stop();
	AudioComponent->SetSound(nullptr);
	SubtitleCartridge = "";
}

// Called when the game starts
void UC_Chatterbox::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_Chatterbox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(inCaptionCurr.Num() != 0)
	{
		while(inCaptionCurr.Num() != 0)
		{
			curTime += GetWorld()->GetDeltaSeconds();
			if(curTime>=inCaptionCurr[0].Duration)
			{
				inCaptionCurr.RemoveAt(0);
				curTime = 0.0f;
			}
		}
	}
	else
	{
		curTime = 0.0f;
	}
	// ...
}

