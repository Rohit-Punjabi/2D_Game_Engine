#pragma once


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update();

	bool CollisionDetector(float Fposx, float Fposy, float Fwidth, float Fheight, float Sposx, float Sposy, float Swidth, float Sheight);
	bool GetCollisionState();
	void CollisionReset();

	int GetEnemyLeftCounter();

	void ResetCounter();

private:
	bool Collision;
	int EnemyLeftCounter;

};
