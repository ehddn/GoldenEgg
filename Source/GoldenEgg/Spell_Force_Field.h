// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "Components/SphereComponent.h"
#include "Spell_Force_Field.generated.h"

/**
 * 
 */
UCLASS()
class GOLDENEGG_API ASpell_Force_Field : public ASpell
{
	GENERATED_BODY()



public:
	ASpell_Force_Field();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
		USphereComponent* ProxSphere;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
		float Force;

	virtual void Tick(float DeltaSeconds) override;
	
};
