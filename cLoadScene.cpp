#include "DXUT.h"
#include "cLoadScene.h" 
#include <string>

using namespace std;
cLoadScene::cLoadScene()
{ 
	IMAGEMANAGER->AddImage("Loading", "./Image/Load/load.png");
}


cLoadScene::~cLoadScene()
{
}

void cLoadScene::Init()
{ 
	m_NowLoad = 0; 
	//배경  
	Load("LobbyBg", "./Image/Lobby/BG/LobbyBg.png");
	Load("SeaBg", "./image/InGame/BG/SeaBg.png");   
	Load("PauseBg", "./Image/InGame/BG/PauseBg.png");
	Load("TitleBg", "./Image/Title/BG/TitleBg", 3);
	Load("DamageBg", "./Image/InGame/BG/DamageBg", 5);

	Load("coll", "./Image/coll.png");
	Load("coll2", "./Image/coll2.png");
	//오브젝트 
	Load("PlayerBullet", "./Image/InGame/PlayerBullet.png");
	Load("bullet", "./Image/InGame/bullet", 8);
	Load("SkillFull", "./Image/InGame/UI/SkillFull", 5);
	//UI
	Load("Title_Logo",  "./Image/Title_Logo.png");
	Load("Skill_icon",  "./Image/Lobby/UI/스킬아이콘.png");
	Load("Coin_icon",   "./Image/Lobby/UI/코인아이콘.png");
	Load("Bullet_icon", "./Image/Lobby/UI/탄환아이콘.png");
	Load("Hp_icon",		"./Image/Lobby/UI/하트아이콘.png");
	Load("GameMoney",	"./Image/Lobby/UI/Gamemoney.png");
	Load("L_Skill",		"./Image/Lobby/UI/Lobster_Skill.png");
	Load("J_Skill",		"./Image/Lobby/UI/Jellyfish_Skill.png");
	Load("S_Skill",		"./Image/Lobby/UI/Stingray_Skill.png");
	Load("CharSelect",	"./Image/Lobby/UI/CharSelect.png");
	Load("OptionBg",	"./Image/Lobby/UI/OptionBg.png");
	//캐릭터 스탠딩
	Load("JellyfishChar", "./Image/Lobby/UI/JellyfishChar.png");
	Load("LobsterChar",	  "./Image/Lobby/UI/LobsterChar.png");
	Load("StingrayChar",  "./Image/Lobby/UI/StingrayChar.png");
	Load("Jellyfish",	  "./Image/Lobby/UI/Jellyfish", 3);
	Load("Stingray",      "./Image/Lobby/UI/Stingray", 3);
	Load("Lobster",       "./Image/Lobby/UI/Lobster", 3);	
	Load("start_btn",	  "./Image/Lobby/UI/start_btn", 3);
	Load("Back",		  "./Image/Lobby/UI/Back", 3);
	Load("Lvup",		  "./Image/Lobby/UI/Lvup", 3);
	Load("Help",		  "./Image/Lobby/UI/Help", 3);
	Load("Q",			  "./Image/Lobby/UI/Q", 3);
	Load("X",			  "./Image/Lobby/UI/x", 3);
	Load("Music",		  "./Image/Lobby/UI/Music", 3);
	Load("Credits",		  "./Image/Lobby/UI/Credits", 3);

	Load("Player_1","./Image/InGame/Player/jellyfish.png");
	Load("Player_2","./Image/InGame/Player/lobster.png");
	Load("Player_3","./Image/InGame/Player/stingray.png");
	//Player 
	Load("P1_Skill","./Image/InGame/UI/해파리 스킬",6);
	Load("P2_Skill","./Image/InGame/UI/랍스터 스킬",6);
	Load("P3_Skill","./Image/InGame/UI/가오리 스킬",6); 

	Load("IdlePlayer_1",	"./Image/InGame/Player/Jellyfish/Idle/해파리 애니메이션",6);
	Load("DamagePlayer_1",	"./Image/InGame/Player/Jellyfish/Damage/해파리 애니메이션 피격",3);
	Load("DiePlayer_1",		"./Image/InGame/Player/Jellyfish/Die/해파리 애니메이션 죽음",4);
	Load("IdlePlayer_2",	"./Image/InGame/Player/Lobster/Idle/Lobster",6);
	Load("DiePlayer_2",		"./Image/InGame/Player/Lobster/Die/Lobster_die",4);
	Load("DamagePlayer_2",	"./Image/InGame/Player/Lobster/Damage/Lobster_attack",3);
	Load("IdlePlayer_3",	"./Image/InGame/Player/Stingray/Idle/가오리 애니메이션",6);
	Load("DiePlayer_3",		"./Image/InGame/Player/Stingray/Die/가오리 애니메이션 죽음",4);
	Load("DamagePlayer_3",	"./Image/InGame/Player/Stingray/Damage/가오리 애니메이션 피격",3);
	//Enemy
	Load("IdleSquid",	"./Image/InGame/Enemy/Squid/Idle/squid",6);
	Load("DieSquid",	"./Image/InGame/Enemy/Squid/Die/squid_die",4);
	Load("DamageSquid",	"./Image/InGame/Enemy/Squid/Die/squid_die",4);

	Load("IdleAnglerfish", "./Image/InGame/Enemy/Anglerfish/Idle/d", 6);
	Load("DieAnglerfish", "./Image/InGame/Enemy/Anglerfish/Die/devilfish", 4);
	Load("DamageAnglerfish", "./Image/InGame/Enemy/Anglerfish/Die/devilfish", 4);

	Load("IdleFish", "./Image/InGame/Enemy/Fish/Idle/f", 6);
	Load("DieFish", "./Image/InGame/Enemy/Fish/Die/f", 4);
	Load("DamageFish", "./Image/InGame/Enemy/Fish/Die/f", 4);
	//effect
	Load("DamageEffect", "./Image/InGame/Effect/타격 이펙트", 5);
	Load("BackBtn" ,	"./Image/InGame/UI/BackBtn", 3);
	Load("ContinueBtn" ,"./Image/InGame/UI/ContinueBtn", 3);
	Load("RestartBtn" , "./Image/InGame/UI/RestartBtn", 3);
	m_MaxLoad = m_Load.size();
}

void cLoadScene::Update()
{
	if (m_NowLoad != m_MaxLoad && m_Load[m_NowLoad].count >1) { 
		for (int i = 0; i < m_Load[m_NowLoad].count; i++) { 
			IMAGEMANAGER->AddImage(
				m_Load[m_NowLoad].key + "_" + to_string(i),
				m_Load[m_NowLoad].path + "_" + to_string(i)+".png"
			);
		}
		m_NowLoad++;
	}
	else if (m_NowLoad != m_MaxLoad) { 
		IMAGEMANAGER->AddImage(
			m_Load[m_NowLoad].key,
			m_Load[m_NowLoad].path
		);
		m_NowLoad++;
	}
	else {
		GAMEMANAGER->Init();
		SCENEMANAGER->ChangeScene("Title");
	}
}

void cLoadScene::Render()
{
	RECT a;
	a = {
		0,0,500,70
	};
	a.right = a.right * (float)m_NowLoad / (float)m_MaxLoad; 
	IMAGEMANAGER->CropRender(IMAGEMANAGER->FindImage("Loading"), 300, 300,&a);
	FONTMANAGER->sDrawText(780, 100, "Loading...", 50);    
}

void cLoadScene::Release()
{

}
 