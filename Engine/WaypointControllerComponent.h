#pragma once
#include "ControllerComponent.h"
#include "Waypoint.h"

class ENGINE_API WaypointControllerComponent : public IControllerComponent
{
public:
	WaypointControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed, const std::vector<Vector2D>& points, float turnRate, bool setPosAtStart = false);
	void Destroy();
	void Update();

	void SetNextWaypoint();

	bool IsComplete()
	{
		return m_isComplete;
	}

protected:
	bool m_isComplete = false;
	float m_speed = 0.0f;
	float m_turnRate = 0.5f;
	/*
	float m_cooldown;
	float m_firerateMin = 0.7f;
	float m_firerateMax = 2.4f;
	*/

	Waypoint* m_waypoint = nullptr;
	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;
};