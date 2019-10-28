#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>

using namespace std;

class Person
{
    private:
        string fname;
        string lname;
        string mnumber;

    public:
        void setFname(string _fname)
        {
            fname = _fname;
        }

        void setLname(string _lname)
        {
            lname = _lname;
        }

        void setMnumber(string _mnumber)
        {
            mnumber = _mnumber;
        }

        string getFname()
        {
            return fname;
        }

        string getLname()
        {
            return lname;
        }

        string getMnumber()
        {
            return mnumber;
        }
};

class Book
{
    struct node 
    {
        Person data;
        node* left;
        node* right;
    };

    node* x;

    node* makeEmpty(node* root) {
        if(root == NULL)
            return NULL;
        {
            makeEmpty(root->left);
            makeEmpty(root->right);
            delete root;
        }
        return NULL;
    }

    node* insert(Person tmpPerson, node* root)
    {
        if(root == NULL)
        {
            root = new node;
            root->data = tmpPerson;
            root->left = root->right = NULL;
        }
        else if(tmpPerson.getLname() < root->data.getLname())
        {
            root->left = insert(tmpPerson, root->left);
        }
        else if(tmpPerson.getLname() > root->data.getLname())
        {
            root->right = insert(tmpPerson, root->right);
        }
        else if (tmpPerson.getLname() == root->data.getLname())
        {
            if (tmpPerson.getFname() < root->data.getFname())
            {
                root->left = insert(tmpPerson, root->left);
            }
            else if (tmpPerson.getFname() > root->data.getFname())
            {
                root->right = insert(tmpPerson, root->right);
            }
        }
        return root;
    }

    node* findMin(node* root)
    {
        if(root == NULL)
        {
            return NULL;
        }
        else if(root->left == NULL)
        {
            return root;
        }
        else
        {
            return findMin(root->left);
        }
    }

    node* findMax(node* root) {
        if(root == NULL)
        {
            return NULL;
        }
        else if(root->right == NULL)
        {
            return root;
        }
        else
        {
            return findMax(root->right);
        }
    }

    node* remove(node* root, Person tmpPerson) 
    {
        if (root == NULL)
        {
            return root; 
        } 
  
        // If the key to be deleted is smaller than the root's key, 
        // then it lies in left subtree 
        if (tmpPerson.getLname() < root->data.getLname()) 
        {
            root->left = remove(root->left, tmpPerson); 
        }
        // If the key to be deleted is greater than the root's key, 
        // then it lies in right subtree 
        else if (tmpPerson.getLname() > root->data.getLname()) 
        {
            root->right = remove(root->right, tmpPerson); 
        }
        else if (tmpPerson.getLname() == root->data.getLname())
        {
            if (tmpPerson.getFname() < root->data.getFname())
            {
                root->left = remove(root->left, tmpPerson); 
            }
            else if (tmpPerson.getFname() > root->data.getFname())
            {
                root->right = remove(root->right, tmpPerson);
            }
        }
    
        // if key is same as root's key, then This is the node 
        // to be deleted 
        else
        { 
            // node with only one child or no child 
            if (root->left == NULL) 
            { 
                struct node *temp = root->right; 
                free(root); 
                return temp; 
            } 
            else if (root->right == NULL) 
            { 
                struct node *temp = root->left; 
                free(root); 
                return temp; 
            } 
    
            // node with two children: Get the inorder successor (smallest 
            // in the right subtree) 
            struct node* temp = findMin(root->right); 
    
            // Copy the inorder successor's content to this node 
            root->data = temp->data; 
    
            // Delete the inorder successor 
            root->right = remove(root->right, temp->data); 
        } 
        return root; 
    }

    void inorder(node* root) 
    {
        if(root == NULL)
            return;
        inorder(root->left);
        cout << root->data.getLname() << ", "<< root->data.getFname() <<" "<< root->data.getMnumber() << endl;
        inorder(root->right);
    }

    node* find(node* root, string fname, string lname) 
    {
        if(root == NULL)
        {
            return NULL;
        }
        else if (root->data.getLname() == lname && root->data.getFname() == fname)
        {
            return root;
        }
        else if(lname < root->data.getLname())
        {
            return find(root->left, fname, lname);
        }
        else if(lname > root->data.getLname())
        {
            return find(root->right, fname, lname);
        }
        else if (lname == root->data.getLname())
        {
            if (fname < root->data.getFname())
            {
                return find(root->left, fname, lname);
            }
            else if (fname > root->data.getFname())
            {
                return find(root->right, fname, lname);
            }
        }
        else
        {
            return root;
        }
    }

public:
    Book() 
    {
        x = NULL;
    }

    ~Book()
    {
        x = makeEmpty(x);
    }

    void insert(Person tmpPerson)
    {
        x = insert(tmpPerson, x);
    }

    void remove(Person tmpPerson) 
    {
        x = remove(x, tmpPerson);
        cout << x->data.getLname() << " " << x->data.getFname() << endl;
    }

    void display() 
    {
        inorder(x);
        cout << endl;
    }

    Person search(string fname, string lname) 
    {
        x = find(x, fname, lname);
        return x->data;
    }
};

Person addContact() // adds contact to myContacts
{
    string fname, lname, mnumber;
    cout<<"Enter the first name, last name, and mobile of the contact you would like to add:"<< endl;
    cin>>fname>>lname>>mnumber;
    Person newPerson;
    newPerson.setFname(fname);
    newPerson.setLname(lname);
    newPerson.setMnumber(mnumber);
    return newPerson;
}

void findContact()
{

}

int main()
{
    Book bstBook;

    for (int i = 0; i < 5; i++)
    {
        Person tmpPerson = addContact();
        bstBook.insert(tmpPerson);
    }
    Person newPerson;
    newPerson.setFname("Nathan");
    newPerson.setLname("Sucher");
    newPerson.setMnumber("6");
    bstBook.search("A", "C");
    
    bstBook.display();
}