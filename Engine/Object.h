#pragma once
#include "Engine.h"
#include "ID.h"

class ENGINE_API Object
{
public:
	Object(const ID& id = ID()) : m_id(id) {}
	virtual ~Object() {}

	bool operator == (const Object& obj) const
	{
		return m_id == obj.m_id;
	}

	bool operator != (const Object& obj) const
	{
		return m_id != obj.m_id;
	}

	bool operator == (const ID& id) const
	{
		return m_id == id;
	}

	bool operator != (const ID& id) const
	{
		return m_id != id;
	}

protected:
	ID m_id;
};