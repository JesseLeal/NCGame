#pragma once

#include "Component.h"

class ENGINE_API IRenderComponent : public Component
{
public:
	IRenderComponent(Entity* owner) : Component(owner) {}

	virtual void Draw() = 0;

	void SetVisible(bool vis = true)
	{
		m_visible = vis;
	}
	bool IsVisible() const
	{
		return m_visible;
	}

	void SetDepth(int depth = 0)
	{
		m_depth = depth;
	}
	int GetDepth()
	{
		return m_depth;
	}

	static bool CompareDepth(IRenderComponent* render1, IRenderComponent* render2)
	{
		return (render1->GetDepth() < render2->GetDepth());
	}

protected:
	int m_depth = 0;
	bool m_visible = true;
};