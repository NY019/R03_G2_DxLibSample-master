#include "Keyboard.h"

KEYBOARD keyboard;


VOID AllKeyUpdate(VOID)
{
	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		keyboard.OldAllKeyState[i] = keyboard.AllKeyState[i];
	}
	GetHitKeyStateAll(keyboard.TempKeyState);

	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		if (keyboard.TempKeyState[i] != 0)
		{
			keyboard.AllKeyState[i]++;
		}
		else
		{
			keyboard.AllKeyState[i] = 0;
		}
	}

	return;
}

BOOL KeyDown(int KEY_INPUT_)
{
	if (keyboard.AllKeyState[KEY_INPUT_] != 0) 
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL KeyUp(int KEY_INPUT_)
{
	if (keyboard.OldAllKeyState[KEY_INPUT_] != 0
		&&keyboard.AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL KeyClick(int KEY_INPUT_)
{
	if (keyboard.OldAllKeyState[KEY_INPUT_] != 0
		&& keyboard.AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL KeyDownKeep(int KEY_INPUT_, int MillTime)
{
	float MilliSec = 1000.0f;

	int UpdateTime = (MillTime / MilliSec) * 60;

	if (keyboard.AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}