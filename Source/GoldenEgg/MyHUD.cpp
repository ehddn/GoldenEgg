// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

void AMyHUD::DrawHUD()
{
	// call superclass DrawHUD() function first
	Super::DrawHUD();

	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;
	DrawMessages();
	DrawHealthBar();
	DrawWidgets();
	// then proceed to draw your stuff.
	// we can draw lines..
	//DrawLine(200, 300, 400, 500, FLinearColor::Blue);
	// and we can draw text!
	/*DrawText("Greetings from Unreal!", FColor::White,
		0, 0, hudFont);*/


	/*for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// draw the background box the right size
		// for the message
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont,
			1.f);
		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;
		// black backing
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// draw our message using the hudFont
		DrawText(messages[c].message, messages[c].color, x + pad, y + pad, hudFont);
		// reduce lifetime by the time that passed since last
		// frame.
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}*/
}
void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}
void AMyHUD::DrawMessages()
{
	

	for (int c = messages.Num() - 1; c >= 0; c--)
	{
	
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont,
			1.f);
		float messageH = outputHeight + 2.f * pad;
		
		float x = 0.f, y = c * messageH;

		if (messages[c].tex)
		{
			DrawTexture(messages[c].tex, x, y, messageH, messageH, 0, 0, 1, 1);
		}
		else
		{
			DrawRect(FLinearColor::Red, x, y, messageH, messageH);
		}
		x += messageH;

		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// draw our message using the hudFont
		DrawText(messages[c].message, messages[c].color, x + pad, y + pad, hudFont);
		// reduce lifetime by the time that passed since last
		// frame.
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it
		
		// Draw the texture, if there is one
		

		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}

	}
}

void AMyHUD::DrawHealthBar()
{
	// Draw the healthbar.
	
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (avatar->Hp <= 0) {
		return;
	}
	else {
		float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
		float percHp = avatar->Hp / avatar->MaxHp;
		DrawRect(FLinearColor(0, 0, 1, 1), Canvas->SizeX - barWidth - barPad - barMargin,
			Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2 * barPad,
			barHeight + 2 * barPad);
		DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), Canvas->SizeX - barWidth - barMargin, Canvas->SizeY - barHeight - barMargin, barWidth * percHp, barHeight);
	}
	
}

//위젯 출력

void AMyHUD::DrawWidgets() 
{
	for (int c = 0; c < widgets.Num(); c++) 
	{
		DrawTexture(widgets[c].icon.tex, widgets[c].pos.X,
			widgets[c].pos.Y, widgets[c].size.X, widgets[c].size.Y,
			0, 0, 1, 1);
		DrawText(widgets[c].icon.name, FLinearColor::Yellow,
			widgets[c].pos.X, widgets[c].pos.Y, hudFont, .6f,
			false);
	}
}

//위젯 추가

void AMyHUD::addWidget(Widget widget) 
{
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;
	for (int c = 0; c < widgets.Num(); c++) {
		widget.pos.X += widget.size.X + pad.X;
		//오른쪽에 더이상 빈공간이 없으면
		//다음라인으로 넘어감
		if (widget.pos.X + widget.size.X > dims.X) {
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}
	widgets.Add(widget);
}

void AMyHUD::clearWidgets() {
	widgets.Empty();
}

void AMyHUD::MouseClicked() {
	FVector2D mouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);
	heldWidget = NULL;

	for (int c = 0;  c < widgets.Num();  c++) {
		if (widgets[c].hit(mouse)) {
			heldWidget = &widgets[c];
			return;

		}
	}
}

void AMyHUD::MouseMoved() {
	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	dMouse = thisMouse - lastMouse;

	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	if (time > 0.f && heldWidget) {
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y;
	}
	lastMouse = thisMouse;
}


void AMyHUD::MouseRightClicked() {
	

	FVector2D mouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);

	for (int c = 0; c < widgets.Num(); c++) {
		if (widgets[c].hit(mouse)) {
			AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (widgets[c].bpSpell) {
				avatar->CastSpell(widgets[c].bpSpell);
			}
		}
	}
}







