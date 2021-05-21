// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Avatar.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;  //틱 필요없음!

	Damage = 100;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProxSphere"));
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::Prox);
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); //중요! 복습하기



}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	avatar->Hp -= 10;
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, "Bullet hit");
	if (OtherActor == Firer) {
		return;     //총알이 쏜 사람은 때리지 못하도록
	}

	if (OtherComp != OtherActor->GetRootComponent()) {
		return;
	}
	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);

	Destroy();
	
	
	
}
