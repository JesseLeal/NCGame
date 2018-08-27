#include "WaypointControllerComponent.h"
#include "KinematicComponent.h"
#include "Timer.h"
#include  "DebugDraw.h"

void WaypointControllerComponent::Create(float speed, const std::vector<Vector2D>& points)
{
	m_speed = speed;
	m_cooldown = Math::GetRandomRange(m_firerateMin, m_firerateMax);

	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_owner->GetScene()->AddEntity<Waypoint>();
		waypoint->Create(point, Vector2D(10.0f, 10.0f), m_owner);
		m_waypoints.push_back(waypoint);
	}

	m_waypointIndex = 0;
	m_waypoint = m_waypoints[m_waypointIndex];
}

void WaypointControllerComponent::Destroy()
{
	for (Waypoint* waypoint : m_waypoints)
	{
		waypoint->SetState(Entity::DESTROY);
	}
}

void WaypointControllerComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	if (m_owner->Intersects(m_waypoint))
	{
		SetNextWaypoint();
	}

	DEBUG_DRAW_LINE(m_owner->GetTransform().position, m_waypoint->GetTransform().position, Color::red);

	m_cooldown -= Timer::Instance()->DeltaTime();
	Vector2D direction = m_waypoint->GetTransform().position - m_owner->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees + 90.0f);

	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, rotation, dt * 5.0f);

	Vector2D force = Vector2D::Rotate(Vector2D::down, m_owner->GetTransform().rotation * Math::DegreesToRadians);

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	/*if (m_cooldown <= 0.0f)
	{
		m_cooldown = Math::GetRandomRange(m_firerateMin, m_firerateMax);
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create(m_owner->GetTransform().position, Vector2D::up, 800.0f, "enemymissile");
		m_owner->GetScene()->AddEntity(missile);
		AudioSystem::Instance()->PlaySound("laser", false);
	}*/
}

void WaypointControllerComponent::SetNextWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_waypoint = m_waypoints[m_waypointIndex];
	}
	else
	{
		m_isComplete = true;
	}

}