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

class Digraph
{
	int vertices;
	list<int>* adj;
	void SortUtil(int vertex, bool visited[], stack<int>& Stack);
	bool CycleUtil(int vertex, bool visited[], bool* rs);
public:
	Digraph();
	~Digraph();
	Digraph(int Vertex);
	void addEdge(int vertex1, int vertex2);
	bool doesEdgeExist(int vertex1, int vertex2);
	void find_edges(int vertex1);
	void deleteEdge(int vertex1, int vertex2);
	void topologicalsort(string input_array[]);
	bool ContainsCycle();
};

void Digraph::SortUtil(int vertex, bool visited[], stack<int>& Stack)
{
	visited[vertex] = true;

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i;
	for (i = adj[vertex].begin(); i != adj[vertex].end(); ++i)
	{
		if (!visited[*i])
		{
			SortUtil(*i, visited, Stack);
		}
	}

	// Push current vertex to stack which stores result 
	Stack.push(vertex);
}

bool Digraph::CycleUtil(int vertex, bool visited[], bool* rs)
{
	if (visited[vertex] == false)
	{
		// Mark the current node as visited and part of recursion stack 
		visited[vertex] = true;
		rs[vertex] = true;

		list<int>::iterator i;
		for (i = adj[vertex].begin(); i != adj[vertex].end(); ++i)
		{
			if (!visited[*i] && CycleUtil(*i, visited, rs))
			{
				return true;
			}
			else if (rs[*i])
			{
				return true;
			}
		}

	}
	rs[vertex] = false;  // remove the vertex from recursion stack 
	return false;
}

Digraph::Digraph()
{
	//No parameter has been entered into our constructor
	//We will do nothing in this situation
}

Digraph::~Digraph()
{
	delete[] adj;
}

Digraph::Digraph(int Vertex)
{
	this->vertices = Vertex;
	adj = new list<int>[Vertex];
}

void Digraph::addEdge(int vertex1, int vertex2)
{
	adj[vertex1].push_back(vertex2);
}

bool Digraph::doesEdgeExist(int vertex1, int vertex2)
{
	int size, edge;
	size = adj[vertex1].size();
	for (int i = 0; i < size; i++)
	{
		edge = adj[vertex1].front();
		if (edge == vertex2)
		{
			return true;
		}
		adj[vertex1].push_back(adj[vertex1].front());
		adj[vertex1].pop_front();
	}
	return false;
}

void Digraph::find_edges(int vertex1)
{
	int size;
	size = adj[vertex1].size();
	if (size == 0)
	{
		cout << vertex1 << " is not connected to any other vertex" << endl;
	}
	else
	{
		cout << vertex1 + 1 << " is connected to: ";
		for (int i = 0; i < size; i++)
		{
			cout << adj[vertex1].front() + 1 << ", ";
			adj[vertex1].push_back(adj[vertex1].front());
			adj[vertex1].pop_front();
		}
		cout << endl;
	}
}

void Digraph::deleteEdge(int vertex1, int vertex2)
{
	if (doesEdgeExist(vertex1, vertex2))
	{
		adj[vertex1].remove(vertex2);
	}
	cout << "The edge does not exist and thus cannot be deleted. Please try again." << endl;
}

void Digraph::topologicalsort(string input_array[])
{
	stack<int> Stack;
	int num;
	int count = 1;

	// Mark all the vertices as not visited 
	bool* visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
	{
		visited[i] = false;
	}

	// Call the recursive helper function to store Topological 
	// Sort starting from all vertices one by one 
	for (int i = 0; i < vertices; i++)
	{
		if (visited[i] == false)
		{
			SortUtil(i, visited, Stack);
		}
	}
	while (Stack.empty() == false)
	{
		num = Stack.top();
		cout << count << ")" << input_array[num] << endl;
		Stack.pop();
		count++;
	}
}

bool Digraph::ContainsCycle()
{
	// Mark all the vertices as not visited and not part of recursion 
	bool* visited = new bool[vertices];
	bool* recStack = new bool[vertices];
	for (int i = 0; i < vertices; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	// Call the recursive helper function to detect cycle in different 
	// DFS trees 
	for (int i = 0; i < vertices; i++)
	{
		if (CycleUtil(i, visited, recStack))
		{
			return true;
		}
	}
	return false;
}
bool isStringValid(string input_string)
{
	for (int i = 0; i < input_string.length(); i++)
	{
		if (!isdigit(input_string[i]))
		{
			return false;
		}
	}
	return true;
}
bool ValidateNumbers(string input_string)
{
	char option[6] = { '0', '1', '2', '3', '4', '5' };
	for (int i = 0; i < input_string.length(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (option[j] == input_string[i])
			{
				break;
			}
			else if ((j == 4) && (option[j] != input_string[i]))
			{
				return false;
			}
			continue;
		}
	}
	return true;
}
void addtoTaskArray(string input_string, string input_array[])
{
	int length = sizeof(input_array);
	for (int x = 0; x < length; x++)
	{
		if (input_array[x].empty())
		{
			input_array[x] = input_string;
			break;
		}
	}
}
void PrintArray(string input_array[])
{
	int size;
	size = input_array->size();
	if (size == 0)
	{
		cout << "You did not enter any tasks." << endl;
	}
	else
	{
		cout << "Here are the list of tasks that you entered:" << endl;
		for (int i = 0; i < size; i++)
		{
			if (!input_array[i].empty())
			{
				cout << i+1 << ". " << input_array[i] << endl;
			}
			else
			{
				break;
			}
		}
	}
}
int NumberofTasks()
{
	int count = 0;
	return count;
}
int main()
{
	int vertex1, vertex2, count;
	string tasks[100];
	string choice, more_tasks;
	bool loop, loop2;
	loop = true;
	loop2 = true;
	string input_task;
	count = 1;
	while (loop2)
		{
			cout << "Enter task " << count  << " here (enter 'end' when done):" << endl;
			getline(cin, choice);
			if (choice == "end")
			{
				loop2 = false;
				break;
			}
			else{
				input_task = choice;
				addtoTaskArray(input_task, tasks);
				count++;
			}
		}
	Digraph mygraph(count - 1);
	while (loop) {
		PrintArray(tasks);
		cout << "What would you like to do now?" << endl;
		cout << "1. Pair two more tasks together in the digraph" << endl;
		cout << "2. Find all the edges connected to one vertex:" << endl;
		cout << "3. Output the topological sort of the current digraph and end the program" << endl;
		cin >> more_tasks;
			while (loop)
			{
				if (more_tasks == "1")
				{
					cout << "Enter the two tasks that should be linked(no spaces and enter number associated with list): ";
					cin >> choice;
					cout << endl;
					if (isStringValid(choice) && (choice.length() == 2) && ValidateNumbers(choice))
					{
						char task1 = choice[0];
						char task2 = choice[1];
						vertex1 = task1 - '1';
						vertex2 = task2 - '1';
						mygraph.addEdge(vertex1, vertex2);
					}
					else if (choice.length() != 2)
					{
						cout << "You did not enter two tasks. Try again." << endl;
					}
					else if (!ValidateNumbers(choice))
					{
						cout << "At least one of the task numbers you entered is not from the list above. Please try again." << endl;
					}
					else
					{
						cout << "There were some invalid characters in your input string. Please try again." << endl;
					}
					break;
				}
				else if (more_tasks == "2")
				{
					cout << "Enter the vertex you want to find all the edges for here: ";
					cin >> choice;
					char task1 = choice[0];
					vertex1 = task1 - '1';
					mygraph.find_edges(vertex1);
					break;
				}
				else if (more_tasks == "3")
				{
					if (mygraph.ContainsCycle())
					{
						cout << "Error: The graph contains a cycle and thus we cannot perform a topological sort." << endl;
					}
					else
					{
						cout << "Original List: " << endl;
						PrintArray(tasks);
						cout << "Topological List: " << endl;
						mygraph.topologicalsort(tasks);
					}
					loop = false;
					break;
				}
				else{
					cout << "Enter a correct value." << endl;
					break;
				}
			}
		}
	return 0;
}