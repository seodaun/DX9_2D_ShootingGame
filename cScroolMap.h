#pragma once
class cScroolMap
{
private:
	float m_scrool;
	texture* m_backGround;
public:
	cScroolMap(string background);
	~cScroolMap();

	void Update(float speed);
	void Render();

	float GetScrool() { return m_scrool; }
};

