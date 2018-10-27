#include <iostream>
using namespace std;
//clasa 1:
class nod
{

    char info;
    nod* next;
public:
    //functiile de get si set:
    char get_info();
    nod* get_next();
    void set_info(char);
    void set_next(nod*);
    //constructor de initializare si constructor parametrizat:
    nod();
    nod(char,nod*);
//destructor:
    ~nod();
    friend class coada_de_caractere;
};
//functiile de get si set pentru elemntele din clasa nod:
char nod::get_info()
{
    return info;
}
nod *nod::get_next()
{
    return next;
}
void nod::set_info(char i)
{
    info=i;
}
void nod::set_next(nod *n)
{
    next=n;
}
//constructorul de initializare fara parametrii:
nod::nod()
{
    info=0;
    next=NULL;
};
//constructorul de initializare cu parametrii:
nod::nod(char i,nod *n=NULL)
{
    info=i;
    next=n;
};
//destructorul:
nod::~nod()
{
    next=NULL;
};
//clasa 2:
class coada_de_caractere
{
//elementele clasei:
    nod*prim;
    nod*ultim;
public:
    //get:
    nod *get_prim();
    nod *get_ultim();
    //set:
    void set_prim(nod*pr);
    void set_ultim(nod*u);
    //functiile pentru adaugarea unui nod, stergerea unui nod si verificarea cozii:
    void push(char x);
    void pop();
    void isempty();
    void afisare();
    //supraincarcarea functiilor:
    friend ostream & operator <<(ostream &A, coada_de_caractere& c);
    friend istream & operator >>(istream &, coada_de_caractere& c);
    friend coada_de_caractere &operator +(coada_de_caractere &c1,coada_de_caractere &c2);
    friend coada_de_caractere &operator -(coada_de_caractere &c1, coada_de_caractere &c2);
    //constructor:
    coada_de_caractere();
    //destructor:
    ~coada_de_caractere();
};
//functiile de get si set:
nod* coada_de_caractere::get_prim()
{
    return prim;
};
nod* coada_de_caractere::get_ultim()
{
    return ultim;
};
void coada_de_caractere::set_prim(nod*pr)
{
    prim=pr;
};
void coada_de_caractere:: set_ultim(nod*u)
{
    ultim=u;
};
//constructorul pentru coada:
coada_de_caractere::coada_de_caractere()
{
    prim=NULL;
    ultim=NULL;
};
//destructor:
coada_de_caractere::~coada_de_caractere()
{
    while(prim)
        pop();
}
//functiile:
//Adaugarea unui elemnet in coada:
void coada_de_caractere::push(char x)
{
    nod*r;

    if(!prim)
    {
        prim=new nod;
        prim->info=x;
        prim->next=NULL;
        ultim=prim;
    }
    else
    {
        r=new nod;
        ultim->next=r;
        r->info=x;
        ultim=r;
        ultim->next=NULL;
    }
}
//Eliminare nod:
void coada_de_caractere::pop()
{
    nod *r;
    if(prim)
    {
        r=prim;
        prim=prim->next;
        delete r;
    }
}
//Verificare coada vida:
void coada_de_caractere::isempty()
{
    if(prim==NULL)
        cout<<"este vida!";
    else
        cout<<"nu este vida!";
}
//Afisare coada:
void coada_de_caractere::afisare()
{
    nod *curent;
    curent=prim;
    while(curent!=NULL)
    {
        cout<<curent->info<<" ";
        curent=curent->next;
    }
}
//Functiile supraincarcate:
//Supraincarcarea operatorului << prin afisatea si golirea cozii:
ostream &operator << (ostream &A, coada_de_caractere &c)
{
    nod *p;
    p=c.prim;
    while(p!=NULL)
    {
        A<<p->get_info()<<" ";//afisez p
        c.pop();//sterg p
        p=c.prim;//actualizez p
    }
    return A;
}
//Supraincarcatrea operatorului >> prin push uri succesive:
istream &operator >>(istream &A, coada_de_caractere &c)
{
    char x;//caracterul ce urmeaza sa fie adaugat
    int n,i;//numarul de elemete pe care vreau sa le adaug
    cout<<"Numarul de elemente pe care doresc sa-l adaug in coada:";
    A>>n;
    for(i=0; i<n; i++)
    {
        cout<<"Elementul pe care doresc sa-l adaug in coada este:";
        A>>x;
        c.push(x);
    }
    return A;
}
//Supraincarcarea operatorului + prin concatenarea a doua cozi
coada_de_caractere & operator+(coada_de_caractere &c1, coada_de_caractere &c2)
{
    coada_de_caractere *c3 = new coada_de_caractere;
    nod *p,*r;
    p=c1.prim;
    r=c2.prim;
    //Adaug toate elementele din coada c1 in c3
    while(p)
    {
        c3->push(p->get_info());
        p=p->get_next();
    }
    //Adaug toate elementele din coada c2 in c3
    while(r)
    {
        c3->push(r->get_info());
        r=r->get_next();
    }

    return *c3;
}
//Supraincacarea operatorului - prin eliminarea concomitenta a elementelor din coua cozi si adaugarea elementului cu codul ASCII mai mare inntr-o alta coada
coada_de_caractere & operator - (coada_de_caractere &c1, coada_de_caractere &c2)
{
    coada_de_caractere *c3 = new coada_de_caractere;
    nod*p,*r;
    p=c1.prim;
    r=c2.prim;
    while(p!=NULL && r!=NULL)
    {
        if(p->get_info()<=r->get_info())//Verific care element are codul ASCII mai mare
            c3->push(r->get_info());
        else
            c3->push(p->get_info());
        //Sterg elementele din ambele cozi
        c1.pop();
        c2.pop();

        //Actualizez valorile lui p si r dupa stergere
        p = c1.prim;
        r = c2.prim;
    }
    //Verific daca au mai ramas elemente in cozi si le sterg
    if(p==NULL)
        while(r!=NULL)
        {
            r=c2.prim, c2.pop();
        }
    if(r==NULL)
        while(p!=NULL)
        {
            p=c1.prim, c1.pop();
        }
    return *c3;
}
//functie prin care se realizeaza citirea informațiilor complete a n obiecte, memorarea și afisarea acestora
void n_obiecte()
{
    int n,i;
    cout<<"Numarul de cozi:";
    cin>>n;
    coada_de_caractere *v = new coada_de_caractere[n];//creez un vector de cozi
    for(i=0; i<n; i++)
    {
        cin>>v[i];//creez coada
        cout<<v[i];//afisez coada
        cout<<endl;
    }
}
int main()
{
    coada_de_caractere *c1 = new coada_de_caractere;
    coada_de_caractere *c2 = new coada_de_caractere;
    coada_de_caractere *c3 = new coada_de_caractere;
    coada_de_caractere *c4 = new coada_de_caractere;
    char x;
    int opt;
    cout<<endl;
    cout<<" 1. Adaugarea unui elemnet in coada c1 si in coada c2 (push)!"<<endl;
    cout<<" 2. Stergerea unui element din coada c1 (pop)!"<<endl;
    cout<<" 3. Verificare coada vida (isempty)!"<<endl;
    cout<<" 4. Adaugarea a n elemente in coada c1(supraincarcarea operatorului>>)!"<<endl;
    cout<<" 5. Adaugarea a n elemente in coada c2 (supraincarcarea operatorului>>)!"<<endl;
    cout<<" 6. Concatenarea a doua cozi (c1+c2)(supraincarcarea operatorului +)!"<<endl;
    cout<<" 7. C1-C2. Eliminarea concomitenta de elemente din coazile c1 si c2 adaugand caracterul ce are codul ASCII mai mare în coada c4 (supraincarcarea operatorului -)!"<<endl;
    cout<<" 8. Golirea si afisarea cozilor!(supraincarcarea operatorului <<)"<<endl;
    cout<<" 9. Citirea memorarea si afisarea a n obiecte din clasa coada_de_caractere!"<<endl;
    cout<<" 10.Terminare program!"<<endl;
    cout<<endl;
    do
    {
        cout<<"Dati optiunea: ";
        cin>>opt;
        switch (opt)
        {
        case 1:
        {
            cout<<"Elementul pe care doresc sa-l adaug in coada c1 este:";
            cin>>x;
            c1->push(x);
            cout<<"C1:";
            c1->afisare();
            cout<<endl<<"Elementul pe care doresc sa-l adaug in coada c2 este:";
            cin>>x;
            c2->push(x);
            cout<<"C2:";
            c2->afisare();
            cout<<endl;
            break;
        };

        case 2:
        {
            c1->pop();
            cout<<"Coada c1:";
            c1->afisare();
            cout<<endl;
            break;
        }

        case 3:
        {
            cout<<"C1 ";
            c1->isempty();
            cout<<endl<<"C2 ";
            c2->isempty();
            cout<<endl<<"C3 ";
            c3->isempty();
            cout<<endl<<"C4 ";
            c4->isempty();
            cout<<endl;
            break;
        }

        case 4:
        {
            cin>>*c1;
            cout<<"C1:";
            c1->afisare();
            cout<<endl;
            break;
        }
        case 5:
        {
            cin>>*c2;
            cout<<"C2:";
            c2->afisare();
            cout<<endl;
            break;
        }

        case 6:
        {
            delete c3;
            (*c3) = (*c1) + (*c2);
            cout<<"C3:";
            c3->afisare();
            cout <<endl;
            break;
        }
        case 7:
        {
            delete c4;
            (*c4) = (*c1)-(*c2);
            cout<<"C4:";
            c4->afisare();
            cout<<endl<<"C1:";
            c1->afisare();
            cout<<endl<<"C2:";
            c2->afisare();
            cout<<endl;
            break;
        }
        case 8:
        {
            cout<<"C1:";
            cout<<*c1;
            cout<<endl<<"C2:";
            cout<<*c2;
            cout<<endl<<"C3:";
            cout<<*c3;
            cout<<endl<<"C4:";
            cout<<*c4;
            cout<<endl;
            break;
        }
        case 9:
        {
            n_obiecte();
        }
        case 10:
        {
            break;
        }
        default :
        {
            cout << "Optiune invalida"<<endl;
            break;
        }
        }
    }
    while(opt!=10);

    return 0;
}
