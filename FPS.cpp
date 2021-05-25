
#include "FPS.h"

FPS fps;

VOID FPSUpdate(VOID)
{
	if (fps.IsInitFlg == FALSE)
	{
		fps.StartTime = GetNowHiPerformanceCount();

		fps.IsInitFlg = TRUE;
	}

	fps.NowTime = GetNowHiPerformanceCount();

	fps.DeltaTime = (fps.NowTime = fps.OldTime) / 1000000.0f;

	fps.OldTime = fps.NowTime;

	if (fps.Count < fps.SampleRate)
	{
		fps.Count++;
	}
	else
	{
		fps.DrawValue = 1000000.0f / ((fps.NowTime - fps.StartTime) / (float)fps.SampleRate);

		fps.StartTime = GetNowHiPerformanceCount();

		fps.Count = 1;
	}

	return;
}

VOID FPSDraw(VOID)
{
	if (GAME_DEBUG == TRUE)
	{
		DrawFormatString(0, GAME_HEIGHT - 20, GetColor(0, 0, 0), "FPS: %.1f", fps.DrawValue);
	}
	return;
}

VOID FPSWait(VOID)
{
	LONGLONG resultTime = fps.NowTime - fps.StartTime;

	LONGLONG waitTime = 1000000.0f / fps.Value * fps.Count - resultTime;

	waitTime /= 1000.0f;

	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	if (GetWaitVSyncFlag() == FALSE)
	{
		if (fps.Value < GAME_FPS_MAX)
		{
			if (waitTime > 0 && waitTime <= 1000.0f / fps.Value)
			{
				//fps.Count++;
				fps.Value++;
			}
			else
			{
				if (fps.Value > GAME_FPS_MIN)
				{
					fps.Value--;
				}
			}
		}
	}
	return;
}