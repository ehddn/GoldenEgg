// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "Monster.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProxBox"));
	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	
	RootComponent = Particles;

	//ProxBox->AttachTo(RootComponent);
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Duration = 3;
	DamagePerSecond = 1;
	TimeAlive = 0;

	

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//search the proxbox for all actors in the volume.
		TArray<AActor*> actors;
	ProxBox->GetOverlappingActors(actors);
	// damage each actor the box overlaps
	for (int c = 0; c < actors.Num(); c++)
	{
		// don't damage the spell caster
		if (actors[c] != Caster)
		{
			
			AMonster* monster = Cast<AMonster>(actors[c]);
			if (monster && ProxBox->IsOverlappingComponent(monster->GetCapsuleComponent()))
			{
				monster->TakeDamage(DamagePerSecond * DeltaTime, FDamageEvent(), 0, this);
			}
			// to damage other class types, try a checked cast here..
		}
	}
	TimeAlive += DeltaTime;
	if (TimeAlive > Duration)
	{
		Destroy();
	}

}

void ASpell::SetCaster(AActor* caster) {
	Caster = caster;
	
	//execK2_AttachRootComponentTo(caster->GetRootComponent());
	K2_AttachRootComponentTo(caster->GetRootComponent());

	//ProxBox->AttachTo(caster->GetRootComponent());
}

