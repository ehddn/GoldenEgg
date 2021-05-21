// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "PickUpItem.h"
#include "MyHUD.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	MaxHp = 500;
	Hp = 200;
	Backpack.Add("Weapon", 1);
	Icons.Add("Weapon", Weapon_Icon);
	Backpack.Add(WTEat, 0);
	Icons.Add(WTEat, Muffin_Icon);
}

// Called every frame
float AAvatar::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, 
	AController*EventInstigator, AActor* DamageCauser) {
	knockback = GetActorLocation() - DamageCauser->GetActorLocation();
	knockback.Normalize();
	knockback *= Damage * 500;

	return knockback.Size();      //에러, 백터형을 플로프형으로 반환할수 없다고 함.
}
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	AddMovementInput(knockback, 1.f);
	knockback *= 0.5f;


}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);

	//인벤토리 액션 매핑
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	PlayerInputComponent->BindAction("EatMuffin", IE_Pressed, this, &AAvatar::EatMuffin);

	//마우스 클릭 액션 매핑
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
}
void AAvatar::MoveForward(float amount)
{
	// Don't enter the body of this function if Controller is 
	// not set up yet, or if the amount to move is equal to 0 
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		// we call AddMovementInput to actually move the 
		// player by `amount` in the `fwd` direction 
		AddMovementInput(fwd, amount);
	}
}
void AAvatar::MoveRight(float amount)
{
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}
void AAvatar::MoveLeft(float amount)
{
	if (Controller && amount)
	{
		FVector left = -GetActorRightVector();
		AddMovementInput(left, amount);
	}
}
void AAvatar::MoveBack(float amount)
{
	if (Controller && amount)
	{
		FVector back = -GetActorForwardVector();
		AddMovementInput(back, amount);
	}
}
void AAvatar::Yaw(float amount)
{
	//인벤토리가 보여지고 잇으면 못움직이게 하기 코드 ㄹㅇ 간단하네 ...ㄷㄷ
	if (inventoryShowing) {
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}
void AAvatar::Pitch(float amount)
{
	AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}


void AAvatar::ToggleInventory() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, "Showing inventory..");
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	//이미 보여지고 있으면 false로 끄기
	if (inventoryShowing)
	{
		hud->clearWidgets();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}
	
	inventoryShowing = true;
	PController->bShowMouseCursor = true;
	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
	{
		FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
		UTexture2D* tex = 0;
		if (Icons.Find(it->Key))
			tex = Icons[it->Key];
		hud->addWidget(Widget(Icon(fs, tex)));

	}

}
void AAvatar::MouseClicked() {
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->MouseClicked();
}

void AAvatar::EatMuffin() {
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	if (Backpack.Find(WTEat)) {  //버그 시작하자 마자 EatMuffine()시전시 게임 팅김 왜?... Backpack에 확인 불가?... else문 밖으로 return 값 지정해줘서 해결
		if (Backpack[WTEat] > 0)
		{   //먹을것의 잔고가 남아있다면
			Backpack[WTEat] = Backpack[WTEat] - 1;  //TMap의 value 값은 바로 수정!

			if (Hp < 500)
			{
				Hp += 100;
			}
			hud->addMessage(Message(Muffin_Icon, "Eat Muffin!", 3.f, FColor::Red));
		}
		else {
			hud->addMessage(Message(Warning, "you dont have any muffin", 3.f, FColor::Red));
		}
	}
	else {
		return;
	}
}





