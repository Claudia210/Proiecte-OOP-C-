#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class personal
{
protected:
    string nume;
    string prenume;
    string cnp;
    double salariu;
    int procent_incasari;
public:
    personal();
    personal(string n, string p, string c, double s,int pr);
    friend ostream & operator <<(ostream &out,const personal  &p);
    friend ifstream & operator >>(ifstream &in, personal &p);
    personal  operator =(personal p);
    virtual void salariu_personal(int incasari)
    {
        salariu=(incasari*procent_incasari)/100;
    };
};
personal::personal()
{
    nume=" ";
    prenume=" ";
    cnp=" ";
    salariu=0;
    procent_incasari=0;
}
personal::personal(string n, string p, string c, double s, int pr)
{
    nume=n;
    prenume=p;
    salariu=s;
    cnp=c;
    procent_incasari=pr;
}
personal personal:: operator =(personal p)
{
    nume=p.nume;
    prenume=p.prenume;
    salariu=p.salariu;
    cnp=p.cnp;
    procent_incasari=p.procent_incasari;
    return *this;
}
ifstream &operator >>(ifstream &in,personal &p)
{
    in>>p.nume;
    in>>p.prenume;
    in>>p.cnp;
    in>>p.procent_incasari;
    return in;
}
ostream &operator <<(ostream &out,const personal &p)
{
    try
    {
        out<<"Nume:"<<p.nume<<endl;
        out<<"Prenume:"<<p.prenume<<endl;
        if(p.cnp.size()!=13)
            throw 0;
        out<<"CNP:"<<p.cnp<<endl;
        out<<"Salariu:"<<p.salariu<<endl;
    }
    catch(int x)
    {
        cout<<"CNP-ul nu este valid!";
    }
    return out;
}
class regizor:public personal
{
protected:
    int salariu_regizor;
public:
   friend ostream & operator <<(ostream &out,const regizor  &r);
   friend ifstream & operator >>(ifstream &in, regizor &r);
   regizor operator =(regizor &r);
   void salariu_personal(int n);
};

ostream & operator <<(ostream &out, const regizor &r)
{
    out<< dynamic_cast <const personal&>(r);
    return out;
}
ifstream & operator >>(ifstream &in,regizor &r)
{
    in>>r.nume;
    in>>r.prenume;
    in>>r.cnp;
    in>>r.procent_incasari;
    in>>r.salariu_regizor;
    return in;
}
regizor regizor::operator =(regizor &r)
{
    personal::operator=(r);
    return *this;
}
void regizor::salariu_personal(int incasari)
{
    salariu=salariu_regizor+(incasari*procent_incasari)/100;
}
class actor_principal:public personal
{
   public:
   friend ostream & operator <<(ostream &out,const actor_principal  &a);
   friend ifstream & operator >>(ifstream &in, actor_principal &a);
   void salariu_personal(int icasari);
};
ostream & operator <<(ostream &out, const actor_principal &a)
{
    out<< dynamic_cast <const personal&>(a);
    return out;
}
ifstream & operator >>(ifstream &in,actor_principal &a)
{
    in>> static_cast<personal&>(a);
    return in;
}
void actor_principal::salariu_personal(int incasari)
{
    salariu=(incasari*procent_incasari)/100+(10*incasari)/100;
}
class film
{
protected:
    string nume_film;
    string tip;
    int durata;
    double incasari;
    int nr_cinematografe;
    double *cinematografe;//incasarile pentru fiecare cinematograf in parte
    int nr_personal;
    int nr_actori;
    personal *p;//vector personal
    string tip_personal;
    int nr_actori_principali;

public:
    film();
    int get_nr_actori_principali(){return nr_actori_principali;};
    int get_nr_personal(){return nr_personal;};
    int get_nr_actori(){return nr_actori;};
    personal get_personal(int i){return p[i];}
    friend ostream & operator <<(ostream &out, film  &f);
    friend ifstream & operator >>(ifstream &in, film &f);

    void calculeaza_incasari()
    {
        for(int i=0;i<nr_personal;i++)
            p[i].salariu_personal(incasari);
    };
    ~film(){delete []cinematografe;
    delete []p;}
};
film::film()
{
    nume_film=" ";
     tip=" ";
     durata=0;
     incasari=0;
     nr_cinematografe=0;
     nr_personal=0;
     nr_actori=0;
     tip_personal=" ";
}
ifstream & operator >>(ifstream &in,film &f)
{

    // cout<<"Nume film:";
    in>>f.nume_film;
    // cout<<"Tip film:";
    in>>f.tip;
    // cout<<"Durata film:";
    in>>f.durata;
    // cout<<"Nr. cinematografe:";
    in>>f.nr_cinematografe;
    f.cinematografe=new double[f.nr_cinematografe];
    f.incasari=0;
    for(int i=0; i<f.nr_cinematografe; i++)
    {
        //cout<<"Incasari cinematograf:";
        in>>f.cinematografe[i];
        f.incasari+=f.cinematografe[i];
    }
    //cout<<"Nr perasonal:";
    in>>f.nr_personal;
    //cout<<"Tip personal:";
    f.p=new personal[f.nr_personal];
    for(int i=0; i<f.nr_personal; i++)
     {
    in>>f.tip_personal;
    //cout<<"Personal:";
    in>>f.p[i];
     }
    return in;
}
ostream & operator <<(ostream &out, film  &f)
{
    f.calculeaza_incasari();
    out<<"Nume film:"<<f.nume_film<<endl;
    out<<"Tip film:"<<f.tip<<endl;
    out<<"Durata film:"<<f.durata<<endl;
    out<<"Incasari:"<<f.incasari<<endl<<endl;
    out<<"Nr. personal:"<<f.nr_personal<<endl<<endl;
    f.nr_actori=0;
    //f.nr_actori_principali=0;
    for(int i=0; i<f.nr_personal; i++)
    {
        out<<"Tip personal:"<<f.tip_personal<<endl;
        if((f.tip_personal.compare("actor_principal")==0)||(f.tip_personal.compare("actor")==0))
        {
            f.nr_actori++;}
        if(f.tip_personal.compare("actor_principal")==0)
            f.nr_actori_principali++;
        out<<f.p[i]<<endl;}
        out<<endl;
        return out;
    }
template<class T>
class Firma_Distributie
{
    int an;
    int nr_persoane;
    int nr_actori;
    int nr_filme;
    personal *pers;
    T *filme;
public:
    Firma_Distributie(int a,int nr_f)
    {
        an=a;
        nr_filme=nr_f;
        filme=new T[nr_filme];
        nr_persoane=0;
        nr_actori=0;
    }
    friend ifstream &operator >>(ifstream &in,Firma_Distributie<film> &F);
    friend ostream &operator <<(ostream &out,Firma_Distributie<film> &F);
    };
ifstream &operator >>(ifstream &in,Firma_Distributie<film> &F)
{

    for(int i=0;i<F.nr_filme;i++)
        in>>F.filme[i];
        return in;
}
ostream &operator <<(ostream &out,Firma_Distributie<film> &F)
{
    for(int i=0;i<F.nr_filme;i++)
{
    out<<F.filme[i];
F.nr_persoane+=F.filme[i].get_nr_personal();

F.nr_actori+=F.filme[i].get_nr_actori();
F.pers=new personal[F.nr_persoane];
}
for(int i=0;i<F.nr_filme;i++)
{
   for(int j=0;j<F.filme[i].get_nr_personal();j++)
    F.pers[i]=F.filme[i].get_personal(j);
}
out<<"Numar total personal:"<<F.nr_persoane<<endl;
out<<"Numar total de actori:"<<F.nr_actori<<endl;
return out;
}
template<>
class Firma_Distributie<int>{
    int an;
    int nr_persoane;
    int nr_actori;
    int nr_filme;
    int nr_actori_principali;
    personal *pers;
    film *filme;

public:
    Firma_Distributie(int a,int nr_f)
    {
        an=a;
        nr_filme=nr_f;
        nr_persoane=0;
        nr_actori=0;
        nr_actori_principali=0;
    }
    friend ifstream &operator >>(ifstream &in,Firma_Distributie &F);
    friend ostream &operator <<(ostream &out,Firma_Distributie &F);
    ~Firma_Distributie()
    {
        delete[]pers;
        delete[]filme;
    }

};
ifstream &operator >>(ifstream &in,Firma_Distributie<int> &F)
{
    for(int i=0;i<F.nr_filme;i++)
        in>>F.filme[i];
        return in;
}
ostream &operator <<(ostream &out,Firma_Distributie<int> &F)
{
F.nr_actori_principali=0;
for(int i=0;i<F.nr_filme;i++)
{
    out<<F.filme[i];
F.nr_actori_principali+=F.filme[i].get_nr_actori_principali();
}
out<<"Nr. actori principali:"<<F.nr_actori_principali;
return out;
}
int main()
{
    ifstream in("date.in");

    int an_aparitie,nr_filme;

    in>>an_aparitie;
    in>>nr_filme;
    Firma_Distributie<film> f(an_aparitie,nr_filme);
    Firma_Distributie<int> g(2004,1);
    in>>f;
    cout<<f;
    cout<<g;
    return 0;
}



