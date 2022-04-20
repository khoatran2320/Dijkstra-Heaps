#ifndef SHORTPATH_H_
#define SHORTPATH_H_

#include <queue>
#include "heaps/binary.h"
#include "./heaps/quake.h"
#include "./heaps/fibonacci.h"
#include "./heaps/pairing.h"
#include <string>
#include "node_utils.h"

#define LARGE1 9999999

using namespace std;


void DijkstraBinary(node N[], int Or, int Nm)
{
   BinaryHeap<BinaryNode> *thisHeap = new BinaryHeap<BinaryNode>;
   BinaryNode NN[Nm+1];
   struct arc *edge;
   BinaryNode *node;
   N[Or].key = 0;
    int v, du, dv;
   //push all nodes to priority queue
   for(int i = 1; i <= Nm; i++){
       NN[i] = BinaryNode(&N[i]);
       thisHeap->insert(&NN[i]);
   }

    //loop until priority queue is empty
   while(!thisHeap->IsEmpty()){
       node = thisHeap->remove_min();
       edge = node->entry->first;

       //traverse all neighbors v of u
       while(edge != NULL){
            v = edge->end;
            du = node->entry->key;
            dv = NN[v].entry->key;

            //update distance and predecessor
            if(dv > du + edge->length){
                thisHeap->decreaseKey(NN[v].position, du + edge->length);
                N[v].P = node->entry->id;
                N[v].key = du + edge->length;
            }

            edge = edge->next;
       }
   }

} /* end DijkstraHeap */ 


void DijkstraQuake(node N[], int Or, int Nm)
{
   QuakeHeap<QuakeNode> *thisHeap = new QuakeHeap<QuakeNode>;
   QuakeNode NN[Nm+1];
   struct arc *edge;
   QuakeNode *node;
   N[Or].key = 0;
    int v, du, dv;
   //push all nodes to priority queue
   for(int i = 1; i <= Nm; i++){
       NN[i] = QuakeNode(&N[i]);
       thisHeap->insert(&NN[i]);
   }

    //loop until priority queue is empty
   while(!thisHeap->IsEmpty()){
       node = thisHeap->remove_min();
       edge = node->entry->first;

       //traverse all neighbors v of u
       while(edge != NULL){
            v = edge->end;
            du = node->entry->key;
            dv = NN[v].entry->key;

            //update distance and predecessor
            if(dv > du + edge->length){
                thisHeap->decreaseKey(&NN[v], du + edge->length);
                NN[v].entry->P = node->entry->id;
                NN[v].entry->key = du + edge->length;
            }

            edge = edge->next;
       }
   }

} /* end DijkstraQuake */ 

void DijkstraFib(node N[], int Or, int Nm)
{
   FibHeap<node> *thisHeap = new FibHeap<node>;
   FibNode *NN[Nm+1];
   struct arc *edge;
   node *node;
   N[Or].key = 0;
    int v, du, dv;
   //push all nodes to priority queue
   for(int i = 1; i <= Nm; i++){
       NN[i] = thisHeap->insert(&N[i]);
   }

    //loop until priority queue is empty
   while(!thisHeap->IsEmpty()){
       node = thisHeap->remove_min();
       edge = node->first;

       //traverse all neighbors v of u
       while(edge != NULL){
            v = edge->end;
            du = node->key;
            dv = NN[v]->entry->key;

            //update distance and predecessor
            if(dv > du + edge->length){
                thisHeap->decreaseKey(NN[v], du + edge->length);
                NN[v]->entry->P = node->id;
                NN[v]->entry->key = du + edge->length;
            }

            edge = edge->next;
       }
   }

} /* end DijkstraFib */ 

void DijkstraPairing(node N[], int Or, int Nm)
{
   PairingHeap<node> *thisHeap = new PairingHeap<node>;
   PairingNode *NN[Nm+1];
   struct arc *edge;
   node *node;
   N[Or].key = 0;
    int v, du, dv;
   //push all nodes to priority queue
   for(int i = 1; i <= Nm; i++){
       NN[i] = thisHeap->insert(&N[i]);
   }

    //loop until priority queue is empty
   while(!thisHeap->IsEmpty()){
       node = thisHeap->remove_min();
       edge = node->first;

       //traverse all neighbors v of u
       while(edge != NULL){
            v = edge->end;
            du = node->key;
            dv = NN[v]->entry->key;

            //update distance and predecessor
            if(dv > du + edge->length){
                thisHeap->decreaseKey(NN[v], du + edge->length);
                NN[v]->entry->P = node->id;
                NN[v]->entry->key = du + edge->length;
            }

            edge = edge->next;
       }
   }

} /* end DijkstraPairing */ 
#endif
