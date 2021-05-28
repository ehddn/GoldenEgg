// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Monster.generated.h"
class AAMeleeWeapon;

UCLASS()
class GOLDENEGG_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float HitPoints;
//����ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		int32 Experience;
	//�������Ʈ Ÿ������ �������� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPLoot;
	//���ݽ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float BaseAttackDamage;
	//������ ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float AttackTimeout;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonsterProperties)
		float TimeSinceLastStrike;
	//�þ߹���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonsterProperties)
		USphereComponent* SightSphere;
	//���ݹ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonsterProperties)
		USphereComponent* AttackRangeSphere;

	


	//�Ÿ����� �Լ�.  �ζ��� ��� ª�� �Լ��̹Ƿ� �� ���� ���� ����!
	inline bool isInSightRange(float d) {
		return d < SightSphere->GetScaledSphereRadius();
	}
	inline bool isInAttackRange(float d) {
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}

	//���� �������� �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPMeleeWeapon;
	

	AAMeleeWeapon* MeleeWeapon;
	
	virtual void PostInitializeComponents() override;

	//ĳ���� �ִϸ��̼� ���ݸ��� �����ϱ� ���� �ڵ�
	UFUNCTION(BlueprintCallable, Category = Collision)
		bool isInAttackRangeOfPlayer();

	//���� �ֵθ��� �ڵ�
	UFUNCTION(BlueprintCallable, Category = Collision)
		void SwordSwung();

	//�Ѿ�bullet ��� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPBullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float BulletLaunchImpulse;
	void Attack(AActor* thing);

	//���������� �߰��Ѱ͵� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	FVector knockback;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


};
