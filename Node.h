#pragma once
#include "GameObject.h"
struct Node {
	GameObject* value = nullptr;
	Node* next = nullptr;
};