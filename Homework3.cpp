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

    node* remove(node* root, string name)
    {
        if (root == NULL)
        {
            return root;
        }
        if (name < (root->data.getLname() + root->data.getFname()))
        {
            root->left = remove(root->left, name);
        }
        else if (name > (root->data.getLname() + root->data.getFname()))
        {
            root->right = remove(root->right, name);
        }
        else
        {
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

            struct node* temp = findMin(root->right);

            root->data = temp->data;

            root->right = remove(root->right, (temp->data.getLname() + temp->data.getFname()));
        }
        return root;
    }

    void inorder(node* root)
    {
        if(root == NULL)
        {
            return;
        }
        inorder(root->left);
        cout << root->data.getLname() << "      "<< root->data.getFname() <<"       "<< root->data.getMnumber() << endl;
        inorder(root->right);
    }

    void writeContacts(node* root, string filename)
    {
        vector<string> vect;
        BSTtoVect(root, vect);
        ofstream saveFile;
        if (!saveFile.is_open())
        {
            saveFile.open( filename.c_str() );
        }

        if(root == NULL)
        {
            return;
        }
        for (int i = 0; i < vect.size(); i++) {
          saveFile << vect[i] << '\n';
        }
        saveFile.close();
    }

    // Converting a BST into a Vector
    void BSTtoVect(node* root, vector<string> &vect)
    {
        string contact;
        static int pos = 0;
        if(root == NULL) return;

        BSTtoVect(root->left, vect);
        contact = root->data.getLname() + "," + root->data.getFname() + "," + root->data.getMnumber() + ",";
        vect.push_back(contact);
        BSTtoVect(root->right, vect);
    }

    void restore(node* root, string filename)
    {
        x = makeEmpty(x);
        vector<string> vect;
        string element;
        ifstream readFile;
        //readFile.open( filename.c_str() );
        readFile.open( filename );
        if (readFile.is_open())
        {
            int i = 0;
            while (readFile >> element) {
                vect.push_back(element);
            }
        }
        readFile.close();

        for (int i = 0; i < vect.size(); i++)
        {
            Person newPerson;
            string delimiter = ",";
            size_t pos = 0;
            string token;
            int number;
            string str = vect.at(i);
            for (int j = 0; j < 3; j++)
            {
                pos = str.find(delimiter);
                token = str.substr(0, pos);
                str.erase(0, pos + delimiter.length());
                //cout << j << " : " << token << endl;
                switch(j)
                {
                    case 0:
                        newPerson.setLname(token);
                        break;
                    case 1:
                        newPerson.setFname(token);
                        break;
                    case 2:
                        newPerson.setMnumber(token);
                        break;
                }
            }
            cout << newPerson.getLname() << ","<< newPerson.getFname() <<","<< newPerson.getMnumber() << endl;
            x = insert(newPerson, x);
        }
    }

    node* find(node* root, string name)
    {
        if(root == NULL)
        {
            return NULL;
        }
        else if(name < (root->data.getLname() + root->data.getFname()))
        {
            return find(root->left, name);
        }
        else if(name > (root->data.getLname()+ root->data.getFname()))
        {
            return find(root->right, name);
        }
        else
        {
            return root;
        }
    }

    bool checkForValue(node* root, string name)
    {
        while (root != NULL)
        {
            if (name > (root->data.getLname() + root->data.getFname()))
            {
                root = root->right;
            }
            else if (name < (root->data.getLname() + root->data.getFname()))
            {
                root = root->left;
            }
            else
            {
                return true;
            }
        }
        return false;
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

    void remove()
    {
        string fname, lname;
        cout<<"Enter first and last name to remove: ";
        cin>>fname>>lname;
        string person = lname + fname;
        if (isInTree(person))
        {
            x = remove(x, person);
            cout<<"User Deleted."<<endl;
        }
        else
        {
            cout<<"User Does Not Exist."<<endl;
        }
    }

    void display()
    {
        inorder(x);
        cout << endl;
    }

    void writeContacts()
    {
        string file;
        cout<<"Enter the name of the text file to write to: ";
        cin>>file;
        writeContacts(x, file);
        cout<<endl;
    }

    void restore()
    {
        string file;
        cout<<"Enter the name of the text file to read from: " << endl;
        cout<<"Contact info must be space/enter separated and " << endl;
        cout<<"Ex: firstname,lastname,mobile,"<< endl;
        cout<<"    firstname,lastname,mobile,"<< endl;
        cin>>file;
        restore(x, file);
        cout<<endl;
    }

    void search()
    {
        string fname, lname;
        cout<<"Enter first and last name to search: ";
        cin>>fname>>lname;
        string person = lname + fname;
        if (isInTree(person))
        {
            node* tmpPerson = find(x, person);
            cout<<"User: "<<tmpPerson->data.getLname()<<", "<<tmpPerson->data.getFname()<<"     "<<tmpPerson->data.getMnumber()<<endl;
        }
        else
        {
            cout<<"User Does Not Exist."<<endl;
        }
    }

    void edit()
    {
        string fname, lname, mnumber;
        cout<<"Enter first and last name to edit: ";
        cin>>fname>>lname;
        string person = lname + fname;
        if (isInTree(person))
        {
            node* tmp = find(x, person);
            cout<<"Enter the new number: ";
            cin>>mnumber;
            tmp->data.setMnumber(mnumber);
        }
        else
        {
            cout<<"User Does Not Exist."<<endl;
        }
    }

    bool isInTree(string name)
    {
        return checkForValue(x, name);
    }

};

Person addContact() // adds contact to myContacts (Constructor)
{
    string fname, lname, mnumber;
    cout<<"Enter the first name, last name, and mobile of the contact you would like to add:" << endl;
    cout<<"Ex:'firstname lastname mobile'"<< endl;
    cin>>fname>>lname>>mnumber;
    Person newPerson;
    newPerson.setFname(fname);
    newPerson.setLname(lname);
    newPerson.setMnumber(mnumber);
    return newPerson;
}

class UserInterface
{
  Book bstBook;

public:
  void menu()
  {
      int choice;
      int exit = 0;
      Person tmpPerson;

      do
      {
          cout<<endl;
          cout<<"-------------------"<<endl;
          cout<<"USER MENU"<<endl;
          cout<<"-------------------"<<endl;
          cout<<"1. Add User"<<endl;
          cout<<"2. Delete User"<<endl;
          cout<<"3. Find User"<<endl;
          cout<<"4. Edit User"<<endl;
          cout<<"5. Display All Users"<<endl;
          cout<<"6. Save to Text File"<<endl;
          cout<<"7. Restore from Text File"<<endl;
          cout<<"8. Quit"<<endl<<endl;

          cin>>choice;

          if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8)
          {
              cout<<"Not a valid choice."<<endl;
              exit = 0;
          }
          else
          {
              switch(choice)
              {
                  case 1:
                      tmpPerson = addContact();
                      bstBook.insert(tmpPerson);
                      cout<<"User Added!"<<endl;
                      break;
                  case 2:
                      bstBook.remove();
                      break;
                  case 3:
                      bstBook.search();
                      break;
                  case 4:
                      bstBook.edit();
                      break;
                  case 5:
                      cout<<"Last Name"<<"     "<<"First Name"<<"   "<<"Number"<<endl;
                      cout<<"---------------------------------------------------------"<<endl;
                      bstBook.display();
                      break;
                  case 6:
                      bstBook.writeContacts();
                      break;
                  case 7:
                      bstBook.restore();
                      break;
                  case 8:
                      exit = 1;
                      break;
              }
          }
      }while (exit == 0);

  }
};


int main()
{
    UserInterface ui;
    ui.menu();
}
