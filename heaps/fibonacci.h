#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H
#include "../node_utils.h"
using namespace std;


template <typename Object>
class FibHeap
{
private:
   int elements;       //  how many elements are in the heap
   FibNode *_heap;

   void _clean(FibNode *root){
      //delete all. Call for subtrees of each neighbor
      if(root != nullptr){
         FibNode *curr = root;
         do {
			   FibHeap *tmp = curr;
				curr = curr->next;
				_clean(tmp->child);
				delete tmp;
			} while(curr != root);
      }
   }
   void _unMarkAndUnParentAll(FibNode *n) {
		if(n == nullptr) return;
		FibNode *curr = n;
		do {
			curr->marked = false;
			curr->parent = nullptr;
			curr = curr->next;
		}while(curr != n);
	}

   FibNode * _removeMin(FibNode *root) {
		_unMarkAndUnParentAll(root->child);
		if(root->next == root) {
			root = root->child;
		} else {
			root->next->prev = root->prev;
			root->prev->next = root->next;
			root = _merge(root->next, root->child);
		}
		if(root == nullptr) return root;
		FibNode *trees[256] = {nullptr};
		
		while(true) {
			if(trees[root->deg] != nullptr) {
				FibNode *t = trees[root->deg];
				if(t == root) break;
				trees[root->deg] = nullptr;
				if(root->entry->key < t->entry->key) {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					_addChild(root, t);
				} 
            else {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if(root->next == root) {
						t->next = t->prev = t;
						_addChild(t,root);
						root = t;
					} 
               else {
						root->prev->next = t;
						root->next->prev = t;
						t->next = root->next;
						t->prev = root->prev;
						_addChild(t, root);
						root = t;
					}
				}
				continue;
			} else {
				trees[root->deg] = root;
			}
			root = root->next;
		}
		FibNode *min = root;
		FibNode *start = root;
		do {
			if(root->entry->key < min->entry->key) min = root;
			root = root->next;
		} while(root != start);
		return min;
	}

   FibNode* _cut(FibNode *heap, FibNode* root) {
		if(root->next == root) {
			root->parent->child = nullptr;
		} else {
			root->next->prev = root->prev;
			root->prev->next = root->next;
			root->parent->child = root->next;
		}
		root->next = root;
      root->prev = root;
		root->marked = false;
		return _merge(heap, root);
	}

   void _addChild(FibNode *parent, FibNode *child) {
		child->prev = child;
      child->next = child;
		child->parent = parent;
		parent->deg++;
		parent->child = _merge(parent->child, child);
	}

   FibNode * _merge(FibNode *n1, FibNode *n2){
      if(n1 == nullptr) return n2;
      if(n2 == nullptr) return n1;
      FibNode *n1N = n1->next;
		FibNode *n2P = n2->prev;
		n1->next = n2;
		n2->prev = n1;
		n1N->prev = n2P;
		n2P->next = n1N;

      return n1->entry->key < n2->entry->key ? n1 : n2;
   }
   FibNode* _decreaseKey(FibNode* heap, FibNode* n, int value) {
		if(n->entry->key < value) return heap;
		n->entry->key = value;
		if(n->parent) {
			if(n->entry->key < n->parent->entry->key) {
				heap = _cut(heap,n);
				FibNode *parent = n->parent;
				n->parent = nullptr;
				while(parent != nullptr && parent->marked) {
					heap = _cut(heap, parent);
					n = parent;
					parent = n->parent;
					n->parent = nullptr;
				}
				if(parent != nullptr && parent->parent != nullptr) parent->marked = true;
			}
		} else {
			if(n->entry->key < heap->entry->key) {
				heap = n;
			}
		}
		return heap;
	}
public:
   FibHeap(){
      elements = 0;
      _heap = nullptr;
   };
   ~FibHeap(){
      _clean(_heap);
   };
   FibNode *insert(Object* item){
      FibNode *n = new FibNode(item);
      n->next = n;
      n->prev = n;
      _heap = _merge(_heap, n);
      elements++;
      return n;
   };  	
   Object* remove_min(){
      FibNode *old = _heap;
		_heap = _removeMin(_heap);
		Object *ret = old->entry;
		// delete old;
      elements--;
		return ret;
   }; 
   
   void decreaseKey(FibNode *n, int val){
      _heap = _decreaseKey(_heap, n, val);
   }; 
     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
   
};
#endif
