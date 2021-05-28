// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Spell.generated.h"

UCLASS()
class GOLDENEGG_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	virtual void Tick(float DeltaTime) override;
	// box defining volume of damage

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell) // 박스컴포넌트, 데미지 볼륨 설정
		UBoxComponent* ProxBox;
	// the particle visualization of the spell
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)  //파티클 
		UParticleSystemComponent* Particles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)//초당 몇데미지인지
		float DamagePerSecond;               
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell) //주문이 얼마나 지속되는지
		float Duration;

	float TimeAlive;       //레벨에서 주문이 살아있을 시간
	AActor* Caster;          //주문 사용자 형변환하기 위한 변수
	void SetCaster(AActor* caster);  // 주문 사용자 설정해주는 함수



};
