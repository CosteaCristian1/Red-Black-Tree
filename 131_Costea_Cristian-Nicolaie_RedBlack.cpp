#include <bits/stdc++.h>
using namespace std;

struct nod
{
    int id;
    char culoare;
    nod *parinte;
    nod *st;
    nod *dr;
};
class RBtree
{
private:
    nod *root;
    nod *q;
public :
    RBtree()
    {
        q=NULL;
        root=NULL;
    }
    void insert();
    void insertfix(nod *);
    void leftrotate(nod *);
    void rightrotate(nod *);
    void del();
    nod* succesor(nod *);
    void delfix(nod *);
    void search();
};
void RBtree::insert()
{
    int z,i=0;
    cout<<"\nIntrodu numar nod: ";
    cin>>z;
    nod *p,*q;
    nod *t=new nod;
    t->id=z;
    t->st=NULL;
    t->dr=NULL;
    t->culoare='r';
    p=root;
    q=NULL;
    if(root==NULL)
    {
        root=t;
        t->parinte=NULL;
    }
    else
    {
        while(p!=NULL)
        {
            q=p;
            if(p->id<t->id)
                p=p->dr;
            else
                p=p->st;
        }
        t->parinte=q;
        if(q->id<t->id)
            q->dr=t;
        else
            q->st=t;
    }
    insertfix(t);
}
void RBtree::insertfix(nod *t)
{
    nod *u;
    if(root==t)
    {
        t->culoare='b';
        return;
    }
    while(t->parinte!=NULL&&t->parinte->culoare=='r')
    {
        nod *g=t->parinte->parinte;
        if(g->st==t->parinte)
        {
            if(g->dr!=NULL)
            {
                u=g->dr;
                if(u->culoare=='r')
                {
                    t->parinte->culoare='b';
                    u->culoare='b';
                    g->culoare='r';
                    t=g;
                }
            }
            else
            {
                if(t->parinte->dr==t)
                {
                    t=t->parinte;
                    leftrotate(t);
                }
                t->parinte->culoare='b';
                g->culoare='r';
                rightrotate(g);
            }
        }
        else
        {
            if(g->st!=NULL)
            {
                u=g->st;
                if(u->culoare=='r')
                {
                    t->parinte->culoare='b';
                    u->culoare='b';
                    g->culoare='r';
                    t=g;
                }
            }
            else
            {
                if(t->parinte->st==t)
                {
                    t=t->parinte;
                    rightrotate(t);
                }
                t->parinte->culoare='b';
                g->culoare='r';
                leftrotate(g);
            }
        }
        root->culoare='b';
    }
}

void RBtree::del()
{
    if(root==NULL)
    {
        return ;
    }
    int x;
    cout<<"\nIntrodu nr nod de sters: ";
    cin>>x;
    nod *p;
    p=root;
    nod *y=NULL;
    nod *q=NULL;
    int found=0;
    while(p!=NULL&&found==0)
    {
        if(p->id==x)
            found=1;
        if(found==0)
        {
            if(p->id<x)
                p=p->dr;
            else
                p=p->st;
        }
    }
    if(found==0)
    {
        cout<<"\nElementul nu a fost gasit.";
        return ;
    }
    else
    {
        cout<<"\nElement sters: "<<p->id;
        if(p->st==NULL||p->dr==NULL)
            y=p;
        else
            y=succesor(p);
        if(y->st!=NULL)
            q=y->st;
        else
        {
            if(y->dr!=NULL)
                q=y->dr;
            else
                q=NULL;
        }
        if(q!=NULL)
            q->parinte=y->parinte;
        if(y->parinte==NULL)
            root=q;
        else
        {
            if(y==y->parinte->st)
                y->parinte->st=q;
            else
                y->parinte->dr=q;
        }
        if(y!=p)
        {
            p->culoare=y->culoare;
            p->id=y->id;
        }
        if(y->culoare=='b')
            delfix(q);
    }
}

void RBtree::delfix(nod *p)
{
    nod *s;
    while(p!=root&&p->culoare=='b')
    {
        if(p->parinte->st==p)
        {
            s=p->parinte->dr;
            if(s->culoare=='r')
            {
                s->culoare='b';
                p->parinte->culoare='r';
                leftrotate(p->parinte);
                s=p->parinte->dr;
            }
            if(s->dr->culoare=='b'&&s->st->culoare=='b')
            {
                s->culoare='r';
                p=p->parinte;
            }
            else
            {
                if(s->dr->culoare=='b')
                {
                    s->st->culoare=='b';
                    s->culoare='r';
                    rightrotate(s);
                    s=p->parinte->dr;
                }
                s->culoare=p->parinte->culoare;
                p->parinte->culoare='b';
                s->dr->culoare='b';
                leftrotate(p->parinte);
                p=root;
            }
        }
        else
        {
            s=p->parinte->st;
            if(s->culoare=='r')
            {
                s->culoare='b';
                p->parinte->culoare='r';
                rightrotate(p->parinte);
                s=p->parinte->st;
            }
            if(s->st->culoare=='b'&&s->dr->culoare=='b')
            {
                s->culoare='r';
                p=p->parinte;
            }
            else
            {
                if(s->st->culoare=='b')
                {
                    s->dr->culoare='b';
                    s->culoare='r';
                    leftrotate(s);
                    s=p->parinte->st;
                }
                s->culoare=p->parinte->culoare;
                p->parinte->culoare='b';
                s->st->culoare='b';
                rightrotate(p->parinte);
                p=root;
            }
        }
        p->culoare='b';
        root->culoare='b';
    }
}

void RBtree::leftrotate(nod *p)
{
    if(p->dr==NULL)
        return ;
    else
    {
        nod *y=p->dr;
        if(y->st!=NULL)
        {
            p->dr=y->st;
            y->st->parinte=p;
        }
        else
            p->dr=NULL;
        if(p->parinte!=NULL)
            y->parinte=p->parinte;
        if(p->parinte==NULL)
            root=y;
        else
        {
            if(p==p->parinte->st)
                p->parinte->st=y;
            else
                p->parinte->dr=y;
        }
        y->st=p;
        p->parinte=y;
    }
}
void RBtree::rightrotate(nod *p)
{
    if(p->st==NULL)
        return ;
    else
    {
        nod *y=p->st;
        if(y->dr!=NULL)
        {
            p->st=y->dr;
            y->dr->parinte=p;
        }
        else
            p->st=NULL;
        if(p->parinte!=NULL)
            y->parinte=p->parinte;
        if(p->parinte==NULL)
            root=y;
        else
        {
            if(p==p->parinte->st)
                p->parinte->st=y;
            else
                p->parinte->dr=y;
        }
        y->dr=p;
        p->parinte=y;
    }
}

nod* RBtree::succesor(nod *p)
{
    nod *y=NULL;
    if(p->st!=NULL)
    {
        y=p->st;
        while(y->dr!=NULL)
            y=y->dr;
    }
    else
    {
        y=p->dr;
        while(y->st!=NULL)
            y=y->st;
    }
    return y;
}

void RBtree::search()
{
    if(root==NULL)
    {
        cout<<"\nArborele nu are elemente\n" ;
        return  ;
    }
    int x;
    cout<<"\n Numarul elementului cautat: ";
    cin>>x;
    nod *p=root;
    int found=0;
    while(p!=NULL&& found==0)
    {
        if(p->id==x)
            found=1;
        if(found==0)
        {
            if(p->id<x)
                p=p->dr;
            else
                p=p->st;
        }
    }
    if(found==0)
        cout<<"\nElementul nu exista.";
    else
    {
        cout<<"\n Numar: "<<p->id;
        cout<<"\n Culoare: ";
        if(p->culoare=='b')
            cout<<"Negru";
        else
            cout<<"Rosu";
        if(p->parinte!=NULL)
            cout<<"\n Parinte: "<<p->parinte->id;
        else
            cout<<"\n Nodul nu are parinte.  ";
        if(p->dr!=NULL)
            cout<<"\n Descendent drept: "<<p->dr->id;
        else
            cout<<"\n Nodul nu are un descendent drept.  ";
        if(p->st!=NULL)
            cout<<"\n Descendent stang: "<<p->st->id;
        else
            cout<<"\n Nodul nu are un descendent stang.  ";
        cout<<endl;

    }
}
int main()
{
    int ch,OK=1;
    RBtree obj;
    cout<<"\n Red Black Tree \n";
    cout<<"\n 1. Insereaza nod ";
    cout<<"\n 2. Sterge nod";
    cout<<"\n 3. Cauta nod";
    cout<<"\n 4. Exit " ;
    cout<<"\n";
    cin>>ch;
    while(OK==1)
    {
         if(ch==1) {
             obj.insert();
             cout << "\nNod inserat.\n";
         }
         else if(ch==2) {
             obj.del();
         }
         else if(ch==3) {
             obj.search();
         }
         else if(ch==4) {
             break;
         }
        cout<<"\n\n";
        cout<<"\n 1. Insereaza nod ";
        cout<<"\n 2. Sterge nod";
        cout<<"\n 3. Cauta nod";
        cout<<"\n 4. Exit " ;
        cout<<"\n";
         cin>>ch;

    }
    return 0;
}

