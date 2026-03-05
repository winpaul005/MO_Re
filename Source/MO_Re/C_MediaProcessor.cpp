// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MediaProcessor.h"

// Sets default values for this component's properties
UC_MediaProcessor::UC_MediaProcessor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UC_MediaProcessor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_MediaProcessor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

