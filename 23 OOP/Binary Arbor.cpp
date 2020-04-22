#include<iostream>
#include<bits/stdc++.h>
#include<cstddef>
#include<iomanip>
using namespace std;
#define width_unit 5

class Tree
{
    private:
        class Node
        {
            public:
                int data;
                Node *left, *right;
                Node(int d=0) //constructor
:data(d), left(NULL), right(NULL) {}
        };

        Node *root;
        Node * trav(int, Node * &);
        void chop(Node * N);
        void copy(Node * N);
        void print(ostream &, Node *, int) const;
        void print(Node *, int) const;

    public:
        Tree(void); //constructor
        ~Tree(void); //destructor
        bool find(int);
        void insert(int);
        void remove(int);
        bool empty(void) const;
        Tree(const Tree &); //copy constructor
        const Tree & operator=(const Tree &); //
        friend ostream & operator<<(ostream &, const Tree &);
};


Tree::Tree(void)
{
     root=NULL;
}

bool Tree::empty(void) const
{
     return !root;
}

Tree::Node * Tree::trav(int foo, Node * & par)
{
     Node * curr=root;
     par=NULL;
     while(curr && curr->data != foo)
     {
         par=curr;
         if(foo < curr->data)
             curr=curr->left;
         else
             curr=curr->right;
     }
     return curr;
}

bool Tree::find(int foo)
{
     Node * par=NULL;
     Node * curr=trav(foo, par);
     return curr;
}

void Tree::insert(int foo)
{
     Node * par=NULL;
     Node * curr=trav(foo,par);
     if(!curr)
     {
         curr= new Node(foo);
         if(!par)
             root=curr;
         else if(foo < par->data)
             par->left=curr;
         else
             par->right=curr;
     }
}

void Tree::remove(const int foo)
{
     Node * par=NULL;
     Node * curr=trav(foo,par);
     if(curr)
     {
         if(curr->left && curr->right)
         {
             Node * tmp=curr;
             par=curr;
             curr=curr->left;
             while(curr->right)
             {
                 par=curr;
                 curr=curr->right;
             }
             tmp->data=curr->data;
         }


         Node *tmp=(curr->left ? curr->left : curr->right);

         if(!par)
             root=tmp;
         else if(par->data < curr->data)
                  par->right=tmp;
              else
                  par->left=tmp;
         delete curr;
     }
}

void Tree::chop(Node *N)
{
     if(N)
     {
         chop(N->left);
         chop(N->right);
         delete N;
     }
}

//destructor
Tree::~Tree(void)
{
     chop(root);
}

Tree::Tree(const Tree & T)
{
     root=NULL;
     copy(T.root);
}

void Tree::copy(Node * N)
{
     if(N)
     {
         insert(N->data);
         copy(N->left);
         copy(N->right);
     }
}

const Tree & Tree::operator=(const Tree & T)
{
     if(this != &T)
     {
          chop(root);
          root=NULL;
          copy(T.root);
     }
     return *this;
}

void Tree::print(ostream & ost, Node * curr, int level) const
{
     if(curr)
     {
         print(ost,curr->right,level+1);

         ost<<setw(level*width_unit)<<curr->data<<endl;
         print(ost,curr->left,level+1);
     }
}


void Tree::print(Node * curr, int level) const
{
     if(curr) // Daca nodul curent e null
     {
         print(curr->right,level+1); //Incercam  sa mergem la nodul drept

         cout<<setw(level*width_unit)<<curr->data<<endl;
         print(curr->left,level+1); //Incercam sa mergem la nodul stang
     }
}

ostream & operator<<(ostream &print, const Tree &t)
{
     t.print(print, t.root, 1);
     return print;
}


int main()
{
    Tree mytree;

    mytree.insert(5);
    mytree.insert(3);
    mytree.insert(2);
    mytree.insert(7);
    mytree.insert(0);
    mytree.insert(2);
    cout<<mytree<<endl<<endl;
    mytree.remove(0);
    cout<<mytree<<endl<<endl;
    mytree.remove(5);
    cout<<mytree<<endl<<endl;
    mytree.insert(9);
    mytree.insert(10);
    mytree.insert(4);
    cout<<mytree<<endl<<endl;
    mytree.remove(9);
    cout<<mytree<<endl<<endl;

    Tree mytree2=mytree; //Copy construcotr
    cout<<mytree2<<endl<<endl;

    Tree mytree3;
    mytree3=mytree2; //overload copy constructor
    cout<<mytree3<<endl<<endl;

return 0;
}
