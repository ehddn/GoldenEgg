// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickUpItem.h"
#include "NPC.h"
#include "Avatar.generated.h"

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

	


public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//ĳ���� ������
	void MoveForward(float amount);
	void MoveRight(float amount);
	void MoveLeft(float amount);
	void MoveBack(float amount);
	void Yaw(float amount);
	void Pitch(float amount);
	
	//ĳ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString WTEat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	UTexture2D* Warning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	UTexture2D* Muffin_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item);
	UTexture2D* Weapon_Icon;
	//�κ��丮 �߰�
	UPROPERTY()
	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> Icons;
	bool inventoryShowing;

	void Pickup(APickUpItem* item); 
	void Getup(ANPC* item);  //���� ���� �Լ�

	
	
	

	//�κ��丮 ���
	void ToggleInventory();
	void EatMuffin();
	
	

	void MouseClicked();

	

	//ĳ���Ͱ� ������ ������ �ʿ��� �ڵ�
	FVector knockback;
	virtual float TakeDamage(float Damage, struct
		FDamageEvent const& DamageEvent, AController*
		EventInstigator, AActor* DamageCauser) override;

};
