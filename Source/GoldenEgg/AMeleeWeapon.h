// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AMeleeWeapon.generated.h"
class AMonster;

UCLASS()
class GOLDENEGG_API AAMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AAMeleeWeapon)
		float AttackDamage;
	//��Ʈ�� ������Ʈ�� ����� �迭
	TArray<AActor*> ThingsHit;
	//���Ⱑ ��鸮���� �ƴ��� �Ǻ��� �� Ÿ�� ����
	bool Swinging;
	//�ڱ��ڽ��� ��Ʈ���� �ʵ���, ���⸦ ����־ �� ����� ���ظ� ���� �ʵ���

	AMonster *WeaponHolder;
	

	//��Ʈ �Ǻ��� ���� �ݶ��̴�
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		UBoxComponent* ProxBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		UStaticMeshComponent* Mesh;
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Swing();
	void Rest();

};
