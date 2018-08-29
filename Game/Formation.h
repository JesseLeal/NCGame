#pragma once
#include "Entity.h"
#include "Enemy.h"

using Path = std::vector<Vector2D>;

class Formation : public Entity
{
public:
	struct Info
	{
		Enemy::Info enemyInfo;
		float enterTime;
		bool isActive;
	};

public:
	Formation(Scene* scene, const ID& id) : Entity(scene, id) {}
	virtual ~Formation() {}

	void Create();
	void Destroy();
	void Update();

	const Path& GetEnterPath(Enemy::eSide side)
	{
		return m_enterPaths[side];
	}
	const Path& GetRandomAttackPath();

protected:
	std::vector<Info> m_information;
	float m_timer;
	Path m_enterPaths[4];
	std::vector<Path> m_attackPaths;
};