# Project Proposal

## Leading Question 
We're focusing the scope of our project on the MTD bus system on campus. The broad idea of what we want to learn from this dataset is being able to provide more useful information to bus users, including students as well as people who use the MTD bus route but are not on campus residents. This relates to the issue of trying to improve it for passenger utility since that is who this information is intended for. 


As such, there's a few specific pieces of information we wish to find to achieve this goal. These are a) finding the shortest path that is also the cheapest (for people who use this system off campus, as buses off campus require money) and b) finding which areas are strongly connected, because this can provide different options to reach a certain stop. We will use a minimum spanning tree and Prim's algorithm to evaluate the shortest and cheapest path, as the weights can represent the cost of going from one path to another. We will use Tarjan’s algorithm to find strongly connected components (for the sake of effectiveness, we will be stricting this to on campus using bounds that will also be used with Prim's) because this will indicate different ways to reach a stop, if perhaps a user's plan changes or they miss a stop. DFS traversal will also be utilized to check if two stops are on the same route, as well to judge the length of the path of one stop on the route from another. 

## Dataset Acquisition

The General Transit Feed Specification (GTFS) is an open format that defines schedule and geographic information for public transportantion systems. The feed is available for download at the MTD Developer Resources website (https://developer.cumtd.com/).

#### Data Format
The input data set comes from the MTD Developer Resources website. The dataset consists of TXT files, each presenting data that, combined, compose the bus routes at the Champaign-Urbana Mass Transit District. The whole dataset is 103.3 MB, but we are not going to use all the data; only `shapes.txt`, `stops.txt`, `fare_attributes.txt`, and `fare_rules.txt`.

- `shapes.txt`: Shapes describe the path that a vehicle travels along a route alignment.

- `stops.txt`: Stops describe all the information about the stops throughout the CUMTD. It includes details such as stop IDs, description of location, stop geographical coordinates, and location type.

- `fare_attributes.txt` and `fare_rules.txt`: Contains information about the fares. Includes data such as price and currency type, transfers permitted with certain fare, route ID associated with the fare, origin and destination ID associated with fare.

#### Data Correction
TXT files can be converted to CSV; therefore, we are simply going to read the files as comma-separated values and store this information into our algorithms.

In order to make sure data is error free (which will include checking for missing entries and correcting them, as well as other possible concerns), we will focus on being careful with naming types and routes. We assume most errors would come from our own error instead of from the file in terms of the dataset. Nonetheless, we can implement to check for empty entries. We should exactly map all types of name IDs we are going to use to minimize the chance of wrong entries. We can also check the bus routes manually online to make sure the data is correct.

#### Data Storage
Minimum spanning tree will be used for the shortest cheapest path. The space complexity is O(n) using Prim’s Algorithm (normally is O(n^2)).

Trees for the bus routes and DFS will have a space complexity of O(n), since we need every node to be stored.

Connected components checks will require a graph. Using Tarjan’s algorithm for strongly connected components, the space complexity is O(V * (2 + 5w)), where V is the number of nodes, and w is the machine word size. Each node has two fields which requires 2 words, one bit for checking whether or not a node is on the stack used by the algorithm, one bit for checking the validity of the indices of the nodes (whether or not it’s been traversed or not), one word is required to hold the current node, and another is required to store the current position in our list of edges.


## Algorithm 

#### Function Inputs

The Prim’s algorithm requires converting our stored dataset into a minimum spanning tree where we keep track of costs with the weights. Within our scenario, this will mean creating a minimum spanning tree that has weight information for the cost, as well as distance so we can keep track of both of these factors. For Tarjan's algorithm, a tree is necessary in order to conduct the analysis to find strongly connected components. As such, we can create a few trees for a few popular bus routes (one for each direction), and find the strongly connected components for each of these trees. These will be the same trees that we will conduct DFS traversals on in order to find if two stops are within a route, as well as the length between these stops. 

#### Function Outputs

The return value for our implementation of the Prims algorithm function itself will likely be a void data type but we will be editing a variable by reference to be able to print a visual representation of the route as well as store a list of bus routes and transfer points needed to reach the destination in the most cost-effective manner possible. Our function output for the Tarjan algorithm will be a list of stop pairs that are strongly connected to each other, and which single bus routes can be used to connect the two stops. If there is a requested start/end stop the algorithm's output will simply display which routes (including direction) can be used to get from one point to another, and give the connection a numeric “score”.

#### Function Efficiency
The efficiency of our implementation of Prim's algorithm will be based on an implementation using an adjacency matrix. The time complexity we will be aiming for is O(V^2), and the space complexity is O(n) for the minimum spanning tree generated.

For Tarjan's algorithm, ideally we’d like to hit O(n) time, since it relies on DFS, which is O(n). More specifically, the runtime is O(V+E), which is the sum of the number of vertices and edges in our Strongly Connected Components data structure. The space complexity of Tarjan’s algorithm is O(V * (2+5w)) (explained above).


## Timeline
Along with the work of each week, by the end of the week update slides that keeps track of our work and updates to the notes for the final readme (use descriptive commit changes for each week to aid this process).

#### Week 1 (11/7)
We will aim to have most of data parsing done (will split between two members), and have at least one of the algorithms drafted (other two members).

#### Week 2 (11/14)
We will aim to finish data parsing, have one algorithm fully done and have the second algorithm drafted.

####	Thanksgiving Break
If anyone has work that they would like to work on/get ahead during this time, feel free to do it but not expected.

#### Week 3 (11/28)
We should have the code fully finished by mid-week (allowing time for debugging as well as starting spend more time on the deliverables).

#### Week 4 (12/5)
We will have created and finalized the video of our project and the written report, as well as double checking the functionality of our code.
