# dijkstra
Implementation of Dijkstra's algorithm for finding the shortest path between two points, using an adjacency list.

/// Purpose and Overview ///

This program is meant to simulate Dijkstra's algorithm, whereby a starting point and an ending point are given, and the shortest possible path between the two is found. This was created for my Algorithm Analysis and Data Structures class in the Spring of 2018. 

/// How to Use ///

Ensure that cities.dat is present in the same directory, as that file is what the program uses to read its data points. If a custom file is desired, follow the format of [point 1] [point 2] [distance between]. Point 1 and 2 being integers, and the distance being a float. 

/// How it Works ///

The program works by reading in sets of data points, 2 at a time, and the distance between them. These values are added to the adjacency list. There are two arrays, prev_verts and distance, whose indices are the different points from the data file. They keep track of the shortest point that led to that point, and the shortest distance to that point, respectively. The list is iterated through, with the points being added back into a queue if their 'best' distance was changed (if the path to that node was found to be obsolete and a better path was found. 

Once the best path is found, the shortest distance is output along with the path it took to get from the starting point to the ending point. 
