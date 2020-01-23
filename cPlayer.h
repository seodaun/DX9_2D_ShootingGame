#pragma once    
class cBullet; 
class cEnemy;
class cFps;
class cPlayer
{
private:
	int m_hp;
	int m_bulletSpeed;
	int m_skill;
	bool bDead = false;
	bool m_bInvincible =false; //무적인 상태 
	bool m_bSkill = false;
	float m_InvincibleTime;//무적 시간 
	bool m_succession = false; //연발
	int m_MaxBullet =0;
	int m_cntBullet =0;
	bool bskillfull = false;
private:
	cFps* m_InvincibleFps;
	CHARACTER_STATE m_pState;
	CHARACTER m_character;
	texture* m_playerImage[CHARACTER_KIND];
	texture* m_SkillGauge[6]; 
	cAnimation* m_PlayerAni[CHARACTER_KIND][STATE_KIND]; 
	cAnimation* m_skillFullAni; 
	cAnimation* m_DamageBgAni; 
	D3DXVECTOR2 m_playerPos; 

	POINT m_beforePos;
	POINT m_afterPos; 
	bool bDamage = false;
	int m_cntKillEnemy;
	int m_Gauge;
	int maxHp;
private:
	bool bMouseColl(D3DXVECTOR2 bulletpos, POINT mousepos, int w, int h);
	cBullet* bMouseColl(POINT mousePos);
	cBullet* bCatchBullet();
	void PlayerColl();  
	void JellyfishSkill();
	void LobsterSkill();
	void StingraySkill();
	void Succession(cBullet* bullet); //연발  
	void Fire(cBullet* bullet, POINT mousepos);
public:
	cPlayer();
	~cPlayer();
	void StatInit();
	void Init();
	void Update();
	void Render();
	void Release(); 
public:
	bool isDead() { return m_hp <= 0; }
	bool chkDead() { return bDead && m_pState == eDIE; } 
	void Heal(int hill) { if(maxHp>m_hp)m_hp += hill; };
	void Damage(int damage) {
		if (!m_bInvincible) {
			bDamage = true;
			m_hp -= damage;
			m_PlayerAni[m_character][eDAMAGE]->SetActive(true);
			m_pState = CHARACTER_STATE::eDAMAGE;
			if (isDead()) m_pState = CHARACTER_STATE::eDIE;
		}
	}
	int getHp() { return m_hp; };
	D3DXVECTOR2 GetPos() { return m_playerPos; }
};

