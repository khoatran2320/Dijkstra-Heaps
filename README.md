# EC504 Final Project

Khoa Tran and Yan Chen

## Purpose

The purpose of this project is to analyze the computation time of Dijkstra's single source shortest path problem using different types of priority heaps. The heaps implemented are binary, binomial, fibonacci, rank-pairing, and quake. 

| Heap          | find-min      | delete-min  | insert | decrease-key | merge |
| ------------- | ------------- | ----------- | ------ | ------------ | ----- | 
| Binary        | O(1)          | O(logn)     | O(logn)| O(logn)      | O(n)  |
| Binomial      | O(1)          | O(logn)     | O(1)   | O(logn)      | O(1)  |
| Fibonacci     | O(1)          | O(logn)     | O(1)   | O(1)         | O(1)  |
| Rank-Pairing  | O(1)          | O(logn)     | O(1)   | O(1)         | O(1)  |
| Quake         | O(1)          | O(logn)     | O(1)   | O(1)         | O(1)  |