// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickUpItem.h"
#include "NPC.generated.h"

UCLASS()
class GOLDENEGG_API ANPC : public ACharacter
{
	GENERATED_BODY()

	

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FString NpcMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
	UTexture2D* Face;

	
	
	
	

	void SpawnItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		class USphereComponent* ProxSphere;
	// Triggered when the sphere is messed with
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	int32 ItemQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	UTexture2D* Icon;

};
