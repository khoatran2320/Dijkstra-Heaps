#ifndef PAIRING_HEAP_H
#define PAIRING_HEAP_H

#include "../node_utils.h"

#include <vector>
using namespace std;


template <typename Object>
class PairingHeap
{
private:
    unsigned int elements;
    PairingNode *_heap;

    void _add_child(PairingNode *parent, PairingNode *child){
        if(parent->_lchild == nullptr){
            parent->_lchild = child;
        }else{
            child->_next = parent->_lchild;
            parent->_lchild = child;
        }
    }

    void _merge(PairingNode *&n1, PairingNode *n2){
        if (n2 == nullptr)
            return;
        if (n2->entry->key < n1->entry->key)
        {
            n2->_prev = n1->_prev;
            n1->_prev = n2;
            n1->_next = n2->_lchild;
            if (n1->_next != nullptr)
                n1->_next->_prev = n1;
            n2->_lchild = n1;
            n1 = n2;
        }
        else
        {
            n2->_prev = n1;
            n1->_next = n2->_next;
            if (n1->_next != nullptr)
                n1->_next->_prev = n1;
            n2->_next = n1->_lchild;
            if (n2->_next != nullptr)
                n2->_next->_prev = n2;
            n1->_lchild = n2;
        }
    }

    PairingNode *_twoPassMerge(PairingNode *n){
        if (n->_next == nullptr)
            return n;
        static vector<PairingNode *> treeArray(5);
        int numSiblings = 0;
        for (; n != nullptr; numSiblings++)
        {
            if (numSiblings == treeArray.size())
                treeArray.resize(numSiblings * 2);
            treeArray[numSiblings] = n;
            n->_prev->_next = nullptr;
            n = n->_next;
        }
        if (numSiblings == treeArray.size())
            treeArray.resize(numSiblings + 1);
        treeArray[numSiblings] = nullptr;
        int i = 0;
        for (; i + 1 < numSiblings; i += 2)
            _merge(treeArray[i], treeArray[i + 1]);
        int j = i - 2;
        if (j == numSiblings - 3)
            _merge (treeArray[j], treeArray[j + 2]);
        for (; j >= 2; j -= 2)
            _merge(treeArray[j - 2], treeArray[j] );
        return treeArray[0];
    }
    
    void _clean(PairingNode *root){
        if (root != nullptr)
        {
            _clean(root->_lchild);
            _clean(root->_next);
            delete root;
        }
    }
public:
    unsigned int numInserts = 0;
    unsigned int numRemoveMins = 0;
    unsigned int numDecreaseKeys = 0;
    PairingHeap(){
        elements = 0;
        _heap = nullptr;
    };
    ~PairingHeap(){
        _clean(_heap);
        _heap = nullptr;
    };
    PairingNode *insert(Object* item){
        numInserts++;
        PairingNode * newN = new PairingNode(item);
        if (_heap == nullptr)
            _heap = newN;
        else
            _merge(_heap, newN);
        elements++;
        return newN;
    };  	
    Object* remove_min(){
        numRemoveMins++;
        if (IsEmpty())
        {
            cout << "The Heap is Empty" << endl;
            return nullptr;
        }
        Object *ret = _heap->entry;
        if (_heap->_lchild == nullptr)
            _heap = nullptr;
        else
            _heap = _twoPassMerge(_heap->_lchild);
        elements--;
        return ret;
    }; 

    void decreaseKey(PairingNode *node, int val){
        numDecreaseKeys++;
        if (node->entry->key < val) return;
        node->entry->key = val;
        if (node != _heap)
        {
            if (node->_next != nullptr)
                node->_next->_prev = node->_prev;
            if (node->_prev->_lchild == node)
                node->_prev->_lchild = node->_next;
            else
                node->_prev->_next = node->_next;
                node->_next = nullptr;
                _merge(_heap, node);
        }
    }; 
        

    bool IsEmpty() const {  return (elements <= 0);};
    bool IsFull() const {return (elements >=MAX_SIZE );};
    int count() const {return elements;};
};
#endif
