// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Avatar.h"
#include"AMeleeWeapon.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"  //Ugameplaystatics 헤더
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20.f;
	HitPoints = 20;
	Experience = 0;
	BPLoot = NULL;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;
	SightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	//SightSphere->AttachTo(RootComponent);
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	//AttackRangeSphere->AttachTo(RootComponent);
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//몬스터 움직이기 시작
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;
	FVector playerPos = avatar->GetActorLocation();
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();
	//시야안에 플레이어가 없다면 돌아가기
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius()) {
		//시야 밖이면 아무것도 안해도 됨
		return;
	}
	toPlayer /= distanceToPlayer;  // 벡터 노말라이즈 
	//toPlayer.Normalize(); // unit vector로 줄이기
	AddMovementInput(toPlayer, Speed * DeltaTime);
	// 타겟을 보고 toPlayer방향으로 유저가 움직이면 따라서 움직이도록 방향을 바꿔야함 
	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0;  //pitch값은 변경 없음! y값이 바뀌면 앞으로 꼬꾸라질거임 
	RootComponent->SetWorldRotation(toPlayerRotation);
	//몬스터 움직이기 끝


	//몬스터가 플레이어 공격
	if (isInAttackRange(distanceToPlayer)) {
		if (!TimeSinceLastStrike) {
			Attack(avatar);
		}
		TimeSinceLastStrike += DeltaTime;  //계속공격만하는건 못하도록 시간 설정. 공격속도 
		if (TimeSinceLastStrike > AttackTimeout) {
			TimeSinceLastStrike = 0;
		}
		return;
	}
	else {
		AddMovementInput(toPlayer, Speed * DeltaTime);
	}
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMonster::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (BPMeleeWeapon) {
		MeleeWeapon = GetWorld()->SpawnActor<AAMeleeWeapon>(BPMeleeWeapon, FVector(), FRotator());
		if (MeleeWeapon) {
			const USkeletalMeshSocket* socket = this->GetMesh()->GetSocketByName("RightHandSocket");
			
			socket->AttachActor(MeleeWeapon, this->GetMesh());
		}
	}
}

bool AMonster::isInAttackRangeOfPlayer() {
	AAvatar* avater = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avater) return false;

	FVector playerPos = avater->GetActorLocation();
	FVector toPlayer = playerPos - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();

	return distanceToPlayer < AttackRangeSphere->GetScaledSphereRadius(); //공격범위안에 없으면 false반환!
}

void AMonster::SwordSwung() {
	if (MeleeWeapon) {
		MeleeWeapon->Swing();
	}
}

void AMonster::Attack(AActor* thing) {
	if (MeleeWeapon) {
		MeleeWeapon->Swing();
	}
	else if (BPBullet) {
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("RightHand");
		nozzle += fwd * 155;
		FVector toOpponent = thing->GetActorLocation() - nozzle;
		toOpponent.Normalize();
		ABullet* bullet = GetWorld()->SpawnActor <ABullet>(BPBullet, nozzle, RootComponent->GetComponentRotation());

		if (bullet) {
			bullet->Firer = this;
			bullet->ProxSphere->AddImpulse(fwd * BulletLaunchImpulse);
		}
		else {
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, "Monster: No bullet actor could be spawned. is the bullet overlapping something? ");
		}

	}
}
