#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
	Release();
}

void CTitle::Initialize()
{
	m_bTitle = false;
	m_bNextScene = false;
	m_bFileLoad = false;
}

void CTitle::LateInit()
{
}

void CTitle::Update()
{
	if (InputManager->KeyDown(VK_RETURN))
		m_bNextScene = true;


	if (m_bNextScene)
		if (SceneManager->SceneEnd())
			SceneManager->SceneChange(SCENE_STAGE1);
}

void CTitle::LateUpdate()
{
}

void CTitle::Render(HDC hDC)
{
	if (!m_bFileLoad && !m_bTitle)
		DrawBackground(hDC, TEXT("Title_Load"));
	else if(m_bTitle)
		DrawBackground(hDC, TEXT("Title_1"));
	else
		DrawBackground(hDC, TEXT("Title_2"));

	if (!m_bFileLoad && m_bTitle)
	{
		FileLoad();
	}
	else
		if (g_iFrame % 20 == 0)
			m_bTitle = !m_bTitle;
}

void CTitle::Release()
{
	SoundManager->StopSound(CSoundManager::BGM);
}

void CTitle::FileLoad()
{
	// 스테이지 1 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_Stage1_Background"), TEXT("../Image/Map/Stage1_Background.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_1_Ground"), TEXT("../Image/Map/Stage1-1.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_2_Ground"), TEXT("../Image/Map/Stage1-2.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Stage1_3_Ground"), TEXT("../Image/Map/Stage1-3.bmp"));

	// 보스 스테이지 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_Boss_Background"), TEXT("../Image/Map/Boss_Background.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Boss_Ground"), TEXT("../Image/Map/Boss_Ground.bmp"));

	// 중간 보스 스테이지 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_1"), TEXT("../Image/Map/MidBoss_Background_1.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_2"), TEXT("../Image/Map/MidBoss_Background_2.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_3"), TEXT("../Image/Map/MidBoss_Background_3.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Background_4"), TEXT("../Image/Map/MidBoss_Background_4.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_MidBoss_Ground"), TEXT("../Image/Map/MidBoss_Ground.bmp"));

	// 스페셜 스테이지 배경, 땅 로딩
	BmpManager->RegistBitmap(TEXT("Map_Special_Background"), TEXT("../Image/Map/VsMarioBackground.bmp"));
	BmpManager->RegistBitmap(TEXT("Map_Special_Ground"), TEXT("../Image/Map/VsMarioGround.bmp"));

	// 기타 맵 소스
	BmpManager->RegistBitmap(TEXT("Map_Door"), TEXT("../Image/Map/Door.bmp"));

	// 플레이어 이펙트 로딩
	BmpManager->RegistBitmap(TEXT("Normal_Effect"), TEXT("../Image/Effect/Normal_Effect.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Attack_Left"), TEXT("../Image/Effect/NormalAttack_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Attack_Right"), TEXT("../Image/Effect/NormalAttack_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("ShootingStar_Left"), TEXT("../Image/Effect/ShootingStar_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("ShootingStar_Right"), TEXT("../Image/Effect/ShootingStar_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("InhailStar"), TEXT("../Image/Effect/InhailStar.bmp"));
	BmpManager->RegistBitmap(TEXT("Star"), TEXT("../Image/Effect/Star.bmp"));
	BmpManager->RegistBitmap(TEXT("MiniStar"), TEXT("../Image/Effect/MiniStar.bmp"));
	BmpManager->RegistBitmap(TEXT("ClearStar"), TEXT("../Image/Effect/ClearStar.bmp"));
	BmpManager->RegistBitmap(TEXT("Transform_Effect"), TEXT("../Image/Effect/Transform_Effect.bmp"));

	// 플레이어 로딩
	BmpManager->RegistBitmap(TEXT("Normal_Left"), TEXT("../Image/Kirby/Normal_Kirby/Normal_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Normal_Right"), TEXT("../Image/Kirby/Normal_Kirby/Normal_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_Left"), TEXT("../Image/Kirby/Sword_Kirby/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_Right"), TEXT("../Image/Kirby/Sword_Kirby/Right.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_LeftAttack"), TEXT("../Image/Kirby/Sword_Kirby/Left_Attack.bmp"));
	BmpManager->RegistBitmap(TEXT("Sword_RightAttack"), TEXT("../Image/Kirby/Sword_Kirby/Right_Attack.bmp"));

	// 적 캐릭터 로딩
	BmpManager->RegistBitmap(TEXT("Wadorudi_Left"), // 와도루디
		TEXT("../Image/Enemy/Wadorudi/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Wadorudi_Right"),
		TEXT("../Image/Enemy/Wadorudi/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("Scarfy_Left"), // 스컬피
		TEXT("../Image/Enemy/Scarfy/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Scarfy_Right"),
		TEXT("../Image/Enemy/Scarfy/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("SwordKnight_Left"), // 소드 나이트
		TEXT("../Image/Enemy/SwordKnight/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("SwordKnight_Right"),
		TEXT("../Image/Enemy/SwordKnight/Right.bmp"));

	BmpManager->RegistBitmap(TEXT("DDD_Left"), // DDD
		TEXT("../Image/Enemy/DDD/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("DDD_Right"),
		TEXT("../Image/Enemy/DDD/RIght.bmp"));

	BmpManager->RegistBitmap(TEXT("Mario_Left"), // 마리오
		TEXT("../Image/Enemy/Mario/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("Mario_Right"),
		TEXT("../Image/Enemy/Mario/RIght.bmp"));

	BmpManager->RegistBitmap(TEXT("MetaKnight_Apper"), // 메타나이트
		TEXT("../Image/Enemy/MetaKnight/Appear.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Dead"),
		TEXT("../Image/Enemy/MetaKnight/Dead.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Left"),
		TEXT("../Image/Enemy/MetaKnight/Left.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Right"),
		TEXT("../Image/Enemy/MetaKnight/Right.bmp"));

	// 메타나이트 이펙트 로딩
	BmpManager->RegistBitmap(TEXT("MetaKnight_SlashSkill_Left"), TEXT("../Image/Effect/MetaKnight_SlashSkill_Left.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_SlashSkill_Right"), TEXT("../Image/Effect/MetaKnight_SlashSkill_Right.bmp"));
	BmpManager->RegistBitmap(TEXT("MetaKnight_Tornado"), TEXT("../Image/Effect/MetaKnight_Tornado.bmp"));

	// 마리오 이펙트 로딩
	BmpManager->RegistBitmap(TEXT("MarioFire"), TEXT("../Image/Effect/MarioFire.bmp"));

	// UI 로딩
	BmpManager->RegistBitmap(TEXT("PlayerHp"), TEXT("../Image/UI/PlayerHp.bmp"));
	BmpManager->RegistBitmap(TEXT("BossHp"), TEXT("../Image/UI/BossHP.bmp"));	
	BmpManager->RegistBitmap(TEXT("BossName"), TEXT("../Image/UI/BossName.bmp"));

	SoundManager->Initialize();

	SoundManager->PlayBGM(TEXT("Title.mp3"));

	m_bFileLoad = true;
}
