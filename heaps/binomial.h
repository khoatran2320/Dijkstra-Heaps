#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <queue>
#include <stack>

#include "../node_utils.h"

using namespace std;

template <typename Object>
class BinomialHeap {
 public:
  BinomialHeap() {
    head = nullptr;
    elements = 0;
  };

  /* set current instance's head as head*/
  void setHead(Object* head) {
    this->head = head;
  }

  // returns the head pointer
  Object* getHead() {
    return head;
  }

  /* Merge two binomial heaps H and H' to H */
  void merge(BinomialHeap h1) {
    Object* curr1 = getHead();
    Object* curr2 = h1.getHead();
    Object* curr3 = nullptr;
    Object* temp = nullptr;

    if (curr1->degree <= curr2->degree) {
      curr3 = curr1;
      curr1 = curr1->sibling;
    } else {
      curr3 = curr2;
      curr2 = curr2->sibling;
    }

    temp = curr3;

    // merge two heaps without taking care of trees with same degree
    // the roots of the tree must be in accending order of degree from
    // left to right
    while (curr1 != nullptr && curr2 != nullptr) {
      if (curr1->degree <= curr2->degree) {
        curr3->sibling = curr1;
        curr1 = curr1->sibling;
      } else {
        curr3->sibling = curr2;
        curr2 = curr2->sibling;
      }

      curr3 = curr3->sibling;
    }

    if (curr1 != nullptr) {
      // copy all the remaining trees of heap1
      while (curr1 != nullptr) {
        curr3->sibling = curr1;
        curr1 = curr1->sibling;
        curr3 = curr3->sibling;
      }
    }

    if (curr2 != nullptr) {
      // copy all the remaining trees of heap2
      while (curr2 != nullptr) {
        curr3->sibling = curr2;
        curr2 = curr2->sibling;
        curr3 = curr3->sibling;
      }
    }

    // scan the merged list and repeatidly merge binomial trees with same degree
    curr3 = temp;
    Object* prev = nullptr;
    Object* next = curr3->sibling;

    while (next != nullptr) {
      // if two adjacent tree roots have different degree or 3 consecutive roots have same degree
      // move to the next tree
      if ((curr3->degree != next->degree) || (next->sibling != nullptr && curr3->degree == next->sibling->degree)) {
        prev = curr3;
        curr3 = next;
      } else {
        // otherwise repeatdly merge binomial trees with same degree
        if (curr3->entry->key <= next->entry->key) {
          curr3->sibling = next->sibling;
          BinomialHeap::linkTrees(curr3, next);
        } else {
          if (prev == nullptr) {
            temp = next;
          } else {
            prev->sibling = next;
          }

          BinomialHeap::linkTrees(next, curr3);
          curr3 = next;
        }
      }

      next = curr3->sibling;
    }

    setHead(temp);
  }

  /* find node with min data */
  Object* findMin() {
    // traverse all the roots and find compare
    int min = 999999;
    Object* currPtr = head;
    Object* minPtr = nullptr;

    while (currPtr != nullptr) {
      if (currPtr->entry->key < min) {
        min = currPtr->entry->key;
        minPtr = currPtr;
      }
      currPtr = currPtr->sibling;
    }

    return minPtr;
  }

  /* Insert a node with key data to the heap*/
  void insert(Object* node) {
    if (elements >= MAX_SIZE) {
      cout << "Heap is full; can't insert " << endl;
      return;
    }
    elements++;
    BinomialHeap h;
    initNode(node, node->entry->key);
    cout << "here" << endl;

    h.setHead(node);
    merge(h);
  };

  Object* remove_min() {
    if (elements == 0) {
      cout << "empty heap error, can't delete" << endl;
    }
    elements--;  // update the amount of elements in heap

    Object* curr = head;
    Object* prevMin = nullptr;
    // find the root with minimum key
    Object* minPtr = nullptr;
    Object* prevPtr = nullptr;
    int min = 999999;

    while (curr != nullptr) {
      if (curr->entry->key <= min) {
        min = curr->entry->key;
        prevMin = prevPtr;
        minPtr = curr;
      }
      prevPtr = curr;
      curr = curr->sibling;
    }

    // delete the node pointed by minPtr
    if (prevMin != nullptr && minPtr->sibling != nullptr) {
      prevMin->sibling = minPtr->sibling;
    } else if (prevMin != nullptr && minPtr->sibling == nullptr) {
      prevMin->sibling = nullptr;
    } else if (prevMin == nullptr and minPtr->sibling != nullptr) {
      head = minPtr->sibling;
    } else if (prevMin == nullptr and minPtr->sibling == nullptr) {
      head = nullptr;
    }

    // remove parent reference from all its child
    Object* childPtr = minPtr->child;
    while (childPtr != nullptr) {
      childPtr->parent = nullptr;
      childPtr = childPtr->sibling;
    }

    // reverse the order
    stack<Object*> s;
    childPtr = minPtr->child;
    while (childPtr != nullptr) {
      s.push(childPtr);
      childPtr = childPtr->sibling;
    }

    curr = s.top();
    Object* temp = curr;
    s.pop();

    while (!s.empty()) {
      curr->sibling = s.top();
      s.pop();
      curr = curr->sibling;
    }

    curr->sibling = nullptr;

    BinomialHeap h;
    h.setHead(temp);

    // merge
    merge(h);

    // return the min root
    return minPtr;

  };  // Remove the smallest element in the heap & restructure heap

  void decreaseKey(int pos, int val) {
    // Decreases Key in pos to val
    return;
  };

  /* print heap */
  void printHeap() {
    Object* currPtr = head;
    while (currPtr != nullptr) {
      cout << "B" << currPtr->degree << endl;
      cout << "There are " << pow(2, currPtr->degree) << " nodes in this tree" << endl;
      cout << "The level order traversal is" << endl;
      queue<Object*> q;
      q.push(currPtr);
      while (!q.empty()) {
        Object* p = q.front();
        q.pop();
        cout << p->entry->key << " ";

        if (p->child != nullptr) {
          Object* tempPtr = p->child;
          while (tempPtr != nullptr) {
            q.push(tempPtr);
            tempPtr = tempPtr->sibling;
          }
        }
      }
      currPtr = currPtr->sibling;
      cout << endl
           << endl;
    }
  }

  bool IsEmpty() const { return (elements <= 0); };
  bool IsFull() const { return (elements >= MAX_SIZE); };
  int count() const { return elements; };

 protected:
  int elements;  //  how many elements are in the heap
 private:
  Object* head;

  void initNode(Object* node, int data) {
    node->entry->key = data;
    node->degree = 0;
    node->parent = nullptr;
    node->child = nullptr;
    node->sibling = nullptr;
  }

  void linkTrees(Object* t1, Object* t2) {
    // t1 must be parent of t2
    t2->parent = t1;
    t2->sibling = t1->child;
    t1->child = t2;

    // increase the degree of t1
    t1->degree += 1;
  }
};
#endif
