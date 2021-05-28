// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "PickUpItem.generated.h"

UCLASS()
class GOLDENEGG_API APickUpItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItem(const FObjectInitializer& ObjectInitializer);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//아이템 픽업에 필요한 변수 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	FString Name;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	//FString Muffin="Muffin";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	USphereComponent* ProxSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	UTexture2D* Icon;

	

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*
			OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	//spell
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UClass* Spell;
	
};
