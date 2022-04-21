// Copyright 2018 Michael Graziano mjgrazia@bu.edu
// Copyright 2018 Richard Brower brower@bu.edu

/************

Make First[0:Vsize]   Lables Vertice(nodes) from  0,.., Vsize-1;
Make Edge[[0:Esize]   Lables Edge[Esize]  from  0,..., Esize -1

The last fake vertex  Frist[Vsize] = Esize  point to the 
null facke edge with "null" value Edge[Esize] = -1.

The routine uses connection matrix 
A[Vsize][Vsize] 

with A[i][j] = 1 or edge 0 or no edge.

See https://en.wikipedia.org/wiki/Erdős–Rényi_model

 ************/

#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cstring>


using namespace std;


int main(int argc, char *argv[])
{
    int Vsize = 0;
    //int start[500000], end[500000],dist[500000];
    int start, end, dist;
    Vsize =  atoi(argv[1]);
    int degree = atoi(argv[2]);
    int Esize = Vsize*degree;
    char filename[20];
    sprintf(filename, "Graph_%d_%d.txt", Vsize, Esize); 
    ofstream outfile(filename);
    outfile << Vsize << "  " << Esize << endl;
    
    for(int i =0; i< Vsize; i++) {
        for (int  j = 0; j < degree; j++){
            start = i+1;
            end = rand()%Vsize + 1;
            dist = rand()%100 +1;
            outfile << start << "  " << end << "  "<< dist << endl;
        }
    }
    outfile.close();

 
  return 0;
}