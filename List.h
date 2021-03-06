//
// Created by user on 03/06/2020.
//

#ifndef SOUNDCLOUD_LIST_H
#define SOUNDCLOUD_LIST_H

#include <stdlib.h>
#include <string>
#include <assert.h>



template <class T>
class List{
    class OUT_OF_MEM : public std::exception{
        const char* what() const throw(){
            return "Out Of Memory";
        }
    };
    class FAILURE : public std::exception{
        const char* what() const throw(){
            return "Failure";
        }
    };
    class ListNode{
        int key;
        T data;
        ListNode* prev;
        ListNode* next;

    public:
        friend class iterator;
        friend class List;
        ListNode(int keyT, T d){
            this->key = keyT;
            this->data = d;
            this->prev = nullptr;
            this->next = nullptr;
        }
        ~ListNode(){
            if(this->prev != nullptr) {
                this->prev->next = this->next;
            }
            if(this->next != nullptr) {
                this->next->prev = this->prev;
            }
            this->data = nullptr;
        }
    };

private:
ListNode* head;
ListNode* iterator;
public:
    List(){
        this->head = nullptr;
        this->iterator = nullptr;
    }
    ~List(){
        if(head == nullptr){
            return;
        }
        ListNode* temp1 = head;
        ListNode* temp2 = nullptr;
        while(temp1 != nullptr){
            temp2 = temp1;
            temp1 = temp1->next;
            delete temp2;
        }
    }
    void listInsert(int key_to_insert,T& data){
        if(listIsExists(key_to_insert) != nullptr){
            throw FAILURE();
        }
        try {
            if (this->head == nullptr) {
                this->head = new ListNode(key_to_insert, data);
            } else {
                this->head->prev = new ListNode(key_to_insert, data);
                this->head->prev->next = this->head;
                this->head = this->head->prev;
            }
        }
        catch (...){
            throw OUT_OF_MEM();
        }
    }
    T listRemove(int key_to_remove){
        if(this->head == nullptr){
            throw FAILURE();
        }
        ListNode* temp = head;
        while(temp != nullptr){
            if(temp->key == key_to_remove){
                if(head==temp){
                    head = temp->next;
                }
                T data = temp ->data;
                delete temp;
                return data;
            }
            temp = temp->next;
        }
        throw FAILURE();
    }

    T* listGetStart(){
        this->iterator = this->head;
        return &(this->head->data);
    }

    int listGetKey(){
        if(this->iterator != nullptr) return this->iterator->key;
        return -1;
    }

    T* listGetNext(){
        if(this->iterator != nullptr){
            this->iterator = this->iterator->next;
            if(iterator == nullptr) return nullptr;
            return &(this->iterator->data);
        }
        return nullptr;
    }

    T* listGetCurrent(){
        if(this->iterator != nullptr){
            return &(this->iterator->data);
        }
        return nullptr;
    }
    bool listIsEmpty(){
        if(this->head == nullptr) return true;
        return false;
    }
    T* listIsExists(int k){
        if(this->head == nullptr) return nullptr;
        ListNode* temp = head;
        while(temp != nullptr){
            if(temp->key == k) return &(temp->data);
            temp = temp->next;
        }
        return nullptr;
    }
    T& operator[](int k){
        T* temp = listIsExists(k);
        if(temp == nullptr) throw FAILURE();
        return *temp;
    }
    void delAll(){
        ListNode* it = head;
        while(it!= nullptr){
            delete it->data;
            it = it->next;
        }
    }
};



#endif //SOUNDCLOUD_LIST_H
