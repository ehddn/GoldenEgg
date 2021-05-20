// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


struct Message
{
	FString message;
	float time;
	FColor color;
	FColor fontColor;
	FColor backColor;
	UTexture2D* tex;

	Message()
	{
		tex = 0;
		time = 5.f;
		color = FColor::White;
	}
	Message(FString iMessage, float iTime, FColor iColor)
	{
		message = iMessage;
		time = iTime;
		color = iColor;
	}
	Message(UTexture2D* iTex, FString iMessage, float iTime, FColor iColor)
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		color = iColor;
	}
	Message(UTexture2D* iTex, FString iMessage, float iTime, FColor iFontColor, FColor iBackColor) 
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		fontColor = iFontColor;
		backColor = iBackColor;
	}

};
struct Icon
{
	FString name;
	UTexture2D* tex;
	Icon() { name = "unknown ICON"; tex = 0; }
	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}
};

struct Widget
{
	Icon icon;
	FVector2D pos, size;
	Widget(Icon iicon)
	{
		icon = iicon;
	}
	float left() { return pos.X; }
	float right() {return pos.X + size.X;}
	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }

	bool hit(FVector2D p) {
		return p.X > left() && p.X<right() && p.Y>top() && p.Y < bottom();
	}

};


UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;
	virtual void DrawHUD() override;
	

	TArray<Message> messages;
	void addMessage(Message msg);
	void DrawMessages();
	void DrawHealthBar();


	void DrawWidgets();
	TArray<Widget> widgets;
	FVector2D dims;

	void clearWidgets();
	void addWidget(Widget widget);


	void MouseClicked();
	Widget* heldWidget;
	void MouseMoved();
};


