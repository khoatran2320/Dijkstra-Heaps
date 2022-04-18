#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

using namespace std;


template <typename Object>
class BinomialHeap
{
public:
   BinomialHeap(){
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
