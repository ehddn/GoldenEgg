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
	//히트한 오브젝트를 기록할 배열
	TArray<AActor*> ThingsHit;
	//무기가 흔들리는지 아닌지 판별할 불 타입 변수
	bool Swinging;
	//자기자신은 히트하지 않도록, 무기를 들고있어도 든 대상은 피해를 입지 않도록

	AMonster *WeaponHolder;
	

	//히트 판별을 해줄 콜라이더
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
