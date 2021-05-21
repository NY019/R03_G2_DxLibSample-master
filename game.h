#pragma once


#include "DxLib.h"	



#define GAME_TITLE	"ゲームタイトル"	
#define GAME_WIDTH	1280				
#define GAME_HEIGHT	720					
#define GAME_COLOR  32					

#define GAME_ICON_ID	333				
#define GAME_WINDOW_BAR  0

#define GAME_DEBUG TRUE

enum GAME_SCENE {
	GAME_SCENE_TITLE,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_CHANGE
};
