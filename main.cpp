#include "game.h"
#include "Keyboard.h"
#include "FPS.h"


struct CHARACTOR 
{
	int handle = -1;
	char path[255];
	int x;
	int y;
	int width;
	int height;
	int speed = 1;

	RECT coll;

	BOOL IsDraw = FALSE;
};

GAME_SCENE GameScene;
GAME_SCENE OldGameScene;
GAME_SCENE NextGameScene;

CHARACTOR player;
	
BOOL IsFadeOut = FALSE;
BOOL IsFadeIn  = FALSE;

int fadeTimeMill = 2000;
int fadeTimeMax = fadeTimeMill / 1000 * 60;

int fadeOutCntInit = 0;
int fadeOutCnt = fadeOutCntInit;
int fadeOutCntMax = fadeTimeMax;

int fadeInCntInit = fadeTimeMax;
int fadeInCnt = fadeInCntInit;
int fadeInCntMax = fadeTimeMax;

VOID Title(VOID);
VOID TitleProc(VOID);
VOID TitleDraw(VOID);

VOID Play(VOID);
VOID PlayProc(VOID);
VOID PlayDraw(VOID);

VOID End(VOID);
VOID EndProc(VOID);
VOID EndDraw(VOID);

VOID Change(VOID);
VOID ChangeProc(VOID);
VOID ChangeDraw(VOID);

VOID ChangeScene(GAME_SCENE scene);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);								
	SetMainWindowText(GAME_TITLE);						
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);				
	SetBackgroundColor(255, 255, 255);					
	SetWindowIconID(GAME_ICON_ID);	           
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetWaitVSyncFlag(TRUE);
	SetAlwaysRunFlag(TRUE);


	
	if (DxLib_Init() == -1){ return -1 ;}
	SetDrawScreen(DX_SCREEN_BACK);

	GameScene = GAME_SCENE_TITLE;

	strcpyDx(player.path, ".\\IMAGE\\player.png");
	player.handle = LoadGraph(player.path);

	if (player.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), player.path, "画像読み込みエラー", MB_OK);

		DxLib_End();

		return -1;
	}

	GetGraphSize(player.handle, &player.width, &player.height);

	player.x = GAME_WIDTH / 2 - player.width / 2;
	player.y = GAME_HEIGHT / 2 - player.height / 2;
	player.speed = 5;
	player.IsDraw = TRUE;

	//∞ループ
	while (1)
	{
		
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		AllKeyUpdate();

		FPSUpdate();

		if (KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break; }

		if (GameScene != GAME_SCENE_CHANGE)
		{
			OldGameScene = GameScene;
		}

		switch (GameScene)
		{
		case GAME_SCENE_TITLE:
			Title();
			break;
		case GAME_SCENE_PLAY:
			Play();
			break;
		case GAME_SCENE_END:
			End();
			break;
		case GAME_SCENE_CHANGE:
			Change();
			break;
		default:
			break;
		}

		if (OldGameScene != GameScene)
		{
			if (GameScene != GAME_SCENE_CHANGE)
			{
				NextGameScene = GameScene;
				GameScene  = GAME_SCENE_CHANGE;
			}
		}

		FPSDraw();

		FPSWait();

		ScreenFlip(); 
	}
	
	DeleteGraph(player.handle);

	DxLib_End();

	return 0;	
}

VOID ChangeScene(GAME_SCENE scene)
{
	GameScene = scene;
	IsFadeIn = FALSE;
	IsFadeOut = TRUE;
}

VOID Title(VOID)
{
	TitleProc();
	TitleDraw();
	return;
}

VOID TitleProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		ChangeScene(GAME_SCENE_PLAY);
	}

	return;
}

VOID TitleDraw(VOID)
{
	DrawString(0, 0, "タイトル画面", GetColor(0, 0, 0));
	return;
}

VOID Play(VOID)
{
	PlayProc();
	PlayDraw();
	return;
}


VOID PlayProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		ChangeScene(GAME_SCENE_END);
	}
	return;
}

VOID PlayDraw(VOID)
{
	if (player.IsDraw == TRUE)
	{
		DrawGraph(player.x, player.y, player.handle, TRUE);
	}

	DrawString(0, 0, "プレイ画面", GetColor(0, 0, 0));
	return;
}
VOID End(VOID)
{
	EndProc();
	EndDraw();
	return;
}

VOID EndProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		ChangeScene(GAME_SCENE_TITLE);
	}
	return;
}

VOID EndDraw(VOID)
{
	DrawString(0, 0, "エンド画面", GetColor(0, 0, 0));
	return;
}

VOID Change(VOID)
{
	ChangeProc();
	ChangeDraw();
	return;
}

VOID ChangeProc(VOID)
{
	if (IsFadeIn == TRUE)
	{
		if (fadeInCnt > fadeInCntMax)
		{
			fadeInCnt++;
		}
		else
		{
			fadeInCnt = fadeInCntInit;
			IsFadeIn = FALSE;
		}
	}

	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt > fadeOutCntMax)
		{
			fadeOutCnt++;
		}
		else
		{
			fadeOutCnt = fadeOutCntInit;
			IsFadeOut = FALSE;
		}
	}

	if (IsFadeIn == FALSE && IsFadeOut == FALSE) 
	{
		GameScene = NextGameScene;
		OldGameScene = GameScene;
	}
	return;
}

VOID ChangeDraw(VOID)
{
	switch (OldGameScene)
	{
	case GAME_SCENE_TITLE:
		TitleDraw();
		break;
	case GAME_SCENE_PLAY:
		PlayDraw();
		break; 
	case GAME_SCENE_END:
		EndDraw();
			break;
	default:
		break;
	}

	if (IsFadeIn == TRUE)
	{
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, ((float)fadeInCnt / fadeInCntMax) * 255);
	}

	if (IsFadeOut == TRUE)
	{
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, ((float)fadeOutCnt / fadeOutCntMax) * 255);
	}

	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "切り替え画面", GetColor(0, 0, 0));
	return;
}