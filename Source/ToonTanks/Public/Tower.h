// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category="Combat") //탱크에 동일한 사정거리를 적용하기 위해 EditDefaultsOnly-> 디폴트 블루프린트에서만 편집가능,
	float FireRange = 300.f;

private:
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool InFireRange();
};
