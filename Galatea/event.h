#pragma once
#include "vector2D.h"

enum EventType{EVENT_NONE, EVENT_PLAYERDESTROYED, EVENT_PLAYERGONE, EVENT_ENEMYDESTROYED};


class GameObject;

struct Event
{
	GameObject* pSource;
	EventType type;
	Vector2D position;
	float data1;
	float data2;
};