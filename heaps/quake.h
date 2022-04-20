
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
   void cons(){
      for (int i = 0; i < _roots.size(); i++) {
         list<QuakeHeapNode *> roots = _roots[i];
         while (roots.size() > 1) {
               QuakeHeapNode *n1 = roots.front();
               roots.pop_front();
               QuakeHeapNode *n2 = roots.front();
               roots.pop_front();
               link(n1, n2);
         }
      }
   }
   void quake(){
      bool doQuake = false;
      for (int i = 0; i < _heights.size() - 1; i++) {
         if (doQuake) {
               _heights[i] = 0;
         } else {
               if (_heights[i + 1] > _alpha * _heights[i]) {
                  doQuake = true;
               }
         }
      }
   }
   void cut(QuakeHeapNode *root){
      QuakeHeapNode *p = root->_parent;
      if(p != nullptr){
         if(p->_lchild == root){
            p->_lchild = nullptr;
         }
         else if(p->_rchild == root){
            p->_rchild = nullptr;
         }
         root->_parent = nullptr;
         // _roots[root->_height].push_back(root);
      }
   }

   Object * findMin(){
      Object *min = nullptr;
      for (auto &roots : _roots) {
         for (auto &root : roots) {
            if(root == nullptr) continue;
            Object *treeMinimum = root->_node;
            if (min == nullptr || treeMinimum->entry->key < min->entry->key) {
               min = treeMinimum;
            }
         }
      }

      return min;
   }

   void deleteMin(Object * minLeaf){
      cout<< "Level 0 roots: " << _roots[0].size() << " ---" << elements << "--- " <<endl; 
      QuakeHeapNode* currentNode = minLeaf->_top;
      int currentLevel = currentNode->_height;

      while (currentLevel > 0) {
         _roots[currentLevel].remove(currentNode);
         _heights[currentLevel]--;

         currentLevel--;
         _roots[currentLevel].push_back(currentNode->_lchild);
         if(currentNode->_lchild && currentNode->_lchild->_node == minLeaf){
            currentNode = currentNode->_lchild;
         } 
         _roots[currentLevel].push_back(currentNode->_rchild);   
         if(currentNode->_rchild && currentNode->_rchild->_node == minLeaf){
            currentNode = currentNode->_rchild;
         } 
      }
      
      _roots[currentLevel].remove(currentNode);
      _heights[currentLevel]--;
  }


   void link(QuakeHeapNode *n1, QuakeHeapNode *n2){
      if(n1 == nullptr || n2 == nullptr) return;
      int height = n1->_height;
      QuakeHeapNode *newN = new QuakeHeapNode(n1, n2);
      if(newN->_node == n1->_node){
         n1->_node->_top = newN;
      }
      else if(newN->_node == n2->_node){
         n2->_node->_top = newN;
      }
      n1->_parent = newN;
      n2->_parent = newN;

      // _roots[height].remove(n1);
      // _roots[height].remove(n2);
      if (_roots.size() == height + 1) {
            list<QuakeHeapNode *> tmp;
            _roots.push_back(tmp);
        }
        _roots[height + 1].push_back(newN);
   }

   vector<list<QuakeHeapNode *> > _roots;
   vector<int> _heights;
   unsigned int elements;
   float _alpha;
public:
   QuakeHeap(float alpha=0.5){
      _alpha = alpha;
      list<QuakeHeapNode *> tmp;
      _roots.push_back(tmp);
      elements = 0;
      _heights.push_back(0);

   };
   ~QuakeHeap(){
      // while(!_forest.empty()) delete _forest.back(), _forest.pop_back();
   }
   void insert(Object* item){
      QuakeHeapNode *entry = new QuakeHeapNode(item);
      item->_top = entry;
      _roots[0].push_back(entry);
      _heights[0]++;
      ++elements;
      cout << "Inserted key " << item->entry->key << endl;
   };  	
   Object* remove_min(){
      Object *minimumLeaf = findMin();
      deleteMin(minimumLeaf);
      cons();
      quake();
      --elements;
      cout << "Removed key " << minimumLeaf->entry->key << endl;
      return minimumLeaf;
   }; 
   
   void decreaseKey(Object *node, int newval){
      if (newval >= node->entry->key) {
         cout << "Invalid new key\n";
      }

      QuakeHeapNode *top = node->_top;
      if (top->_parent != nullptr) {
         cut(top);
      }
      cout<< "Decreased key from " << node->entry->key << " to " << newval << endl;
      node->entry->key = newval;
   }; 
     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
private:
  
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
   using RootsIt = typename list<QuakeHeapNode *>::iterator;
   void cons(){
      for (int i = 0; i < _roots.size(); i++) {
         list<QuakeHeapNode *> roots = _roots[i];
         while (roots.size() > 1) {
               QuakeHeapNode *n1 = roots.front();
               roots.pop_front();
               QuakeHeapNode *n2 = roots.front();
               roots.pop_front();
               link(n1, n2);
         }
      }
   }
   void quake(){
      bool doQuake = false;
      for (int i = 0; i < _heights.size() - 1; i++) {
         if (doQuake) {
               _heights[i] = 0;
         } else {
               if (_heights[i + 1] > _alpha * _heights[i]) {
                  doQuake = true;
               }
         }
      }
   }
   void cut(QuakeHeapNode *root){
      QuakeHeapNode *p = root->_parent;
      if(p != nullptr){
         if(p->_lchild == root){
            p->_lchild = nullptr;
         }
         else if(p->_rchild == root){
            p->_rchild = nullptr;
         }
         root->_parent = nullptr;
         // _roots[root->_height].push_back(root);
      }
   }

   Object * findMin(){
      Object *min = nullptr;
      for (auto &roots : _roots) {
         for (auto &root : roots) {
            if(root == nullptr) continue;
            Object *treeMinimum = root->_node;
            if (min == nullptr || treeMinimum->entry->key < min->entry->key) {
               min = treeMinimum;
            }
         }
      }

      return min;
   }

   void deleteMin(Object * minLeaf){
      cout<< "Level 0 roots: " << _roots[0].size() << " ---" << elements << "--- " <<endl; 
      QuakeHeapNode* currentNode = minLeaf->_top;
      int currentLevel = currentNode->_height;

      while (currentLevel > 0) {
         _roots[currentLevel].remove(currentNode);
         _heights[currentLevel]--;

         currentLevel--;
         _roots[currentLevel].push_back(currentNode->_lchild);
         if(currentNode->_lchild && currentNode->_lchild->_node == minLeaf){
            currentNode = currentNode->_lchild;
         } 
         _roots[currentLevel].push_back(currentNode->_rchild);   
         if(currentNode->_rchild && currentNode->_rchild->_node == minLeaf){
            currentNode = currentNode->_rchild;
         } 
      }
      
      _roots[currentLevel].remove(currentNode);
      _heights[currentLevel]--;
  }


   void link(QuakeHeapNode *n1, QuakeHeapNode *n2){
      if(n1 == nullptr || n2 == nullptr) return;
      int height = n1->_height;
      QuakeHeapNode *newN = new QuakeHeapNode(n1, n2);
      if(newN->_node == n1->_node){
         n1->_node->_top = newN;
      }
      else if(newN->_node == n2->_node){
         n2->_node->_top = newN;
      }
      n1->_parent = newN;
      n2->_parent = newN;

      // _roots[height].remove(n1);
      // _roots[height].remove(n2);
      if (_roots.size() == height + 1) {
            list<QuakeHeapNode *> tmp;
            _roots.push_back(tmp);
        }
        _roots[height + 1].push_back(newN);
   }

   vector<list<QuakeHeapNode *> > _roots;
   vector<int> _heights;
   unsigned int elements;
   float _alpha;
public:
   QuakeHeap(float alpha=0.5){
      _alpha = alpha;
      list<QuakeHeapNode *> tmp;
      _roots.push_back(tmp);
      elements = 0;
      _heights.push_back(0);

   };
   ~QuakeHeap(){
      // while(!_forest.empty()) delete _forest.back(), _forest.pop_back();
   }
   void insert(Object* item){
      QuakeHeapNode *entry = new QuakeHeapNode(item);
      item->_top = entry;
      _roots[0].push_back(entry);
      _heights[0]++;
      ++elements;
      cout << "Inserted key " << item->entry->key << endl;
   };  	
   Object* remove_min(){
      Object *minimumLeaf = findMin();
      deleteMin(minimumLeaf);
      cons();
      quake();
      --elements;
      cout << "Removed key " << minimumLeaf->entry->key << endl;
      return minimumLeaf;
   }; 
   
   void decreaseKey(Object *node, int newval){
      if (newval >= node->entry->key) {
         cout << "Invalid new key\n";
      }

      QuakeHeapNode *top = node->_top;
      if (top->_parent != nullptr) {
         cut(top);
      }
      cout<< "Decreased key from " << node->entry->key << " to " << newval << endl;
      node->entry->key = newval;
   }; 
     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
private:
  
};
#endif