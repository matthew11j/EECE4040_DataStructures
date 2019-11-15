#include <iostream>
#include <cstdlib>
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
    //cout<<"\nDelete edge (1,3)"<<endl;
    //dg.deleteEdge(1, 3);
    //dg.displayDigraph();

    return 0;
}
