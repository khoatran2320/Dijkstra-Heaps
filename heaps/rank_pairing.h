#ifndef RANK_PAIRING_HEAP_H
#define RANK_PAIRING_HEAP_H

#include "node_utils.h"
#include <algorithm>
using namespace std;

const int MAX_SIZE = 200000; //the maximum amount of elements our heap should have.

template <typename Object>
class RPHeap
{
public:
    RPHeap(){
        elements = 0;
        min = NULL;
    };
    ~RPHeap(){
        clear();
    };
    void insert(Object* item){
        rpnode * newNode = new rpnode;
        newNode->node = item; 
        if(min = NULL){
            min = newNode;
        }
        else{
            link_to_root(newNode);
            if(elements == 1){
                newNode->next = min;
            }
        }
        elements++;
    };  	
    Object* remove_min(){

    }; 

    void decreaseKey(int pos, int val){
    }; 
        

    bool IsEmpty() const {  return (elements <= 0);};
    bool IsFull() const {return (elements >=MAX_SIZE );};
    int count() const {return elements;};
protected:
    Object* array[MAX_SIZE];
    int elements;       //  how many elements are in the heap
    rpnode *min;
private:
    Object * merge(rpnode *n1, rpnode *n2){
        if(n1 == NULL) return n2;
        if(n2 == NULL) return n1;
        if(n1->node->key > n2->node-key){
            n2->rank++;
            n1->rchild = n2->lchild;
            n2->lchild = n1;
            return n2;
        }else{
            n1->rank++;
            n2->rchild = n1->lchild;
            n1->lchild = n2;
            return n1;
        }
        return NULL;
    }

    void cut(rpnode *item){
        rpnode *curr = item;
        rpnode *next = item->rchild;
        while(next != NULL){
            curr->rchild = NULL;
            link_to_root(next);
            curr = next;
            next = next->rchild;
        }
    }
    void compress(){
        bool complete = false;
        while(!complete){
            complete = true;
            Object * curr =  min;

        }
    }
    void link_to_root(rpnode *item){
        if(item == NULL) return;
        rpnode * next = min->next;
        min->next = item;
        item->next = next;
    }

    void freeNodes(rpnode *node){
        if(node == NULL) return;
        freeNodes(node->lchild);
        freeNodes(node->rchild);
        delete node;
    }
    void clear(){
        rpnode *curr = min->next;
        while(curr != min){
            rpnode *toDel = curr;
            curr = curr->next;
            freeNodes(toDel);
        }
        freeNodes(min);
    }

    int rank(rpnode *node){
        
    }
    void calc_ranks(){
        rpnode *curr = min->next;
        while(curr != min){
            
        }
    }
};
#endif
