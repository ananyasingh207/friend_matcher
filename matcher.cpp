#include <iostream> 
#include <vector>
#include <queue>
#include <unordered_map>
#include <list> 
#include <algorithm>
#include <stack>
#include <string>
#include <set>
using namespace std;

class Graph {
public:
    unordered_map<int, list<int>> adj;
    int nodes;

    Graph(int n) {
        nodes = n;
    }

    void addEdge(int u, int v, bool direction = 0) {
        adj[u].push_back(v);
        if (direction == 0) {
            adj[v].push_back(u);
        }
    }

    void printAllUsers(const vector<string>& names) {
        cout << "All users:\n";
        for (int i = 0; i < nodes; i++) {
            cout << i << ": " << names[i] << "\n";
        }
    }

    void printFriends(int user, const vector<string>& names) {
        cout << "Friends of " << names[user] << ":\n";
        if (adj.find(user) == adj.end() || adj[user].empty()) {
            cout << "  No friends found.\n";
            return;
        }
        for (auto f : adj[user]) {
            cout << "  " << names[f] << "\n";
        }
    }

    void printMutualFriends(int u, int v, const vector<string>& names) {
        cout << "Mutual friends between " << names[u] << " and " << names[v] << ":\n";
        set<int> friends_u(adj[u].begin(), adj[u].end());
        set<int> friends_v(adj[v].begin(), adj[v].end());
        vector<int> mutual;
        for (int f : friends_u) {
            if (friends_v.count(f)) mutual.push_back(f);
        }
        if (mutual.empty()) {
            cout << "  None\n";
        } else {
            for (int mf : mutual) cout << "  " << names[mf] << "\n";
        }
    }

    void recommendFriends(int user, const vector<string>& names) {
        cout << "Friend recommendations for " << names[user] << " (friends of friends):\n";
        set<int> direct_friends(adj[user].begin(), adj[user].end());
        set<int> recommendations;

        for (int friend1 : direct_friends) {
            for (int friend2 : adj[friend1]) {
                if (friend2 != user && direct_friends.count(friend2) == 0) {
                    recommendations.insert(friend2);
                }
            }
        }

        if (recommendations.empty()) {
            cout << "  No recommendations found.\n";
        } else {
            for (int r : recommendations) cout << "  " << names[r] << "\n";
        }
    }

    void bfs(int start, const vector<string>& names) {
        vector<bool> visited(nodes, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << "BFS traversal starting from " << names[start] << ": ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << names[node] << " ";
            for (auto neigh : adj[node]) {
                if (!visited[neigh]) {
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }
        cout << "\n";
    }

    void dfsUtil(int node, vector<bool>& visited, const vector<string>& names) {
        visited[node] = true;
        cout << names[node] << " ";
        for (auto neigh : adj[node]) {
            if (!visited[neigh]) {
                dfsUtil(neigh, visited, names);
            }
        }
    }

    void dfs(int start, const vector<string>& names) {
        vector<bool> visited(nodes, false);
        cout << "DFS traversal starting from " << names[start] << ": ";
        dfsUtil(start, visited, names);
        cout << "\n";
    }

    void shortestPath(int source, int destination, const vector<string>& names) {
        vector<bool> visited(nodes, false);
        vector<int> parent(nodes, -1);
        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int front = q.front();
            q.pop();
            if (front == destination) break;

            for (auto neigh : adj[front]) {
                if (!visited[neigh]) {
                    visited[neigh] = true;
                    parent[neigh] = front;
                    q.push(neigh);
                }
            }
        }

        if (!visited[destination]) {
            cout << "No path exists between " << names[source] << " and " << names[destination] << "\n";
            return;
        }

        vector<int> path;
        for (int cur = destination; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest path between " << names[source] << " and " << names[destination] << ":\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << names[path[i]];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
};

int findUserByName(const vector<string>& names, const string& name) {
    for (int i = 0; i < (int)names.size(); i++) {
        if (names[i] == name) return i;
    }
    return -1;
}

int main() {
    vector<string> names = {
        "Aarav", "Vivaan", "Aditya", "Arjun", "Reyansh",
        "Sai", "Krishna", "Ishaan", "Shaurya", "Anay",
        "Kabir", "Vihaan", "Arnav", "Atharv", "Dev",
        "Rudra", "Dhruv", "Madhav", "Om", "Advait"
    };
    int n = (int)names.size();

    Graph g(n);

    // Predefined friendships (undirected)
    g.addEdge(0, 1); // Aarav - Vivaan
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 8);
    g.addEdge(7, 9);
    g.addEdge(8, 10);
    g.addEdge(9, 11);
    g.addEdge(10, 12);
    g.addEdge(11, 13);
    g.addEdge(12, 14);
    g.addEdge(13, 15);
    g.addEdge(14, 16);
    g.addEdge(15, 17);
    g.addEdge(16, 18);
    g.addEdge(17, 19);
    g.addEdge(0, 19); // Making graph somewhat connected

    int choice;
    do {
        cout << "\nMain menu:\n";
        cout << " 1) Show all users\n";
        cout << " 2) Show friends of a user\n";
        cout << " 3) Show mutual friends between two users\n";
        cout << " 4) Recommend friends for a user (friends-of-friends)\n";
        cout << " 5) Shortest path between two users\n";
        cout << " 6) Add friendship\n";
        cout << " 7) BFS traversal from a user\n";
        cout << " 8) DFS traversal from a user\n";
        cout << " 0) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            g.printAllUsers(names);
        } else if (choice == 2) {
            cout << "Enter user name: ";
            string user;
            cin >> user;
            int idx = findUserByName(names, user);
            if (idx == -1) cout << "User not found.\n";
            else g.printFriends(idx, names);
        } else if (choice == 3) {
            cout << "Enter first user name: ";
            string u1, u2;
            cin >> u1;
            cout << "Enter second user name: ";
            cin >> u2;
            int idx1 = findUserByName(names, u1);
            int idx2 = findUserByName(names, u2);
            if (idx1 == -1 || idx2 == -1) cout << "One or both users not found.\n";
            else g.printMutualFriends(idx1, idx2, names);
        } else if (choice == 4) {
            cout << "Enter user name: ";
            string user;
            cin >> user;
            int idx = findUserByName(names, user);
            if (idx == -1) cout << "User not found.\n";
            else g.recommendFriends(idx, names);
        } else if (choice == 5) {
            cout << "Enter source user name: ";
            string src;
            cin >> src;
            cout << "Enter destination user name: ";
            string dest;
            cin >> dest;
            int idx_src = findUserByName(names, src);
            int idx_dest = findUserByName(names, dest);
            if (idx_src == -1 || idx_dest == -1) cout << "One or both users not found.\n";
            else g.shortestPath(idx_src, idx_dest, names);
        } else if (choice == 6) {
            cout << "Enter first user name: ";
            string u1, u2;
            cin >> u1;
            cout << "Enter second user name: ";
            cin >> u2;
            int idx1 = findUserByName(names, u1);
            int idx2 = findUserByName(names, u2);
            if (idx1 == -1 || idx2 == -1) cout << "One or both users not found.\n";
            else {
                g.addEdge(idx1, idx2);
                cout << "Friendship added between " << u1 << " and " << u2 << ".\n";
            }
        } else if (choice == 7) {
            cout << "Enter user name to start BFS: ";
            string user;
            cin >> user;
            int idx = findUserByName(names, user);
            if (idx == -1) cout << "User not found.\n";
            else g.bfs(idx, names);
        } else if (choice == 8) {
            cout << "Enter user name to start DFS: ";
            string user;
            cin >> user;
            int idx = findUserByName(names, user);
            if (idx == -1) cout << "User not found.\n";
            else g.dfs(idx, names);
        } else if (choice != 0) {
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    cout << "Exiting program.\n";
    return 0;
}
