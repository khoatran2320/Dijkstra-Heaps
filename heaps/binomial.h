#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H
#include "../node_utils.h"
#include <unordered_map>
#include <list>
using namespace std;
#define LIST list<BinomialNode *>

template <typename Object>
class BinomialHeap
{
private:
   LIST _heap;
   unsigned int elements;
   unordered_map<int, BinomialNode *> _pos;

   BinomialNode *_mergeTrees(BinomialNode *n1, BinomialNode *n2){
      if(n1->entry->key > n2->entry->key){
         BinomialNode *tmp = n1;
         n1 = n2;
         n2 = tmp;
      }
      n2->_parent = n1;
      n2->_next = n1->_child;
      n1->_child = n2;
      n1->_deg++;

      return n1;
   }

   void _consolidate(){
      if (_heap.size() <= 1) return;
      LIST newheap;
      LIST::iterator it1, it2, it3;
      it1 = it2 = it3 = _heap.begin();

      if (_heap.size() == 2)
      {
         it2 = it1;
         it2++;
         it3 = _heap.end();
      }
      else
      {
         it2++;
         it3 = it2;
         it3++;
      }
      while (it1 != _heap.end())
      {
         if (it2 == _heap.end()){
            it1++;
         }
         else if ((*it1)->_deg < (*it2)->_deg)
         {
            it1++;
            it2++;
            if (it3 != _heap.end())
            {
               it3++;
            }
         }
         else if (it3 != _heap.end() && (*it1)->_deg == (*it2)->_deg && (*it1)->_deg == (*it3)->_deg)
         {
            it1++;
            it2++;
            it3++;
         }
         else if ((*it1)->_deg == (*it2)->_deg)
         {
            BinomialNode *tmp;
            *it1 = _mergeTrees(*it1, *it2);
            it2 = _heap.erase(it2);
            if (it3 != _heap.end()){
               it3++;
            }
         }
      }
   }

   LIST _mergeHeaps(LIST &h1, LIST &h2){

      LIST _new;
      LIST::iterator it1 = h1.begin();
      LIST::iterator it2 = h2.begin();

      // same merging process as merge algo
      while (it1 != h1.end() && it2 != h2.end())
      {
         if ((*it1)->_deg <= (*it2)->_deg)
         {
               _new.push_back(*it1);
               // next(it1);
               it1++;
         }
         else
         {
               _new.push_back(*it2);
               // next(it2);
               it2++;
         }
      }

      // merge remaining 
      while (it1 != h1.end())
      {
         _new.push_back(*it1);
         it1++;
      }
      while (it2 != h2.end())
      {
         _new.push_back(*it2);
         it2++;
      }
      return _new;
   }

   void _insertTree(BinomialNode *tree){
      // insert tree into heap
      LIST tmp;

      // inserting Binomial Tree into heap
      tmp.push_back(tree);
      _heap = _mergeHeaps(_heap, tmp);
      
      _consolidate();
   }

   BinomialNode * _findNode(BinomialNode *start, Object *entry)
   {
      if(start == nullptr) return nullptr;
      if (start->entry == entry) return start;
      
      // Recur for child
      BinomialNode *res = _findNode(start->_child, entry);
      if (res != nullptr) return res;
      return _findNode(start->_next, entry);
   }
   
public:
   unsigned int numInserts = 0;
   unsigned int numRemoveMins = 0;
   unsigned int numDecreaseKeys = 0;

   BinomialHeap(){
      elements = 0;
   };
   ~BinomialHeap(){
   };

   void insert(Object* item){
      numInserts++;
      BinomialNode *newN = new BinomialNode(item);
      if(elements == 0){
         _heap.push_back(newN);
      }
      else{
         _insertTree(newN);
      }
      elements++;
      _pos.emplace(make_pair(item->id, newN));
   };  	

   Object* remove_min(){
      numRemoveMins++;
      //find min
      LIST::iterator it = _heap.begin();
      BinomialNode *minTree = *it;
      while (it != _heap.end())
      {
         // cout << "extract min\n";

         if ((*it)->entry->key < minTree->entry->key){
            minTree = *it;
         }
         it++;
      }

      LIST newheap;
      it = _heap.begin();
      while (it != _heap.end())
      {
         if (*it != minTree)
         {
            newheap.push_back(*it);
         }
         it++;
      }
      Object *ret = minTree->entry;
      unordered_map<int, BinomialNode*>::iterator z = _pos.find(ret->id);
      _pos.erase(z);

      LIST newH;
      BinomialNode *tmp = minTree->_child;
      BinomialNode *lo;

      // making a binomial heap from Binomial Tree
      while(tmp)
      {
         lo = tmp;
         tmp = tmp->_next;
         lo->_next = NULL;
         newH.push_front(lo);
      }
      _heap = _mergeHeaps(newheap, newH);
      _consolidate();
      elements--;
      return ret;
   }; 

   void decreaseKey(Object *n, int val){
      numDecreaseKeys++;
      if(n->key < val){
         return;
      }
      // LIST::iterator it = _heap.begin();
      // BinomialNode *node = nullptr;
      // while (it != _heap.end() && node == nullptr)
      // {
      //    node = _findNode(*it, n);
      //    it++;
      // }
      BinomialNode *node = _pos.at(n->id);
      
      // return if Node is not present
      if (node == nullptr) return;
      node->entry->key = val;
      BinomialNode *parent = node->_parent;

      //upheap
      while (parent != nullptr && node->entry->key < parent->entry->key)
      {
         _pos.at(node->entry->id) = parent;
         _pos.at(parent->entry->id) = node;
         Object *tmp = node->entry;
         node->entry = parent->entry;
         parent->entry = tmp;
         node = parent;
         parent = parent->_parent;
      }
      _consolidate();

   }; 

     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
   
};
#endif
