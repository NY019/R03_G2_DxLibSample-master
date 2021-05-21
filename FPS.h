#pragma once


#include "DxLib.h"

#define GAME_FPS 60
#define GAME_FPS_MAX 240
#define GAME_FPS_MIN 60

struct FPS
{
	BOOL IsInitFlg = FALSE;
	LONGLONG  StartTime = 0;
	LONGLONG NowTime = 0;
	LONGLONG OldTime = 0;

	int Value = GAME_FPS;

	float DeltaTime = 0.000001;
	int Count = 1;
	float DrawValue = 0.0f;
	int SampleRate = GAME_FPS;


};

VOID FPSUpdate(VOID);
VOID FPSDraw(VOID);
VOID FPSWait(VOID);