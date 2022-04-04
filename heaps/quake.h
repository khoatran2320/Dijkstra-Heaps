#ifndef QUAKE_HEAP_H
#define QUAKE_HEAP_H

using namespace std;

const int MAX_SIZE = 200000; //the maximum amount of elements our heap should have.

template <typename Object>
class QuakeHeap
{
public:
   QuakeHeap(){
      elements = 0;
   };
   void insert(Object* item){
   };  	
   Object* remove_min(){
   }; 
   
   void decreaseKey(int pos, int val){
   }; 
     

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
protected:
   Object* array[MAX_SIZE];
   int elements;       //  how many elements are in the heap
private:
   
};
#endif
