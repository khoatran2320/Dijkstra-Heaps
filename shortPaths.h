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

void BellmanFord(nodeitem N[], int Or, int Nm)
{
    queue<int> work_q;
    int enq[Nm+1]; //flags to check if node in queue
    memset(enq, 0, sizeof(enq)); // initialize to false
    N[Or].key = 0;
    enq[Or] = 1;
    work_q.push(Or);
    int u, v, du, dv;
    struct arc *edge;
    // loop until no more node in queue
    while(!work_q.empty()){
        //pop u from queue
        u = work_q.front();
        work_q.pop();
        enq[u] = 0;
        edge = N[u].first;
        
        //loop neighbors of u
        while(edge != NULL){
            v = edge->end;
            du = N[u].key;
            dv = N[v].key;

            //update distance and predessor if distance to v is less than previous distance
            if(dv > du + edge->length){
                N[v].key = du + edge->length;
                N[v].P = u;
                if(enq[v] == 0){
                    enq[v] = 1;
                    work_q.push(v);
                }
            }
            edge = edge->next;
        }
    }
    return;

}/* end Bellman-Ford */
/* ---------------*/


void Dijkstra(nodeitem N[], int Or, int Nm)
{
    int Mark[Nm+1];
    struct arc *edge;
    int v, dv, min_d, min_v, finished;
    for (int i=1; i<=Nm; i++){
        Mark[i]=-1;
    }
    N[Or].key = 0;
    Mark[Or] = 1;
    finished = 1;
    min_v = Or;
    min_d = 0;
    while (finished < Nm){
        edge = N[min_v].first;  //update distances
        while (edge != NULL){ // explore the outgoing arcs of u 
            v = edge->end;
            dv = min_d + edge->length;
            if (N[v].key > dv){
                N[v].key = dv;
                N[v].P = min_v;
            }//if D > dv 
            edge = edge->next;
        }// while edge           
        
        min_d = LARGE1;
        for (int j = 0; j <= Nm; j++){
            if (Mark[j] < 1){
                if (N[j].key < min_d){
                    min_d = N[j].key;
                    min_v = j;
                }
            }
        } 
        Mark[min_v]=1;
        finished++;
    } 
} /* end Dijkstra */


void DijkstraHeap(nodeitem N[], int Or, int Nm)
{
   Heap<nodeitem> *thisHeap = new Heap<nodeitem>;
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
