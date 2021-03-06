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
	void remove(int pos);
	GameObject* get(int pos);
	void clear();
	int getSize();
};

