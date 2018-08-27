#pragma once
#include "ID.h"
#include "Variant.h"

class Entity;

struct Event
{
	ID eventID;
	Entity* sender;
	Entity* reciever;
	Variant variant;

	Event() {}
};