#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <list>
#include <stack>
using namespace std;

struct node
{
    int data;
    struct node* next;
};

struct nodeList
{
    struct node *head;
};

class Digraph
{
    private:
        int V;
        nodeList* array;
    public:
        Digraph()
        {

        }

        ~Digraph()
        {
          delete[] array;
        }

        Digraph(int V)
        {
            this->V = V;
            array = new nodeList [V];
            for (int i = 0; i < V; ++i)
                array[i].head = NULL;
        }

        void addEdge(int from, int to)
        {

            node* head = array[from].head;
        	  node* temp = new node;

            temp->data = to;
            temp->next = NULL;
            temp->next = array[from].head;
            array[from].head = temp;
        }

        void deleteEdge(int from, int to)
        {
            node* head = array[from].head;
            if (head == NULL)
            {
              cout<<"Edge does not exist"<<endl;
            }
            node* temp = new node;
            node* prev = new node;
            node* next = new node;
            bool nodeDeleted = false;
            temp = head;
            while ((temp != NULL) && !nodeDeleted) {
              if (temp->data == to)
              {
                next = temp->next;
                if (temp == head)
                {
                  array[from].head = next;
                }
                else
                {
                  prev->next = next;
                }
                nodeDeleted = true;
              }
              prev = temp;
              temp = temp->next;
            }
            if (!nodeDeleted)
            {
               cout<<"Edge does not exist"<<endl;
            }
        }

        void SortUtil(int vertex, bool visited[], stack<int>& Stack)
        {
          bool breakOut = false;
        	visited[vertex] = true;

          node* head = array[vertex].head;
          node* temp = new node;
          temp = head;

          if (temp == NULL)
          {
          	Stack.push(vertex);
            return;
          }
          while (temp != NULL && !breakOut)
          {
            int i = temp->data;
            if (!visited[i])
            {
              SortUtil(i, visited, Stack);
            }
            if (temp->next == NULL)
            {
              breakOut = true;
            }
            else
            {
              temp = temp->next;
            }
          }

        	// Push current vertex to stack which stores result
        	Stack.push(vertex);
        }

        void topologicalsort()
        {
        	stack<int> Stack;
        	int num;
        	int count = 1;

        	// Mark all the vertices as not visited
        	bool* visited = new bool[V];
        	for (int i = 0; i < V; i++)
        	{
        		visited[i] = false;
        	}

        	// Call the recursive helper function to store Topological
        	// Sort starting from all vertices one by one
        	for (int i = 0; i < V; i++)
        	{
        		if (visited[i] == false)
        		{
        			SortUtil(i, visited, Stack);
        		}
        	}
        	while (Stack.empty() == false)
        	{
        		num = Stack.top();
        		cout << count << ")" << num << endl;
        		Stack.pop();
        		count++;
        	}
        }

        bool CycleUtil(int vertex, bool visited[], bool* rs)
        {
        	if (visited[vertex] == false)
        	{
        		// Mark the current node as visited and part of recursion stack
        		visited[vertex] = true;
        		rs[vertex] = true;
            node* head = array[vertex].head;
            node* temp = new node;
            temp = head;

            while (temp != NULL)
            {
              int i = temp->data;
              bool x = !visited[i];
              if (!visited[i] && CycleUtil(i, visited, rs))
              {
                return true;
              }
              else if (rs[i])
              {
                return true;
              }
              temp = temp->next;
            }
        	}
        	rs[vertex] = false;  // remove the vertex from recursion stack
        	return false;
        }

        bool acyclicCheck()
        {
        	// Mark all the vertices as not visited and not part of recursion
        	bool* visited = new bool[V];
        	bool* recStack = new bool[V];
        	for (int i = 0; i < V; i++)
        	{
        		visited[i] = false;
        		recStack[i] = false;
        	}

        	// Call the recursive helper function to detect cycle in different
        	// DFS trees
        	for (int i = 0; i < V; i++)
        	{
        		if (CycleUtil(i, visited, recStack))
        		{
        			return true;
        		}
        	}
        	return false;
        }

        void displayDigraph()
        {
            int v;
            for (v = 0; v < V; ++v)
            {
                node* tmp = array[v].head;
                cout<<"Vertex "<<v<<" head";
                while (tmp)
                {
                    cout<<"->"<<tmp->data;
                    tmp = tmp->next;
                }
                cout<<endl;
            }
        }
};

int main()
{
    bool cyclic;
    Digraph dg(5);
    dg.addEdge(0, 1);
    dg.addEdge(0, 4);
    dg.addEdge(0, 3);
    dg.addEdge(1, 2);
    dg.addEdge(1, 3);
    dg.addEdge(1, 4);
    dg.addEdge(2, 3);
    dg.addEdge(3, 4);
    dg.displayDigraph();
    //dg.deleteEdge(1, 3);
    //dg.topologicalsort();
    //dg.addEdge(4, 2);
    cyclic = dg.acyclicCheck();
    cout<<"Cyclic: "<<cyclic<<endl;

    return 0;
}
