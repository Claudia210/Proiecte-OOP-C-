#include <iostream>

using namespace std;

class nod {
protected:
    int info;
public:
    nod();

    explicit nod(int i);

    nod(const nod &n);

    virtual ~nod();

    virtual nod *get_next() = 0;

    virtual void set_next(nod *) = 0;

    virtual nod *get_ante() = 0;

    virtual void set_ante(nod *) = 0;

    int get_info() {
        return info;
    }

    void set_info(int i) {
        info = i;
    }

    nod &operator=(const nod &n);

    friend istream &operator>>(istream &in, nod &n);

    friend ostream &operator<<(ostream &out, const nod &n);

    virtual void citire(istream &in);

    virtual void afisare(ostream &out) const;
};

nod::nod() {
    info = 0;
};

nod::nod(int i) {
    info = i;
};

nod::nod(const nod &n) {
    info = n.info;
};

nod::~nod() {
    info = 0;
}

nod& nod::operator=(const nod &n)
{
    if(this == &n)
        return *this;

    info = n.info;
    return *this;
}

istream &operator>>(istream &in, nod &n) {
    n.citire(in);
    return in;
};

ostream &operator<<(ostream &out, const nod &n) {
    n.afisare(out);
    return out;
};

void nod::citire(istream &in) {
    in >> info;
};

void nod::afisare(ostream &out) const {
    out << info << " ";
};

class nod_simplu : public nod {
protected:
    nod *next;
    nod *get_ante()  {
        return NULL;
    }
    void set_ante(nod *)  {
        ;
    }
public:
    nod_simplu();

    nod_simplu(int i, nod *urm);

    nod* get_next()  ;
    virtual ~nod_simplu() ;

    void set_next(nod *urm) ;
};

nod_simplu::nod_simplu() : nod() {
    next = NULL;
};

nod_simplu::nod_simplu(int i, nod *urm) : nod(i) {
    next = urm;
};

nod_simplu::~nod_simplu() {
    delete next;
}

nod *nod_simplu::get_next() {
    return next;
}

void nod_simplu::set_next(nod *urm) {
    next = urm;
}

class nod_dublu : public nod_simplu {
protected:
    nod *ante;
public:
    nod_dublu();

    nod_dublu(int i, nod *urm, nod *an);

    virtual ~nod_dublu();

    nod *get_ante()  ;

    void set_ante(nod *an)  ;
};

nod_dublu::nod_dublu() : nod_simplu() {
    ante = NULL;
};

nod_dublu::nod_dublu(int i, nod *urm, nod *an) : nod_simplu(i, urm) {
    ante = an;
};

nod* nod_dublu::get_ante() {
    return ante;
}

void nod_dublu::set_ante(nod *an) {
    ante = an;
}

nod_dublu::~nod_dublu() {
    delete ante;
}

class nod_prioritate : public nod_dublu {
protected:
    int prio;
public:
    int get_prio() {
        return prio;
    }

    void set_prio(int pr) {
        prio = pr;
    }

    nod_prioritate();

    nod_prioritate(int i, nod *n, nod *an, int pr);

    virtual ~nod_prioritate();

    void citire(istream &in)  ;

    void afisare(ostream &out) const ;

};

nod_prioritate::nod_prioritate() : nod_dublu() {
    prio = 0;
};

nod_prioritate::nod_prioritate(int i, nod *n, nod *an, int pr) : nod_dublu(i, n, an) {
    prio = pr;
};

nod_prioritate::~nod_prioritate() {}


void nod_prioritate::citire(istream &in) {
    nod::citire(in);
    in >> prio;
}

void nod_prioritate::afisare(ostream &out) const{
    nod::afisare(out);
    out << prio << " ";
};


class coada_prioritati //(elemente de tip Nod_Prioritate);
{
protected:
    nod_prioritate *start;
    int scoateElement(nod **p){
        if((*p) != NULL) {
            nod * deSters = (*p);
            int val = (*p)->get_info();
            (*p) = (*p)->get_next();
            delete deSters;
            return val;
        }
    }

    nod_prioritate * adaugareSfarsit(nod_prioritate * p,int x, int y){
        nod_prioritate * elem = new nod_prioritate;
        elem->set_prio(x);
        elem->set_info(y);
        elem->set_next(NULL);
        if(p == NULL){
            p = elem;
            return p;
        }
        else {
            nod * parcurg = p;
            while(parcurg->get_next()){
                parcurg = parcurg->get_next();
            }
            parcurg->set_next(elem);
            return p;
        }
    }

    nod_prioritate * adaugareInceput(nod_prioritate * p,int x, int y){
        nod_prioritate * elem = new nod_prioritate;
        elem->set_prio(x);
        elem->set_info(y);
        elem->set_next(p);
        p = elem;
        return p;
    }
    nod_prioritate * adaugareInOrdine(nod_prioritate * p,int x, int y){
        nod_prioritate * elem = new nod_prioritate;
        elem->set_prio(x);
        elem->set_info(y);
        if(p == NULL){
            elem->set_next(NULL);
            p = elem;
            return p;
        }
        else{
            if(p->get_prio() > x){
                p = adaugareInceput(p,x,y);
                return p;
            }
            int breaku = 0;
            nod_prioritate * parcurg = p;
            while(parcurg->get_next()){
                if(parcurg->get_next()->get_info() > x){
                    elem->set_next(parcurg->get_next());
                    parcurg->set_next(elem);
                    breaku = 1;
                    break;
                }
                parcurg = dynamic_cast<nod_prioritate *>(parcurg->get_next());
            }
            if(parcurg->get_prio() > x){
                elem->set_next(parcurg);
                parcurg->set_next(elem);
                return p;
            }
            if(breaku == 0)
                p=adaugareSfarsit(p,x,y);
            return p;
        }
    }

public:
    coada_prioritati();

    coada_prioritati(nod_prioritate *s);

    virtual ~coada_prioritati();

    void adaugare_coada_pr();

    virtual void stergere();

    virtual void afisare(ostream&) const;

    friend ostream& operator<<(ostream&, const coada_prioritati&);
};

coada_prioritati::coada_prioritati() {
    start = NULL;
};

coada_prioritati::coada_prioritati(nod_prioritate *s) {
    start = s;
};

coada_prioritati::~coada_prioritati() {
    while(start)
        stergere();
}

void coada_prioritati::adaugare_coada_pr() {
    int n, i;
    cout << "Nr.elemente pe care urmeaza sa le adaug in coada cu prioritati:";
    cin >> n;
    for (i = 1; i <= n; i++) {
        int aux, tmp;
        cout << "prioritate = ";
        cin >> aux;
        cout << "valoare = ";
        cin >> tmp;
        start = adaugareInOrdine(start, aux, tmp);
    }
}

void coada_prioritati::stergere() {
    scoateElement(reinterpret_cast<nod **>(&start));
}

void coada_prioritati::afisare(ostream& out) const {
    nod *p;

    p = start;
    while (p != NULL) {
        out << p->get_info() << " ";
        p = p->get_next();
    }
}

ostream& operator<<(ostream& out, const coada_prioritati& obj) {
    obj.afisare(out);
    return out;
}


class coada_simpla : public coada_prioritati {
public:
    coada_simpla();

    coada_simpla(nod_prioritate *s);

    virtual ~coada_simpla();

    void adaugare(int x);
    void stergere();
    void afisare(ostream&) const ;
    void insertionsort();
};

coada_simpla::coada_simpla()
        : coada_prioritati() {};

coada_simpla::coada_simpla(nod_prioritate *s) : coada_prioritati(s) {};

coada_simpla::~coada_simpla() {

}

void coada_simpla::adaugare(int x) {

start = adaugareSfarsit(start, 1, x);
}

void coada_simpla::stergere() {
    coada_prioritati::stergere();
}

void coada_simpla::afisare(ostream &out) const {
    coada_prioritati::afisare(out);
}
void coada_simpla::insertionsort()
{
    nod_prioritate *i,*j,*aux;
    int x,y;
    i=start;
    aux=i;
    while(i!=NULL)
    {
        aux->set_next(aux);
        j=aux;

        while(j!=NULL)
        {
            if(i->get_info()>=j->get_info())
               {
                x=i->get_info();
                y=j->get_info();
                swap(x,y);
               }
                j->set_next(j);
        }
        i->set_next(i);
}}
int main()
    {int op,x,n,i;
    coada_prioritati *c;
    c=new coada_prioritati();
    coada_simpla *c1;
    c1=new coada_simpla();
    cout<<"1.Coada cu prioritati adaugare si sortare elemente!"<<endl;
    cout<<"2.Sterge element din coada cu prioritati!"<<endl;
    cout<<"3.Afiseaza elementele sortate din coada cu prioritati!"<<endl;
    cout<<"4.Adaugare elemnt in coada simpla!"<<endl;
    cout<<"5.Stergere element din coada simpla!"<<endl;
    cout<<"6.Afiseaza coada simpla!"<<endl;
    //cout<<"7.Insertionsort!"<<endl;

do{
cout<<"Optiune:";
    cin>>op;
        switch(op)
    {
            case 1:{c->adaugare_coada_pr();break;}
            case 2:{c->stergere();break;}
            case 3:{cout<<c<<endl;break;}
            case 4:{cout<<"Nr. elemente:";cin>>n;
            for(i=0;i<n;i++){cout<<"Elementul ce urmeaza sa fie adaugat in coada:";cin>>x;c1->adaugare(x);};break;}
            case 5:{c1->stergere();break;}
            case 6:{cout<<c1;break;}
            //case 7:{c1->insertionsort();cout<<c1;break;}

        }
}while(op!=8);
 return 0;
}
