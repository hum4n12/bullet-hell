#include "List.h"

List::List() {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

void List::push(GameObject* value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (this->head == nullptr && this->tail == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    }
    else {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->size++;
}

GameObject* List::pop(){
    Node* curr = nullptr;
    Node* next = nullptr;
    GameObject* value = nullptr;

    if (this->head != nullptr && this->tail != nullptr) {
        next = this->head;
        while (next != tail) {
            curr = next;
            next = next->next;
        }
        value = next->value;
        this->tail = curr;
        this->size--;
        delete next;
    }

    return value;
}

GameObject* List::remove(int pos){
    Node* curr = nullptr;
    Node* next = this->head;
    Node* prev = nullptr;
    GameObject* value = nullptr;

    if (this->head != nullptr && this->tail != nullptr) {
        int i = 0;
        while (next != this->tail && i < pos) {
            prev = curr;
            curr = next;
            next = next->next;
            i++;
        }
        prev->next = next;
        value = curr->value;

        this->size--;
        delete curr;
    }

    return value;
}


GameObject* List::get(int pos) {
    Node* curr = nullptr;
    GameObject* value = nullptr;

    int i = 0;
    while (curr != this->tail) {
        curr = curr->next;
        i++;
    }
    value = curr->value;

    return value;
}

int List::getSize() {
    return this->size;
}