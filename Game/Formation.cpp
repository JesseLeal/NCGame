#include "Formation.h"
#include "Timer.h"

void Formation::Create()
{
	m_enterPaths[0] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
	m_enterPaths[1] = { Vector2D(300.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };
	m_enterPaths[2] = { Vector2D(-64.0f, 500.0f), Vector2D(50.0f, 450.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 450.0f) };
	m_enterPaths[3] = { Vector2D(864.0f, 500.0f), Vector2D(750.0f, 450.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 450.0f) };

	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(550.0f, 350.0f), Vector2D(600.0f, 400.0f), Vector2D(300.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(250.0f, 250.0f), Vector2D(300.0f, 350.0f), Vector2D(250.0f, 450.f), Vector2D(300.0f, 550.0f), Vector2D(250.0f, 650.f) });
	m_attackPaths.push_back({ Vector2D(50.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(550.0f, 650.f) });
	m_attackPaths.push_back({ Vector2D(400.0f, 400.0f), Vector2D(500.0f, 350.0f), Vector2D(300.0f, 450.f), Vector2D(400.0f, 700.0f) });

	m_information =
	{ { { Enemy::BOSS, Enemy::LEFT_LOW, 300.0f, Vector2D(240.0f, 40.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(180.0f, 160.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(220.0f, 160.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(180.0f, 200.0f), this }, 1.05f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(220.0f, 200.0f), this }, 1.4f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(260.0f, 160.0f), this }, 1.75f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(300.0f, 160.0f), this }, 2.1f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(260.0f, 200.0f), this }, 2.45f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(300.0f, 200.0f), this }, 2.8f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(340.0f, 160.0f), this }, 3.15f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(380.0f, 160.0f), this }, 3.5f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(340.0f, 200.0f), this }, 3.85f, false },
	{ { Enemy::BEE, Enemy::LEFT_LOW, 300.0f, Vector2D(380.0f, 200.0f), this }, 4.2f, false },
		//
	{ { Enemy::BOSS, Enemy::RIGHT_LOW, 300.0f, Vector2D(560.0f, 40.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(620.0f, 160.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(580.0f, 160.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(620.0f, 200.0f), this }, 1.05f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(580.0f, 200.0f), this }, 1.4f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(540.0f, 160.0f), this }, 1.75f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(500.0f, 160.0f), this }, 2.1f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(540.0f, 200.0f), this }, 2.45f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(500.0f, 200.0f), this }, 2.8f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(460.0f, 160.0f), this }, 3.15f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(420.0f, 160.0f), this }, 3.5f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(460.0f, 200.0f), this }, 3.85f, false },
	{ { Enemy::BEE, Enemy::RIGHT_LOW, 300.0f, Vector2D(420.0f, 200.0f), this }, 4.2f, false },
		//
	{ { Enemy::BOSS, Enemy::LEFT_TOP, 300.0f, Vector2D(320.0f, 40.0f), this }, 0.0f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(180.0f, 80.0f), this }, 0.35f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(220.0f, 80.0f), this }, 0.7f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(180.0f, 120.0f), this }, 1.05f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(220.0f, 120.0f), this }, 1.4f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(260.0f, 80.0f), this }, 1.75f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(300.0f, 80.0f), this }, 2.1f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(260.0f, 120.0f), this }, 2.45f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(300.0f, 120.0f), this }, 2.8f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(340.0f, 80.0f), this }, 3.15f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(380.0f, 80.0f), this }, 3.5f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(340.0f, 120.0f), this }, 3.85f, false },
	{ { Enemy::BUG, Enemy::LEFT_TOP, 300.0f, Vector2D(380.0f, 120.0f), this }, 4.2f, false },
		//
	{ { Enemy::BOSS, Enemy::RIGHT_TOP, 300.0f, Vector2D(480.0f, 40.0f), this }, 0.0f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(620.0f, 80.0f), this }, 0.35f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(580.0f, 80.0f), this }, 0.7f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(620.0f, 120.0f), this }, 1.05f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(580.0f, 120.0f), this }, 1.4f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(540.0f, 80.0f), this }, 1.75f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(500.0f, 80.0f), this }, 2.1f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(540.0f, 120.0f), this }, 2.45f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(500.0f, 120.0f), this }, 2.8f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(460.0f, 80.0f), this }, 3.15f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(420.0f, 80.0f), this }, 3.5f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(460.0f, 120.0f), this }, 3.85f, false },
	{ { Enemy::BUG, Enemy::RIGHT_TOP, 300.0f, Vector2D(420.0f, 120.0f), this }, 4.2f, false },
	};

	m_timer = 0.0f;
}

void Formation::Destroy()
{

}

void Formation::Update()
{
	m_timer += Timer::Instance()->DeltaTime();
	for (Info& info : m_information)
	{
		if (info.isActive == false && m_timer > info.enterTime)
		{
			info.isActive = true;
			Enemy* enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);
		}
	}
}

const Path & Formation::GetRandomAttackPath()
{
	size_t index = rand() % m_attackPaths.size();
	return m_attackPaths[index];
}