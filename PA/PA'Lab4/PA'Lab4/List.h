#pragma once

template<typename T>
class Node {
public:
    Node(T data) {
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }
    Node* left;
    Node* right;
    T data;
};
template<typename T>
class List {
private:
    Node<T>* head;
    Node<T>* GetNodeAt(int index) {
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        return current;
    }
public:
    List() {
        this->head = nullptr;
    }
    void Push(T data) {
        if (this->head == nullptr) {
            this->head = new Node<T>(data);
        }
        else {
            Node<T>* current = this->head;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = new Node<T>(data);
        }
    }
    T Pop() {
        if (this->head == nullptr) {
            throw ("");
        }
        Node<T>* current = this->head;
        Node<T>* prev_current = nullptr;
        while (current->right != nullptr) {
            prev_current = current;
            current = current->right;
        }
        if (prev_current == nullptr) {
            this->head = nullptr;
        }
        else {
            prev_current->right = nullptr;
        }
        T data = current->data;
        delete current;
        return data;
    }
    int Length() {
        int i = 0;
        Node<T>* current = this->head;
        while (current != nullptr) {
            current = current->right;
            i++;
        }
        return i;
    }
    T GetAt(int index) {
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        return current->data;
    }
    void SetAt(T data, int index) {
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        current->data = data;
    }
    T Erase(int index) {
        if (this->head == nullptr) {
            throw ("");
        }
        Node<T>* current = this->head;
        Node<T>* prev_current = nullptr;
        for (int i = 0; i < index; i++)
        {
            prev_current = current;
            current = current->right;
        }
        if (prev_current == nullptr) {
            this->head = this->head->right;
        }
        else {
            prev_current->right = current->right;
        }
        T data = current->data;
        delete current;
        return data;
    }
    void Insert(T data, int index) {
        if (index == 0) {
            Node<T>* node = new Node<T>(data);
            node->right = this->head;
            this->head = node;
        }
        else if (index == this->Length() - 1) {
            Node<T>* node = this->GetNodeAt(this->Length() - 1);
            node->right = new Node<T>(data);
        }
        else {
            Node<T>* node = this->GetNodeAt(index - 1);
            Node<T>* new_node = new Node<T>(data);
            new_node->right = node->right;
            node->right = new_node;
        }
    }
    int Find(T data) {
        if (this->head == nullptr) {
            throw ("");
        }
        Node<T>* current = this->head;
        int index = -1, i = 0;
        bool is_found = false;
        if (current->data == data) {
            is_found = true;
            index = 0;
        }
        while (current != nullptr && !is_found) {
            if (current->data == data) {
                is_found = true;
                index = i;
            }
            current = current->right;
            i++;
        }
        return index;
    }
    void Sort() {
        int length = this->Length();
        for (int i = 0; i < length; i++)
        {
            for (int i = 0; i < length - 1; i++)
            {
                Node<T>* node = this->GetNodeAt(i);
                if (node->data > node->right->data) {
                    swap(node->data, node->right->data);
                }
            }
        }
    }
};
