// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include"MyPawn.h"
#include"MyPlayerController.h"
//COD 기본 값 초기화 용 언리얼에서는 new 키워드 못쓰고 NewObject로 사용
AMyGameModeBase::AMyGameModeBase()
{
	//UE_LOG(LogTemp, Warning, TEXT("안녕하세요"));
	DefaultPawnClass = AMyPawn::StaticClass(); //mean ->anpawn의 이름
	//C++에서는 클래스 이름을 가르치는 방법이 없어서 CDO의 포인터를 가리킴
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
