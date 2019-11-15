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
            temp = head;
            while (temp != NULL)
            {
              if (temp->data == to)
              {
                cout<<"Edge already exists"<<endl;
                return;
              }
              temp = temp->next;
            }

            node* temp2 = new node;
            temp2->data = to;
            temp2->next = NULL;
            temp2->next = array[from].head;
            array[from].head = temp2;
        }

        void deleteEdge(int from, int to)
        {
            node* head = array[from].head;
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
               cout<<"Edge not found"<<endl;
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

        void topologicalSort()
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
          cout<<"**************Topological Sort**************"<<endl;
          cout<<"Tasks in Order:"<<endl;
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

        bool cyclicCheck()
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
            cout<<"*****************************"<<endl;
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
            cout<<"*****************************"<<endl;
        }
};

void displayTaskList(string tasks[], int cnt) {
  int size = cnt;
	//size = sizeof(tasks);
	if (size == 0)
	{
		cout << "Task list is empty." << endl;
	}
	else
	{
		cout << "---Task List---" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << i << ") " << tasks[i] << endl;
		}
	}
}

bool validString(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
		{
			return false;
		}
	}
	return true;
}

bool validEntry(int from, int to, int cnt)
{
  if ((from >= 0 && from <= cnt) && (to >= 0 && to <= cnt))
  {
    return true;
  }
  cout<<"One of your entries is invalid."<<endl;
  return false;
}

void clearScreen()
{
  int n;
  for (n = 0; n < 10; n++)
    cout<<"\n\n\n\n\n\n\n\n\n\n"<<endl;
}

int main()
{
    string tasks[50];
    int taskFrom, taskTo;
    string menuChoice, from, to, task;
    bool recordTasks = true;
    bool running = true;
    bool cyclic = false;
    int cnt = 0;
    while (recordTasks)
    {
        cout<<"\nEnter task "<<cnt<<" here (enter 'stop' when you are done entering tasks):"<<endl;
        //cin >> task;
        getline(cin, task);
        if (task == "stop")
        {
          recordTasks = false;
          break;
        }
        else{
          tasks[cnt] = task;
          cnt++;
        }
    }
    Digraph dg(cnt);
    clearScreen();
    while (running)
    {
      cout<<"\n\n\n"<<endl;
  		displayTaskList(tasks, cnt);
  		cout << "\n--------------------Menu----------------------" << endl;
  		cout << "[1] Specify Order Relation (Add Edge)" << endl;
  		cout << "[2] Delete Order Relation (Delete Edge)" << endl;
  		cout << "[3] Display Adjacency List" << endl;
      cout << "[4] Output Tasks in Order (Topological sort)" << endl;
      cout << "[5] Quit"<< endl;
      cout << "----------------------------------------------" << endl;
  		cin >> menuChoice;
      cout<<endl;
				if (menuChoice == "1")
				{
					cout<<"Enter the Order Relation for a task"<<endl;
          cout<<"i.e., If \'Task 3\' precedes \'Task 1\' then "<<endl;
          cout<<"From: 3"<<endl;
          cout<<"To: 1"<<endl;
          cout<<"---------"<<endl;
          cout<<"From: ";
					cin >> from;
          cout<<"To: ";
          cin >> to;
					cout << endl;
					if (validString(from) && validString(to))
					{
            taskFrom = stoi(from);
            taskTo = stoi(to);
            if (validEntry(taskFrom, taskTo, cnt-1))
            {
  						dg.addEdge(taskFrom, taskTo);
            }
					}
					else
					{
						cout<<"One of your entered values was not valid, Please try again."<<endl;
					}
				}
				else if (menuChoice == "2")
				{
          cout<<"Enter the Order Relation you want to delete"<<endl;
          cout<<"i.e., If Order Relation (3,1) is being deleted then"<<endl;
          cout<<"from: 3"<<endl;
          cout<<"to: 1"<<endl;
          cout<<"---------"<<endl;
          cout<<"From: ";
					cin >> from;
          cout<<"To: ";
          cin >> to;
					cout << endl;
          if (validString(from) && validString(to))
					{
            taskFrom = stoi(from);
            taskTo = stoi(to);
            if (validEntry(taskFrom, taskTo, cnt-1))
            {
  						dg.deleteEdge(taskFrom, taskTo);
            }
					}
					else
					{
						cout<<"One of your entered values was not valid, Please try again."<<endl;
					}
				}
				else if (menuChoice == "3")
				{
					dg.displayDigraph();
				}
				else if (menuChoice == "4")
        {
					cyclic = dg.cyclicCheck();
          if (cyclic)
          {
            cout<<"ERROR: The digraph is not acyclic."<<endl;
          }
          else
          {
            dg.topologicalSort();

          }
				}
        else if (menuChoice == "5")
				{
					running = false;
				}
        else
        {
          cout<<"Enter a correct value."<<endl;
        }
    }

    return 0;
}
