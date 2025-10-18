// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int rowIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int colIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInteractable;
};

USTRUCT(BlueprintType)
struct FGun : public FInventoryItem
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int MaxAmmo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int currentAmmo;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MO_RE_API UC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_InventoryComponent();
	UFUNCTION()
	void AddItem(FInventoryItem item);
	UFUNCTION()
	void MoveItem(int x_old, int y_old, int x_new, int y_new);
	UFUNCTION()
	void RemoveItem(int x, int y);
	UFUNCTION()
	TArray<FInventoryItem> GetInventoryArray();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TArray<FInventoryItem> InventoryArray;
	int tableW;
	int tableH;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
