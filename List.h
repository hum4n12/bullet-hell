#pragma once
#include "Node.h"
class List{
private:
	Node* head;
	Node* tail;
	int size;
public:
	List();
	void push(GameObject* value);
	GameObject* pop();
	GameObject* remove(int pos);
	GameObject* get(int pos);
	int getSize();
};

