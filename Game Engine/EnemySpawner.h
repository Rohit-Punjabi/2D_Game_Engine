#pragma once



class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	void NormalEnemySpawner();
	void FireBallSpawner();
	void WallSpawner();

	float RandomGenerator(float lowest, float highest);

public:
	float rand, lowest, highest;
};