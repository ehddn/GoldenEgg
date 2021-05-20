// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Monster.generated.h"

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
//경험치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		int32 Experience;
	//블루프린트 타입으로 아이템을 드랍
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPLoot;
	//공격시 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float BaseAttackDamage;
	//공격후 잠깐 쉬기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float AttackTimeout;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonsterProperties)
		float TimeSinceLastStrike;
	//시야범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonsterProperties)
		USphereComponent* SightSphere;
	//공격범위
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MonsterProperties)
		USphereComponent* AttackRangeSphere;
	//거리측정 함수.  인라인 사용 짧은 함수이므로 더 빨리 실행 가능!
	inline bool isInSightRange(float d) {
		return d < SightSphere->GetScaledSphereRadius();
	}
	inline bool isInAttackRange(float d) {
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}

	//무기 장착관련 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPMeleeWeapon;

	AAMeleeWeapon* MeleeWeapon;
	
	

	//class AAMeleeWeapon;  //?
	virtual void PostInitializeComponents() override;

};
