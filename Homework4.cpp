#include <iostream>
#include <list>
#include <stack>

using namespace std;

struct node
  {
    int data;
    node *next;
  };

class Digraph
{
    int V;
    list<int> *adj;

public:
    Digraph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }

    // function to add an edge to graph
    void addEdge(int u, int v)
    {
      //WIP
        //adj[u].push_back(v);
        node *head = adj[u];

        node *temp = new node;
        temp->data = v;
        temp->next = NULL;
        if (head == NULL)
        {
          head = temp;
          tail = temp;
          temp = NULL:
        }
        else
        {
          tail->next = temp;
          tail = temp;
        }
    }

    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
    {
        // Mark the current node as visited.
        visited[v] = true;

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                topologicalSortUtil(*i, visited, Stack);

        // Push current vertex to stack which stores result
        Stack.push(v);
    }

    // prints a Topological Sort of the complete graph
    void topologicalSort()
    {
        stack<int> Stack;

        // Mark all the vertices as not visited
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        // Call the recursive helper function to store Topological
        // Sort starting from all vertices one by one
        for (int i = 0; i < V; i++)
          if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

        // Print contents of stack
        while (Stack.empty() == false)
        {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }

    // Displays Digraph
    void displayDigraph()
    {
        for (int u = 0; u < V; ++u)
        {
            cout << "\n Vertex " << u << ": head";
            for (int v : adj[u])
               cout << " -> " << v;
        }
        printf("\n");
    }

    void acyclicCheck()
    {
      // TODO
    }
};

int main()
{
    // Create a graph given in the above diagram
    Digraph dg(6);
    dg.addEdge(5, 2);
    dg.addEdge(5, 0);
    dg.addEdge(4, 0);
    dg.addEdge(4, 1);
    dg.addEdge(2, 3);
    dg.addEdge(3, 1);
    dg.displayDigraph();

    //cout << "Following is a Topological Sort of the given graph \n";
    //dg.topologicalSort();

    return 0;
}
