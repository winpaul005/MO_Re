// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "C_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(BlueprintReadWrite, AdvancedDisplay)
	bool bIsItemValid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* ViewportMesh;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int rowIndex;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int colIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USceneComponent> ItemClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInteractable;
};
UENUM(BlueprintType)
enum EShootingPattern : uint8
{
	Single,
	FullAuto
};

USTRUCT(BlueprintType)
struct FGun : public FInventoryItem
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxAmmo;
	UPROPERTY(BlueprintReadWrite, AdvancedDisplay)
	int currentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PewSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EShootingPattern> shootPattern;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsTooHeavy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float shootCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float shootWarmup;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MO_RE_API UC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_InventoryComponent();
	UFUNCTION(BlueprintCallable)
	void AddItem(FInventoryItem item);
	UFUNCTION(BlueprintCallable)
	void MoveItem(int x_old, int y_old, int x_new, int y_new);
	UFUNCTION(BlueprintCallable)
	void RemoveItem(int x, int y);
	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItem> GetInventoryArray();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)

	TArray<FInventoryItem> InventoryArray;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGun CurrentGun;
	UFUNCTION(BlueprintCallable)
	void AddGun(FGun SourceGun);
	UFUNCTION(BlueprintCallable)
	void AddAmmo(int AmmoDelta);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int maxItems = 9;
	//AC_PlayerCharacter* player_C;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
