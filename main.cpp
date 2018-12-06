//Name: main.cpp
//Author: George Perez
//Description: This program is designed to find the shortest path between two
//             points, given a formatted file. Using the function dijkstra,
//             it will calculate the total distance of the shortest path
//             between the starting and ending and print the result along with the path.
//             The function dijkstra uses adjacency list implementation of path connections.

#include "adjacencylist.h"
#include <iostream>
#include <fstream>
#include <cmath> // Absolute value
#include <queue> // For dijkstra
#include <stack> // For dijkstra

using namespace std;

// Finding the shortest path in an adjacency list given the starting point
void dijkstra(AdjacencyList input_list, int starting, int target);

int main()
{
  AdjacencyList adj_list;

  ifstream file;
  file.open("cities.dat");

  if(!file.is_open())
  {
    cout << " File not found. Exiting..." << endl;
    exit(1);
  }

  int starting_city; // Starting point
  int ending_city; // Destination
  int temp_city; // For use in file read
  pair<int, double> temp_edge; // For use in file read

  file >> starting_city; // Reading in the first 2 lines
  file >> ending_city;

  while(!file.eof())
  {
    file >> temp_city; // The starting
    file >> temp_edge.first; // The destination
    file >> temp_edge.second; // The weight between the two

    temp_edge.second = abs(temp_edge.second); // Cannot have negative weights

    if(file.eof()) break; // To avoid duplicate entries
    adj_list.add_edge(temp_city, temp_edge);
  }

  dijkstra(adj_list, starting_city, ending_city);

  file.close();
}

void (AdjacencyList input_list, int starting, int target)
{
  queue<int> verts; // To hold the vertices for which to check

  //ID_RANGE is defined in adjacencylist.h
  int prev_verts[ID_RANGE]; // The previous points
  double distance[ID_RANGE]; // Distances from the starting point

  for(int i = 0; i < ID_RANGE; i++) // Initializing all distances to large values
  {
    distance[i] = INT_MAX; // 'Infinity'
  }

  distance[starting] = 0; // Source to source is 0
  verts.push(starting); // Push it onto the stack

  int queue_item = starting;
  double current_distance = 0; // For use in keeping track of the weight it took to get to the current point

  list<pair<int, double>>::iterator vert_it;

  vert_it = input_list.vertices[starting].begin();

  // Adding the very first items to the queue from the starting poing
  while(vert_it != input_list.vertices[starting].end()) // While not at the end of the list
  {
    distance[(vert_it) -> first] = (vert_it) -> second; // The distance for the node is updated to its weight
    prev_verts[(vert_it) -> first] = starting; // Each node points back to the start at the moment
                                               // because it is currently the most efficient
    verts.push((vert_it) -> first); // Adding these nodes onto the queue because their weights were changed
    (vert_it)++; // Moving through the list
  }

  verts.pop(); // Removing the starting item from the queue

  while(!verts.empty()) // For each vertex
  {
    queue_item = verts.front();
    verts.pop();

    current_distance = distance[queue_item];
    vert_it = input_list.vertices[queue_item].begin(); // Starting a new list head

    while(vert_it != input_list.vertices[queue_item].end()) // For each list node in each vertex
    {
      if((current_distance + (vert_it -> second) < distance[(vert_it) -> first]))
      { // If the distance taken to get here plus the distance taken to get to the target node is better than what the node already has
        distance[(vert_it) -> first] = current_distance + (vert_it) -> second; // Then replace the iter index in the weights with the new weight
        prev_verts[(vert_it) -> first] = queue_item; // Set the previous of the iter index item to the queue item that was popped
        verts.push((vert_it) -> first); // Since the iter item index had its weight changed, add it to the queue to be checked
      }

      vert_it++; // Moving through the list
    }
  }

  if(distance[target] == INT_MAX) // If the distance has no change, there were no connections
  {
    cout << endl << " Starting and ending path have no connection. Exiting..." << endl << endl;
    return;
  }

  cout << endl << " Shortest distance from " << starting << " -> " << target << " is " << distance[target] << endl
       << " Path is outlined below: " << endl << endl;


  // Reversing through the path
  stack<int> reverse_path;
  reverse_path.push(target);

  while(prev_verts[target] != starting)
  {
    reverse_path.push(prev_verts[target]);
    target = prev_verts[target];
  }
  reverse_path.push(starting);

  cout << " "; // Aesthetic purposes

  while(reverse_path.size() != 1)
  {
    cout << reverse_path.top() << " -> ";
    reverse_path.pop();
  }

  cout << reverse_path.top() << endl << endl;
}
