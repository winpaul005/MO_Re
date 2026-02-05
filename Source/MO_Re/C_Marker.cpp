// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Marker.h"

// Sets default values
AC_Marker::AC_Marker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AC_Marker::CompleteMarker()
{
	Destroy();
}

// Called when the game starts or when spawned
void AC_Marker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Marker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

