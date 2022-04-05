#ifndef NODE_UTILS_H
#define NODE_UTILS_H

struct arc{
  struct arc *next;
  int length;
  int end;
  };

typedef struct node{
   struct arc *first; /* first arc in linked list */
   int id;  // The number of the vertex in this node 
   int key;  /* Distance estimate, named key to reuse heap code*/
   int P;  /* Predecessor node in shortest path */
   int position;  /* Position of node in heap, from 0 to Nm, where 0 is best */
   } nodeitem;

struct rpnode{
    nodeitem *node;
    int rank;
    rpnode *next;
    rpnode *lchild;
    rpnode *rchild;
};
#endif