// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Avatar.h"
#include"AMeleeWeapon.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"  //Ugameplaystatics ���
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
	//���� �����̱� ����
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;
	FVector playerPos = avatar->GetActorLocation();
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();
	//�þ߾ȿ� �÷��̾ ���ٸ� ���ư���
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius()) {
		//�þ� ���̸� �ƹ��͵� ���ص� ��
		return;
	}
	toPlayer /= distanceToPlayer;  // ���� �븻������ 
	//toPlayer.Normalize(); // unit vector�� ���̱�
	AddMovementInput(toPlayer, Speed * DeltaTime);
	// Ÿ���� ���� toPlayer�������� ������ �����̸� ���� �����̵��� ������ �ٲ���� 
	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0;  //pitch���� ���� ����! y���� �ٲ�� ������ ���ٶ������� 
	RootComponent->SetWorldRotation(toPlayerRotation);
	//���� �����̱� ��


	//���Ͱ� �÷��̾� ����
	if (isInAttackRange(distanceToPlayer)) {
		if (!TimeSinceLastStrike) {
			Attack(avatar);
		}
		TimeSinceLastStrike += DeltaTime;  //��Ӱ��ݸ��ϴ°� ���ϵ��� �ð� ����. ���ݼӵ� 
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

	return distanceToPlayer < AttackRangeSphere->GetScaledSphereRadius(); //���ݹ����ȿ� ������ false��ȯ!
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
