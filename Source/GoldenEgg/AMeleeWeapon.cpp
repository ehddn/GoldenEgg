// Fill out your copyright notice in the Description page of Project Settings.

#include "AMeleeWeapon.h"
#include "Monster.h"

// Sets default values
AAMeleeWeapon::AAMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//코드
	AttackDamage = 1;
	Swinging = false;
	WeaponHolder = NULL;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	ProxBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProxBox"));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AAMeleeWeapon::Prox);
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//KeepRelative 상대적 움직임 , KeepWorld월드 기준으로 움직임 , SnapToTarget ? 얘는 뭐냐 / 세가지 규칙 있음

}

// Called when the game starts or when spawned
void AAMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAMeleeWeapon::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherComp != OtherActor->GetRootComponent()) {
		return;
	}
	//검이 swing하지 않을때는 히트하지 않기, 무기사용자에게 히트하지않기, 두번 히트 하지 않기
	if (Swinging && OtherActor != WeaponHolder && !ThingsHit.Contains(OtherActor)) {
		OtherActor->TakeDamage(AttackDamage + WeaponHolder->BaseAttackDamage,
			FDamageEvent(), NULL, this);
		ThingsHit.Add(OtherActor);
	}
}

void AAMeleeWeapon::Swing() {
	ThingsHit.Empty();
	Swinging = true;
}

void AAMeleeWeapon::Rest() {
	ThingsHit.Empty();
	Swinging = false;
}


