#pragma once

enum OBJ_STATE{ PLAY, DESTROY, WAIT };

enum OBJID 
{
	OBJ_ENEMY, OBJ_UI, OBJ_GROUND, OBJ_INTERECTION, 
	OBJ_PLAYER, PLAYER_ATT, ENEMY_ATT, OBJ_EFFECT, OBJ_END
};

enum SCENEID 
{ 
	SCENE_LOGO, SCENE_TITLE, SCENE_STAGE1, 
	SCENE_MIDBOSS, SCENE_SPECIAL, SCENE_BOSS, 
	SCENE_END
};

enum ENEMYTYPE
{
	EMPTY, NORMAL, SWORD, MARIO, TYPE_BOSS, ENEMYTYPE_END
};

enum HIT_SOUNDTYPE
{
	HIT, SLASH
};