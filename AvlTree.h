//
// Created by user on 02/06/2020.
//

#ifndef SOUNDCLOUD_AVLTREE_H
#define SOUNDCLOUD_AVLTREE_H


#include <stdlib.h>
#include <string>
#include <assert.h>
template<class T, class CompareT>
class AvlTree {
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
    class Node{
    private:
        T* keyT;
        Node* right_son;
        Node* left_son;
        Node* father;
        int nodeHeight;
        int sub_tree_size;
    public:
        friend class AvlTree;
        Node(const T& t, Node * father) {
            try {
                this->keyT = t.clone();
                this->right_son = nullptr;
                this->left_son = nullptr;
                this->father = father;
                this->nodeHeight = 0;
                this->sub_tree_size = 1;
            }
            catch (...) {
                throw OUT_OF_MEM();
            }
        }

        ~Node(){
            if(keyT != nullptr) {
                delete keyT;
            }
            keyT = nullptr;
            if(this->left_son!= nullptr) {
                delete this->left_son;
                this->left_son = nullptr;
            }
            if(this->right_son != nullptr) {
                delete this->right_son;
                this->right_son = nullptr;
            }
            father = nullptr;
        }
        int getBalance(){
            if(this->nodeHeight == 0) return 0;
            if((left_son == nullptr)&&(right_son != nullptr)) return -(right_son->nodeHeight +1);
            if((left_son != nullptr)&&(right_son == nullptr)) return left_son->nodeHeight +1;
            return (left_son->nodeHeight)-(right_son->nodeHeight);
        }
        Node* findNode(const T& t){
            CompareT compare;
            int result = compare(t, *(this->keyT));
            if(result == 0) return this;
            if(result < 0){
                if(this->left_son == nullptr){
                    throw FAILURE();
                }
                return this->left_son->findNode(t);
            }
            else if(result > 0){
                if(this->right_son == nullptr){
                    throw FAILURE();
                }
                return this->right_son->findNode(t);
            }
            return nullptr;
        }
        int max(int a, int b){
            return (a > b) ? a:b;
        }
        void updateHeight(bool specialUpdate){
            if (this->right_son == nullptr && this->left_son == nullptr) {
                this->nodeHeight = 0;
            }
            else if (this->right_son != nullptr && this->left_son == nullptr) {
                this->nodeHeight = 1 + (this->right_son->nodeHeight);
            } else if (this->right_son == nullptr && this->left_son != nullptr) {
                if(specialUpdate == true){
                    this->nodeHeight = this->left_son->nodeHeight;
                }
                else {
                    this->nodeHeight = 1 + (this->left_son->nodeHeight);
                }
            } else {
                if(specialUpdate == true){
                    this->nodeHeight = 1 + max((this->left_son->nodeHeight)-1, this->right_son->nodeHeight);
                }
                else {
                    this->nodeHeight = 1 + max(this->left_son->nodeHeight, this->right_son->nodeHeight);
                }
            }
        }
        void RR_Rotate() {
            Node *temp = this->right_son;
            Node *temp2 = temp->left_son;
            temp->father = this->father;
            if (this->father != nullptr) {
                if (this->father->right_son == this) {
                    this->father->right_son = temp;
                } else {
                    this->father->left_son = temp;
                }
            }
            this->right_son = temp2;
            if(temp2 != nullptr) {
                temp2->father = this;
            }
            temp->left_son = this;
            this->father = temp;
            this->updateHeight(false);
            temp->updateHeight(false);
            if(temp2 != nullptr){
                this->sub_tree_size = this->sub_tree_size - temp->sub_tree_size + temp2->sub_tree_size;
            }
            else{
                this->sub_tree_size = this->sub_tree_size - temp->sub_tree_size;
            }
            if(this->left_son != nullptr){
                temp->sub_tree_size += this->left_son->sub_tree_size +1;
            }
            else{
                temp->sub_tree_size++;
            }
        }
        void LL_Rotate(){
            Node *temp = this->left_son;
            Node *temp2 = temp->right_son;
            temp->father = this->father;
            if (this->father != nullptr) {
                if (this->father->right_son == this) {
                    this->father->right_son = temp;
                } else {
                    this->father->left_son = temp;
                }
            }
            this->left_son = temp2;
            if(temp2 != nullptr) {
                temp2->father = this;
            }
            temp->right_son = this;
            this->father = temp;
            this->updateHeight(false);
            temp->updateHeight(false);
            if(temp2 != nullptr){
                this->sub_tree_size = this->sub_tree_size - temp->sub_tree_size + temp2->sub_tree_size;
            }
            else{
                this->sub_tree_size = this->sub_tree_size - temp->sub_tree_size;
            }
            if(this->right_son != nullptr) {
                temp->sub_tree_size += this->right_son->sub_tree_size + 1;
            }
            else{
                temp->sub_tree_size++;
            }

        }
        void LR_Rotate(){
            this->left_son->RR_Rotate();
            this->LL_Rotate();
        }
        void RL_Rotate() {
            this->right_son->LL_Rotate();
            this->RR_Rotate();
        }
        void balance(){
            this->updateHeight(false);
            int b_factor = this->getBalance();
            if(b_factor > 1){
                if(this->left_son->getBalance() >0){
                    this->LL_Rotate();
                }
                else{
                    this->LR_Rotate();
                }
            }
            else if(b_factor < -1){
                if(this->right_son->getBalance() > 0){
                    this->RL_Rotate();
                }
                else{
                    this->RR_Rotate();
                }
            }
        }

        bool TreeIsExists(const T& t){
            CompareT compare;
            int result = compare(t, *this->keyT);
            if(result == 0) return true;
            if(result < 0 && this->left_son != nullptr){
                return this->left_son->TreeIsExists(t);
            }
            else if(result > 0 && this->right_son != nullptr){
                return this->right_son->TreeIsExists(t);
            }
            return false;
        }
        T* insert(const T& t, Node* father1) {
            T* t1 = nullptr;
            CompareT compare;
            int result = compare(t, *(this->keyT));
            if (result < 0) {
                this->sub_tree_size++;
                if(this->left_son == nullptr){
                    this->left_son = new Node(t, this);
                    this->balance();
                    return this->left_son->keyT;
                }
                t1 = this->left_son->insert(t, this);
            } else if (result > 0) {
                this->sub_tree_size++;
                if(this->right_son == nullptr){
                    this->right_son = new Node(t, this);
                    this->balance();
                    return this->right_son->keyT;
                }
                t1 = this->right_son->insert(t, this);
            }
            else if(result == 0){
                throw FAILURE();
            }
            this->balance();
            return t1;
        }
        Node* remove(const T& t) {
            CompareT compare;
            assert(this->keyT!= nullptr);
            int result = compare(t, *(this->keyT));
            if (result < 0) {
                if(left_son== nullptr) throw FAILURE();
                this->sub_tree_size--;
                this->left_son->remove(t);
                this->balance();
            } else if (result > 0) {
                if(right_son== nullptr) throw FAILURE();
                this->sub_tree_size--;
                this->right_son->remove(t);
                this->balance();
            } else {
                if(father == nullptr && right_son == nullptr && left_son == nullptr){
                    delete this;
                    return nullptr;
                }
                if (this->nodeHeight == 0) {
                    return this->removeLeaf();
                } else if (this->left_son == nullptr && this->right_son != nullptr) {
                    return this->removeFatherWithOnlyRightSon();
                } else if (this->left_son != nullptr && this->right_son == nullptr) {
                    return this->removeFatherWithOnlyLeftSon();
                } else {
                    return this->removeFatherWithTwoSons();
                }
            }
            if (this->father != nullptr) {
                return this->father;
            }
            return this;
        }
        Node* removeLeaf(){
            if(this->father->left_son == this){
                this->father->left_son = nullptr;
            }
            else{
                this->father->right_son = nullptr;
            }
            delete this;
            return nullptr;
        }
        Node* removeFatherWithOnlyRightSon(){
            Node* temp = this->right_son;
            this->right_son->father = this->father;
            if(this->father != nullptr){
                if(this->father->left_son == this){
                    this->father->left_son = this->right_son;
                }
                else{
                    this->father->right_son = this->right_son;
                }
            }
            this->right_son = nullptr;
            this->left_son = nullptr;
            delete this;
            return temp;
        }
        Node* removeFatherWithOnlyLeftSon(){
            Node* temp = this->left_son;
            this->left_son->father = this->father;
            if(this->father != nullptr){
                if(this->father->left_son == this){
                    this->father->left_son = this->left_son;
                }
                else{
                    this->father->right_son = this->left_son;
                }
            }
            this->right_son = nullptr;
            this->left_son = nullptr;
            delete this;
            return temp;
        }
        Node* removeFatherWithTwoSons(){
            int size = this->sub_tree_size - 1;
            Node* temp = this->right_son;
            if(temp->left_son == nullptr){
                temp->father = this->father;
                if(this->father != nullptr){
                    if(this->father->left_son == this){
                        this->father->left_son = temp;
                    }
                    else{
                        this->father->right_son = temp;
                    }
                }
                temp->left_son = this->left_son;
                this->left_son->father = temp;
                this->right_son = temp->right_son;
                if(temp->right_son != nullptr) {
                    temp->right_son->father = this;
                }
                temp->right_son = this;
                this->father = temp;
                this->left_son = nullptr;
                this->sub_tree_size = temp->sub_tree_size;
                temp->sub_tree_size = size;
            }
            else{
                while(temp->left_son != nullptr){
                    temp->sub_tree_size--;
                    temp->updateHeight(true);
                    temp = temp->left_son;
                }
                Node* temp2 = temp->right_son;
                Node* temp3 = temp->father;
                temp->father = this->father;
                if(this->father != nullptr){
                    if(this->father->left_son == this){
                        this->father->left_son = temp;
                    }
                    else{
                        this->father->right_son = temp;
                    }
                }
                temp->left_son = this->left_son;
                temp->right_son = this->right_son;
                this->right_son->father = temp;
                this->left_son->father = temp;
                this->left_son = nullptr;
                this->right_son = temp2;
                this->father = temp3;
                temp3->left_son = this;
                this->sub_tree_size = temp->sub_tree_size;
                temp->sub_tree_size = size;
            }
            if(this->right_son == nullptr){
                this->removeLeaf();
            }
            else{
                this->removeFatherWithOnlyRightSon();
            }
            temp->updateHeight(false);
            return temp;
        }
        int getHeight(){
            return this->nodeHeight;
        }
        int nodeGetDegree(const T& t, int degree){
            CompareT compare;
            int result = compare(t, *this->keyT);
            if(result == 0){
                if(this->left_son != nullptr){
                    return degree + this->left_son->sub_tree_size + 1;
                }
                else return degree + 1;
            }
            else if(result < 0 && this->left_son != nullptr){
                return this->left_son->nodeGetDegree(t, degree);
            }
            else if(result > 0){
                if(this->right_son != nullptr && this->left_son != nullptr) {
                    return this->right_son->nodeGetDegree(t, degree+this->left_son->sub_tree_size+1);
                }
                else{
                    return this->right_son->nodeGetDegree(t, degree + 1);
                }
            }
            else{
                return 0;
            }
        }
        Node* inOrderGetNext() {
            Node *temp = this->right_son;
            Node *temp2 = this->right_son;
            if(temp == nullptr){
                if(this->father == nullptr) return nullptr;
                else if(this->father->left_son == this){
                    return this->father;
                }
                else{
                    temp2 = this->father;
                    while((temp2->father != nullptr) && (temp2->father->right_son == temp2)){
                        temp2 = temp2->father;
                    }
                    return temp2->father;
                }
            }
            while(temp->left_son != nullptr){
                temp = temp->left_son;
            }
            return temp;
        }
        Node* updateRoot(){
            if(this->father != nullptr){
                return this->father;
            }
            return this;
        }
        T* getKey(){
            return this->keyT;
        }
        Node* getMinNode(){
            if(this->left_son == nullptr) return this;
            else{
                Node* n1 = this->left_son;
                while(n1->left_son != nullptr){
                    n1 = n1->left_son;
                }
                return n1;
            }
        }
    };
private:
    Node* root;
    Node* min;
    Node* iterator;

public:
    int size() {
        if (root != nullptr) return root->sub_tree_size;
        return 0;
    }
    AvlTree(){
        root = nullptr;
        min = nullptr;
        iterator = nullptr;
    }

    ~AvlTree(){
        if(root != nullptr) {
            delete root;
        }
    }
    T& getMin(){
        return *(this->min->keyT);
    }
    T* insertElement(const T& t){
        if(root == nullptr) {
            root = new Node(t, nullptr);
            min = root->getMinNode();
            return root->getKey();
        }
        if(root->TreeIsExists(t) == true) throw FAILURE();
        T* t1 = root->insert(t, root);
        root = root->updateRoot();
        min = root->getMinNode();
        if(t1 != nullptr) {
            return t1;
        }
        iterator = nullptr;
        throw FAILURE();
    }
    void removeElement(const T& keyT) {
        if(root==nullptr) throw FAILURE();
        if(root->TreeIsExists(keyT) == false) throw FAILURE();
        root = root->remove(keyT);
        if (root == nullptr) {
            min = nullptr;
            return;
        }
        root = root->updateRoot();
        root->balance();
        root = root->updateRoot();
        if (root != nullptr) {
            min = root->getMinNode();
        } else {
            min = nullptr;
        }
        iterator = nullptr;
    }
    T* startInorder(){
        iterator = min;
        if(iterator == nullptr) return nullptr;
        return min->getKey();
    }
    T* inorderGetNext(){
        iterator = iterator->inOrderGetNext();
        if(iterator == nullptr) return nullptr;
        return iterator->getKey();
    }
    T* inorderGetCurrent(){
        if(iterator != nullptr) return iterator->keyT;
        return nullptr;
    }
    T& findElement(const T& t){
        if(root== nullptr) throw FAILURE();
        return *((root->findNode(t))->keyT);
    }
    int getTreeHeight(){
        return this->root->getHeight();
    }
    int getDegree(const T& t){
        if(root == nullptr) throw FAILURE();
        Node* temp = root->findNode(t);
        if(temp == nullptr) throw FAILURE();
        return root->nodeGetDegree(t, 0);
    }
    bool isEmpty(){
        if(root == nullptr) return true;
        return false;
    }
    void treeClear(){
        delete root->getKey();
        root = nullptr;
    }
    void printTree(){
        for(T* t = startInorder(); t != nullptr; t = inorderGetNext()){
            const T& newt = *t;
            int deg = root->getDegree(newt);
            printf("[Node %d :degree -  %d]", *t, deg);
        }
    }
};


#endif //SOUNDCLOUD_AVLTREE_H
