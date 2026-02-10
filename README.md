# Social Network Graph Analyzer

## Description
A C++ console application that simulates a social network using graph data structures. It allows users to manage friendships, find mutual friends, recommend friends (friends of friends), and perform graph traversals (BFS, DFS).

## Features
-   Show all users
-   Show friends of a user
-   Show mutual friends between two users
-   Recommend friends (friends of friends)
-   Find shortest path between two users
-   Add friendship
-   BFS traversal from a user
-   DFS traversal from a user

## Getting Started

### Prerequisites
-   A C++ compiler (e.g., g++).

### Compilation
To compile the program, use the following command:
```bash
g++ matcher.cpp -o matcher
```

### Running the application
To run the application, use the following command:
```bash
./matcher
```

## Usage
The application provides an interactive menu. You can select an option by entering the corresponding number.
1.  **Show all users:** Lists all users in the network.
2.  **Show friends of a user:** Lists the friends of a specific user.
3.  **Show mutual friends between two users:** Lists the mutual friends of two users.
4.  **Recommend friends for a user:** Recommends friends based on mutual friends (friends of friends).
5.  **Shortest path between two users:** Finds the shortest path between two users using BFS.
6.  **Add friendship:** Adds a new friendship between two users.
7.  **BFS traversal from a user:** Performs a Breadth-First Search traversal starting from a user.
8.  **DFS traversal from a user:** Performs a Depth-First Search traversal starting from a user.
0.  **Exit:** Exits the program.
