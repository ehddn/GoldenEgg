// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "PickUpItem.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->SetSphereRadius(100.f);
	// Code to make ANPC::Prox () run when this proximity sphere
	// overlaps another actor.
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NpcMessage = "Hi, I'm Owen";//default message, can be edited in blueprints

	
	
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
void ANPC::Prox_Implementation(class UPrimitiveComponent*
	OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->addMessage(Message(Face,name+FString(": ")+NpcMessage, 5.f, FColor::White));
	}

	avatar->Getup(this);

	

}
void AAvatar::Getup(ANPC* item)
{
	if (Backpack.Find(item->ItemName))
	{
		// the item was already in the pack.. increase qty of it 
		Backpack[item->ItemName] += item->ItemQuantity;
	}
	else
	{
		// the item wasn't in the pack before, add it in now 
		Backpack.Add(item->ItemName, item->ItemQuantity);
		// record ref to the tex the first time it is picked up 
		Icons.Add(item->ItemName, item->Icon);
	}
	
}





