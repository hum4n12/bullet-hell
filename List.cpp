#include "List.h"
#include <stdio.h>
List::List() {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

void List::push(GameObject* value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (this->head == nullptr) this->head = newNode;
    else {
        Node* curr = this->head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = newNode;
    }
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
        //this->size--;
        delete next;
    }

    return value;
}

void List::remove(int pos) {
    Node* curr = this->head, * prev = nullptr;

    if (this->head == nullptr) {
        return;
    }

    if (this->getSize() <= pos) {
        return;
    }

    if (pos == 0) {
        this->head = this->head->next;
        //this->size--;
        delete curr;
        return;
    }

    while (pos-- > 0) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;

    // Delete the node
    //if(curr != nullptr) this->size--;
    delete curr;
}

GameObject* List::get(int pos) {
    Node* curr = this->head;
    GameObject* value = nullptr;

    if (this->getSize() <= pos) {
        printf("zdarzenie\n");
    }
    if (this->head == nullptr) {
        printf("\n %d \n", this->getSize());
    }
    int i = 0;
    if (curr != nullptr) {
        while (curr != nullptr && curr != this->tail && i < pos) {
            if (curr->next == curr) {
                curr = nullptr;
                break;
            }
            curr = curr->next;
            i++;
        }
    }
    if(curr != nullptr ) value = curr->value;

    return value;
}

int List::getSize() {
    Node* curr = this->head;
    int size = 0;
    while (curr != nullptr) {
        size++;
        curr = curr->next;
    }
    return size;
}