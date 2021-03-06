#ifndef NODE_UTILS_H
#define NODE_UTILS_H
// #include <list>
// #include <iterator>
// #include <iostream>

const int MAX_SIZE = 200000; //the maximum amount of elements our heap should have.

struct arc{
  struct arc *next;
  int length;
  int end;
  };

struct node{
  struct arc *first;
  int P;
  int key;
  int id;
};

struct BinomialNode{
  node *entry;
  BinomialNode *_child;
  BinomialNode *_next;
  BinomialNode *_parent;
  unsigned int _deg;

  BinomialNode(node *e){
    entry = e;
    _child = nullptr;
    _next = nullptr;
    _parent = nullptr;
    _deg = 0;
  };
};

struct PairingNode{
  node *entry;
  PairingNode *_lchild;
  PairingNode *_next;
  PairingNode *_prev;
  PairingNode(node *e){
    _lchild = nullptr;
    _next = nullptr;
    _prev = nullptr;
    entry = e;
  }
};

struct FibNode{
  node *entry;
  FibNode *next;
  FibNode *prev;
  FibNode *child;
  FibNode *parent;
  unsigned int deg;
  bool marked;

  FibNode(node *e){
    entry = e;
    prev = nullptr;
    next = nullptr;
    child = nullptr;
    parent = nullptr;
    deg = 0;
    marked = false;
  };
};

struct BinaryNode{
  node *entry;
  int position;
  BinaryNode(node *e){
    entry = e;
    position = -1;
  }
  BinaryNode(){
    position = -1;
  }
};
// struct QuakeHeapNode;
// struct QuakeNode{
//       node *entry;
//       QuakeHeapNode *_top;
//       QuakeNode(node *e){
//         entry = e;
//         _top = nullptr;
//       }
//       QuakeNode(){
//         _top = nullptr;
//       }
//    };    
// struct QuakeHeapNode{
//       QuakeNode *_node;
//       unsigned int _height;
//       QuakeHeapNode *_parent;
//       QuakeHeapNode *_lchild;
//       QuakeHeapNode *_rchild;
//       std::list<QuakeHeapNode*>::iterator _root;
//       QuakeHeapNode(QuakeNode * item){
//          _node = item;
//          _height = 0;
//          _parent = nullptr;
//          _lchild = nullptr;
//          _rchild = nullptr;
//       };
//       QuakeHeapNode(QuakeHeapNode* left, QuakeHeapNode* right){
//          _lchild = left;
//          _rchild = right;
//          _parent = nullptr;
//          if(left != nullptr && right != nullptr){
//             _node = left->_node->entry->key < right->_node->entry->key ? left->_node : right->_node;
//          }
//          else if(left != nullptr){
//             _node = left->_node;
//          }
//          else if(right != nullptr){
//             _node = right->_node;
//          }
//          else{
//             std::cout << "invalid constructor call" << std::endl;
//          }
//          _height = std::max(left->_height, right->_height) + 1;
//       };
//    };    

// struct rpnode{
//   node *entry;
//   int rank;
//   rpnode *next;
//   rpnode *lchild;
//   rpnode *rchild;
// };

#endif