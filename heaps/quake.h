#ifndef QUAKE_HEAP_H
#define QUAKE_HEAP_H
#include "../node_utils.h"
#include <list>
#include <iterator>
#include <vector>
#include <cmath>

using namespace std;



template <typename Object>
class QuakeHeap
{
private:
   using RootsIt = typename list<QuakeHeapNode *>::iterator;
   void update_min(){
      if(_min == _forest.end()){
         --_min;
      }
      else if(_forest.back()->_node->entry->key < (*_min)->_node->entry->key){
         _min = _forest.end();
         --_min;
      }
   };
   void quake(QuakeHeapNode *root, bool is_min_updated=false){
      Object * node = root->_node;
      while(root != nullptr){
         //traverse down left child if left child is same
         if(root->_lchild != nullptr && root->_lchild->_node == node){
            if(root->_rchild != nullptr){
               root->_rchild->_parent = nullptr;
               _forest.push_back(root->_rchild);
               if(is_min_updated){
                  update_min();
               }
            }
            root = root->_lchild;
         }
         //traverse down right child if right child is same
         else if(root->_rchild != nullptr && root->_rchild->_node == node){
            if(root->_lchild != nullptr){
               root->_lchild->_parent = nullptr;
               _forest.push_back(root->_lchild);
               if(is_min_updated){
                  update_min();
               }
            }
            root = root->_rchild;
         }
         else{
            break;
         }
      }
   }
   RootsIt _min;
   list<QuakeHeapNode *>  _forest;
   unsigned int elements;
   float _alpha;
public:
   QuakeHeap(float alpha=0.5){
      _alpha = alpha;
      elements = 0;
      _min = _forest.end();
   };
   ~QuakeHeap(){
      while(!_forest.empty()) delete _forest.back(), _forest.pop_back();
   }
   void insert(Object* item){
      QuakeHeapNode *entry = new QuakeHeapNode(item);
      item->_top = entry;
      _forest.push_back(entry);
      update_min();
      (*_forest.rbegin())->_container = _forest.end();
      --((*_forest.rbegin())->_container);
      ++elements;
   };  	
   Object* remove_min(){
      RootsIt oldMin = _min;
      Object *retMin = (*_min)->_node;
      quake(*_min);
      _forest.erase(oldMin);
      
      //find min and group all trees of same height
      vector<list<QuakeHeapNode * > > groups(ceil(log2(elements)) + 1);
      vector<int> heights(ceil(log2(elements)) + 1);;

      while(_forest.size() > 0){
         QuakeHeapNode *n = _forest.front();
         _forest.pop_front();
         groups[n->_height].push_back(n);
      }

      //link
      for(int i = 0; i < groups.size(); i++){
         list<QuakeHeapNode *> * n_list = &groups[i];
         if(n_list->size() > 1){
            heights[i] = 1;
         }
         while(n_list->size() > 1){
            //link 2 nodes
            QuakeHeapNode *n1 = n_list->back();
            n_list->pop_back();
            QuakeHeapNode *n2 = n_list->back();
            n_list->pop_back();
            QuakeHeapNode * newN = new QuakeHeapNode(n1, n2);
            n1->_parent = newN;
            n2->_parent = newN;
            groups[i+1].push_back(newN);
         }
      }

      //handle quake heights
      int min_i = -1;
      for(int i = 1; i < heights.size() && min_i != -1; i++){
         if(heights[i] > heights[i-1]*_alpha){
            min_i = i;
         }
      }
      
      //handle min
      _min = _forest.end();
      
      //remove all nodes at height i and add child to roots
      for(int i = 0; i < groups.size(); i++){
         if(groups[i].size() > 0){
            if(min_i != -1 && i > min_i){
               quake(groups[i].front(), true);
            }
            else{
               _forest.push_back(groups[i].front());
               update_min();
            }
         }
      }
      --elements;
      return retMin;
   }; 
   
   void decreaseKey(Object *node, int newval){
      if(node->entry->key < newval){
         cout << "invalid new key value" << endl;
      }
      node->entry->key = newval;
      QuakeHeapNode *topNode = node->_top;
      if(topNode->_parent == nullptr){
         _forest.erase(topNode->_container);
      }
      else if(topNode->_parent->_lchild == topNode){
         topNode->_parent->_lchild = nullptr;
      }
      else if(topNode->_parent->_rchild == topNode){
         topNode->_parent->_rchild = nullptr;
      }
      _forest.push_back(topNode);
      update_min();
   }; 
     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
private:
  
};
#endif
