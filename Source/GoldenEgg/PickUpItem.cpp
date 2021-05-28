// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItem.h"
#include "MyHUD.h"
#include "NPC.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APickUpItem::APickUpItem(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = "Unknown";
	Quantity = 0;

	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxShpere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));

	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::Prox);
	ProxSphere->AttachTo(Mesh);
	
}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APickUpItem::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the overlapped actor isn't the player, return
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	// Get a reference to the player, in order to give the item
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// Let the player pick this item up
	avatar->Pickup(this);
	// Get a reference to the controller
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	// Get a reference to the hud
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->addMessage(Message(Icon, FString("Picked up ") + FString::FromInt(Quantity) +
		FString(" ") + Name, 5.f, FColor::White));
	// Destroy this item, as it was picked up
	Destroy();

}
void AAvatar::Pickup(APickUpItem* item)
{
	if (Backpack.Find(item->Name))
	{
		// the item was already in the pack.. increase qty of it 
		Backpack[item->Name] += item->Quantity;
	}
	else
	{
		// the item wasn't in the pack before, add it in now 
		Backpack.Add(item->Name, item->Quantity);
		// record ref to the tex the first time it is picked up 
		Icons.Add(item->Name, item->Icon);

		Classes.Add(item->Name, item->GetClass());
		Spells.Add(item->Name, item->Spell);
	}

	
}





