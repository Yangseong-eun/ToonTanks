// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tank.h"
#include "Tower.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 탱크까지의 거리 구한 후 

	if (InFireRange()) 
	{
		RotateTurret(Tank->GetActorLocation());
	}
	
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	//탱크를 어떻게 불러오지? ->GetPlayerPawn 사용
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	//게임 시작 시 타이머가 실행되도록 
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);  //GetWorldTimerManager은 FTimerManager을 반환하고 포인터를 반환하지 않음 
}

void ATower::CheckFireCondition()
{
	//함수를 만들고 이제 타이머를 설정해서 타이머가 실행되고 설정 시간이 지나면 함수가 호출되도록 한다.
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
