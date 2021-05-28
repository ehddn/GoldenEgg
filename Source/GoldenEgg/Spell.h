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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell) // �ڽ�������Ʈ, ������ ���� ����
		UBoxComponent* ProxBox;
	// the particle visualization of the spell
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)  //��ƼŬ 
		UParticleSystemComponent* Particles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)//�ʴ� ���������
		float DamagePerSecond;               
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell) //�ֹ��� �󸶳� ���ӵǴ���
		float Duration;

	float TimeAlive;       //�������� �ֹ��� ������� �ð�
	AActor* Caster;          //�ֹ� ����� ����ȯ�ϱ� ���� ����
	void SetCaster(AActor* caster);  // �ֹ� ����� �������ִ� �Լ�



};
