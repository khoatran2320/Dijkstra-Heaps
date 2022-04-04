#ifndef SHORTPATH_H_
#define SHORTPATH_H_

#include <queue>
#include "myHeap.full.h"  // This is my version of HW 2.  You can include your own binary heap
#include <string>

#define LARGE1 9999999

using namespace std;


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

void DijkstraBinary(nodeitem N[], int Or, int Nm)
{
   BinaryHeap<nodeitem> *thisHeap = new BinaryHeap<nodeitem>;
   struct arc *edge;
   nodeitem *node;
   N[Or].key = 0;
    int v, du, dv;
   //push all nodes to priority queue
   for(int i = 1; i <= Nm; i++){
       thisHeap->insert(&N[i]);
   }

    //loop until priority queue is empty
   while(!thisHeap->IsEmpty()){
       node = thisHeap->remove_min();
       edge = node->first;

       //traverse all neighbors v of u
       while(edge != NULL){
            v = edge->end;
            du = node->key;
            dv = N[v].key;

            //update distance and predecessor
            if(dv > du + edge->length){
                thisHeap->decreaseKey(N[v].position, du + edge->length);
                N[v].P = node->id;
                N[v].key = du + edge->length;
            }

            edge = edge->next;
       }
   }

} /* end DijkstraHeap */ 
#endif
