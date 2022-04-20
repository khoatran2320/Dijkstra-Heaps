#ifndef QUAKE_HEAP_H
#define QUAKE_HEAP_H
#include "../node_utils.h"
#include <vector>
using namespace std;


template <typename Object>
class QuakeHeap
{
public:
   QuakeHeap(){
      elements = 0;
      levels.push_back(0);
      trees.push_back(new quakenode);
   };
   void insert(Object* item){
      if(trees[0]->node == nullptr){
         trees[0]->node = item;
      }
      else{
         quakenode *entry = new quakenode;
         entry->node = item;
         if(trees[0]){
            quakenode *first = trees[0];
            trees[0] = entry;
            trees[0]->next = first;
         }else{
            trees[0] = entry;
         }
      }
      levels[0]++;
      elements++;
   };  	
   Object* remove_min(){
      if(elements <= 0){
         cout << "no more nodes to remove\n";
         return nullptr;
      }
      elements--;
      quakenode *min = nullptr;
      for(quakenode *n : trees){
         quakenode *curr = n;

         while(curr != nullptr){
            quakenode *l = l->isLeaf ? curr: curr->leaf;
            if(min == nullptr  || l->node->key < min->node->key){
               min = l;
            }
            curr = curr->next;
         }
      }

      quakenode *cmin = min;
      int clevel = cmin->level;

      while(clevel > 0){
         remove_root(clevel, cmin, false);
         levels[clevel]--;

         clevel--;
         add_root(clevel, cmin->lchild);
         add_root(clevel, cmin->rchild);
         if(cmin->lchild->leaf == cmin){
            cmin = cmin->lchild;
         }
         if(cmin->rchild->leaf == cmin){
            cmin = cmin->rchild;
         }
      }
      
      remove_root(clevel, cmin, true);
      levels[clevel]--;

      consolidate();
      quake();
      return min->node;
   }; 
   
   void decreaseKey(quakenode* n, int newval){
      if(newval >= n->node->key){
         cout << "invalid new value\n";
         return;
      }

      quakenode *t = n->top;
        if (t->parent != nullptr) {
            cut(t);
        }
        n->node->key = newval;
   }; 
     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
protected:
   int elements;       //  how many elements are in the heap
   vector<quakenode *> trees; // trees at level i
   vector<int> levels; //number of nodes at level i
private:
   void remove_root(int level, quakenode* root, bool del){
      quakenode *curr = trees[level]->next;
      quakenode *prev = nullptr;
       
      if (curr != nullptr && curr == root)
      {
         trees[level] = curr->next; // Changed head
         if(del) delete curr;
         return;
      }
      else{
         while (curr != NULL && curr != root)
         {
            prev = curr;
            curr = curr->next;
         }
         if (curr == NULL)
            return;
         
         // Unlink the node from linked list
         prev->next = curr->next;
         if(del) delete curr;
      }
   }

   void add_root(int level, quakenode *root){
      if(trees[level]->node){
         quakenode *first = trees[level];
         trees[level] = root;
         root->next = first;
      }else{
         trees[level] = root;
      }
   }


   void link(quakenode* r1, quakenode* r2){
      int clevel = r1->level;

      // make new root
      quakenode *newRoot;
      if(r1->node->key < r2->node->key){
         newRoot = new quakenode(r1->node);
         newRoot->level = clevel + 1;
         newRoot->lchild = r1;
         newRoot->rchild = r2;
         r1->leaf->top = newRoot;
      }else{
         newRoot = new quakenode(r2->node);
         newRoot->level = clevel + 1;
         newRoot->lchild = r1;
         newRoot->rchild = r2;
         r2->leaf->top = newRoot;
      }

      // update parent
      r1->parent = newRoot;
      r2->parent = newRoot;

      // remove old roots from level
      remove_root(clevel, r1, false);
      remove_root(clevel, r2, false);

      // add new root to higher level
      if(trees.size() == clevel + 1){
         trees.push_back(new quakenode);
      }
      add_root(clevel + 1, newRoot);

      // update level count
      if(levels.size() == clevel + 1){
         levels.push_back(0);
      }
      levels[clevel + 1]++;
   }  

   void cut(quakenode *cNode){
      quakenode *p = cNode->parent;
      if(p != nullptr){
         // cut child
         if(p->lchild == cNode){
            p->lchild = nullptr;
         }
         if(p->rchild == cNode){
            p->rchild = nullptr;
         }

         // cut parent
         cNode->parent = nullptr;

         // add as new level root node
         add_root(cNode->level, cNode);
      }
   }


   void quake(){
      bool quaked = false;
      for(int i = 0; i < levels.size() - 1; i++){
         if(quaked){
            levels[i] = 0;
         }else{
            // alpha = .75
            if(levels[i+1] > 3/4 * levels[i]){
               quaked = true;
            }
         }
      }
   }

   void consolidate(){
      for(int i = 0; i < trees.size(); i++){
         while(true){
            quakenode *head_root = trees[i];
            if(head_root == nullptr) break;
            quakenode *next_root = head_root->next;
            if(next_root == nullptr) break;
            link(head_root, next_root);
         }
      }
   }
};
#endif



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
   void print_forest(){
      for(auto const &i : _forest){
         cout << '|' <<i->_node->entry->key << " height " << i->_height << '|' << '\t';
      }
      cout << endl;
   }
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
   void quake(QuakeHeapNode *root, bool min_update=false){
      Object * node = root->_node;
      while(root != nullptr){
         //traverse down left child if left child is same
         if(root->_lchild != nullptr && root->_lchild->_node == node){
            if(root->_rchild != nullptr){
               root->_rchild->_parent = nullptr;
               _forest.push_back(root->_rchild);
               if(min_update){
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
               if(min_update){
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
      // entry->_root = prev(_forest.end());
      update_min();
      // _forest.back()->_root = prev(_forest.end());
      (*_forest.rbegin())->_root = _forest.end();
      ++((*_forest.rbegin())->_root);
      ++elements;
   };  	
   Object* remove_min(){
      RootsIt oldMin = _min;
      Object *retMin = (*_min)->_node;
      quake(*_min);
      _forest.erase(oldMin);
      
      //find min and group all trees of same height
      vector<list<QuakeHeapNode * > > groups(ceil(log2(elements)) + 2);
      vector<int> heights(ceil(log2(elements)) + 2);;

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
         _forest.erase(topNode->_root);
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
