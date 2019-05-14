#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
ifstream f1("input_spectacole.txt");

struct prezentare
{
    int ora;
    int minute;
    int zi;
    string luna;
    int nr_locuri;
};
class spectacol
{
protected:
    int durata;
    string nume;
    bool copii;
    string gen;
    int nr_prezentari;
    prezentare* prezentari;
public:
    string get_nume(){return nume;}
    string get_gen(){return gen;}
    bool potrivit_copii(){return copii;}
    int get_durata(){return durata;}
    void afisare_prezentari();
    bool afisare_prezentari(int max_locuri);
    virtual void adaugare_prezentare();
    virtual void creare_obiect() = 0;
    virtual spectacol& operator=(const spectacol& s);
    spectacol();
    spectacol(const spectacol& s);
    ~spectacol();
};
void spectacol::adaugare_prezentare()
{
    prezentare* var;
    var = new prezentare[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    {
        var[i].nr_locuri = prezentari[i].nr_locuri;
        var[i].ora = prezentari[i].ora;
        var[i].minute = prezentari[i].minute;
        var[i].zi = prezentari[i].zi;
        var[i].luna.assign(prezentari[i].luna);
    }
    nr_prezentari++;
    delete prezentari;
    prezentari = new prezentare[nr_prezentari];
    int i;
    for(i = 0; i < nr_prezentari - 1; i++)
    {
        prezentari[i].nr_locuri = var[i].nr_locuri;
        prezentari[i].ora = var[i].ora;
        prezentari[i].minute = var[i].minute;
        prezentari[i].zi = var[i].zi;
        prezentari[i].luna.assign(var[i].luna);
    }
    string raspuns;
    cout<<endl<<"Luna in care are loc prezentarea: ";
    cin.ignore();
    getline(cin,raspuns);
    prezentari[i].luna.assign(raspuns);
    cout<<endl<<"Ziua in care are loc prezentarea: ";
    cin>>prezentari[i].zi;
    cout<<endl<<"Ora: ";
    cin>>prezentari[i].ora;
    cout<<endl<<"Minutul: ";
    cin>>prezentari[i].minute;
    cout<<endl<<"Numarul de locuri: ";
    cin>>prezentari[i].nr_locuri;
    return;
}
void spectacol::afisare_prezentari()
{
    for(int i = 0; i < nr_prezentari; i++)
    {
        cout<<nume<<":"<<endl;
        cout<<"Data:"<<prezentari[i].zi<<" "<<prezentari[i].luna<<" ";
        if(prezentari[i].ora < 10)
            cout<<"0"<<prezentari[i].ora<<":";
        else
            cout<<prezentari[i].ora<<":";
        if(prezentari[i].minute < 10)
            cout<<"0"<<prezentari[i].minute<<endl;
        else
            cout<<prezentari[i].minute<<endl;
        cout<<"Locuri:"<<prezentari[i].nr_locuri<<endl<<endl;
    }
    return;
}
bool spectacol::afisare_prezentari(int max_locuri)
{
    bool exista = false;
    for(int i = 0; i < nr_prezentari; i++)
    {
        if(prezentari[i].nr_locuri <= max_locuri)
        {
            cout<<nume<<":"<<endl;
            exista = true;
            cout<<"Data:"<<prezentari[i].zi<<" "<<prezentari[i].luna<<" ";
            if(prezentari[i].ora < 10)
                cout<<"0"<<prezentari[i].ora<<":";
            else
                cout<<prezentari[i].ora<<":";
            if(prezentari[i].minute < 10)
                cout<<"0"<<prezentari[i].minute<<endl;
            else
                cout<<prezentari[i].minute<<endl;
            cout<<"Locuri:"<<prezentari[i].nr_locuri<<endl<<endl;
        }
    }
    return exista;
}
spectacol::spectacol()
{
    durata = 0;
    nume = " ";
    copii = false;
    gen = " ";
    nr_prezentari = 0;
    prezentari = new prezentare;
    prezentari->nr_locuri = 0;
    prezentari->ora = 0;
    prezentari->minute = 0;
    prezentari->zi = 0;
    prezentari->luna = " ";
}
spectacol::spectacol(const spectacol& s)
{
    durata = s.durata;
    nume.assign(s.nume);
    copii = s.copii;
    gen.assign(s.gen);
    nr_prezentari = s.nr_prezentari;
    prezentari = new prezentare[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    {
        prezentari[i].nr_locuri = s.prezentari[i].nr_locuri;
        prezentari[i].ora = s.prezentari[i].ora;
        prezentari[i].minute = s.prezentari[i].minute;
        prezentari[i].zi = s.prezentari[i].zi;
        prezentari[i].luna.assign(s.prezentari[i].luna);
    }
}
spectacol::~spectacol()
{
    delete []prezentari;
}
spectacol& spectacol::operator=(const spectacol& s)
{
    durata = s.durata;
    nume.assign(s.nume);
    copii = s.copii;
    gen.assign(s.gen);
    nr_prezentari = s.nr_prezentari;
    delete prezentari;
    prezentari = new prezentare[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    {
        prezentari[i].nr_locuri = s.prezentari[i].nr_locuri;
        prezentari[i].ora = s.prezentari[i].ora;
        prezentari[i].minute = s.prezentari[i].minute;
        prezentari[i].zi = s.prezentari[i].zi;
        prezentari[i].luna.assign(s.prezentari[i].luna);
    }
    return *this;
}
class opera:public spectacol
{
    struct solist
    {
        string nume;
        string tip;
    };
    struct act
    {
        solist solist_principal;
        int durata_act; //in minute
    };
    int durata_pauza;
    int nr_acte;
    act *acte;
public:
    bool exista_solist(string tip);
    opera();
    opera(const opera& o);
    ~opera();
    int get_durata_fara_pauza();
    void aloca_act(int dimensiune);
    void creare_obiect();
    opera& operator=(const spectacol& o);
    opera& operator=(const opera& o);
    friend istream& operator>>(istream& in, opera& o);
    friend ostream& operator<<(ostream& out,const opera& o);
};
bool opera::exista_solist(string tip)
{
    for(int i = 0; i < nr_acte; i++)
    {
        if(!acte[i].solist_principal.nume.compare(tip))
            return true;
    }
    return false;
}
opera::opera()
{
    durata_pauza = 0;
    nr_acte = 0;
    acte = new act;
    acte->solist_principal.nume = " ";
    acte->solist_principal.tip = " ";
    acte->durata_act = 0;
}
opera::opera(const opera& o):spectacol(o)
{
    durata_pauza = o.durata_pauza;
    nr_acte = o.nr_acte;
    acte = new act[nr_acte];
    for(int i = 0; i < nr_acte; i++)
    {
        acte[i].durata_act = o.acte[i].durata_act;
        acte[i].solist_principal.nume.assign(o.acte[i].solist_principal.nume);
        acte[i].solist_principal.tip.assign(o.acte[i].solist_principal.tip);
    }
}
opera::~opera()
{
    delete []acte;
}
int opera::get_durata_fara_pauza()
{
    return durata-durata_pauza*(nr_acte-1);
}
void opera::aloca_act(int dimensiune)
{
    delete acte;
    acte = new act[dimensiune];
}
void opera::creare_obiect()
{
   cin.clear();
   cout<<"Numele operei: ";
    getline(cin,nume);
    cout<<endl<<"Durata pauzei: ";
    cin>>durata_pauza;
    cout<<endl<<"Numarul de acte: ";
    cin>>nr_acte;
    aloca_act(nr_acte);
    durata = (nr_acte-1)*durata_pauza;
    for(int i = 0; i < nr_acte; i++)
    {
        cout<<endl<<"Durata actului "<<i+1<<": ";
        cin>>acte[i].durata_act;
        durata += acte[i].durata_act;
        cin.ignore();
        cout<<endl<<"Numele solistului principal pentru actul "<<i+1<<": ";
        cin.ignore();
        getline(cin,acte[i].solist_principal.nume);
        cout<<endl<<"Tipul solistului principal pentru actul "<<i+1<<" (tenor/bass/bariton) : ";
        getline(cin,acte[i].solist_principal.tip);
    }
    string categorie_varsta;
    cout<<endl<<"Categoria de varsta (adulti/toate): ";
    getline(cin,categorie_varsta);
    if(categorie_varsta.compare("adulti")!=0)
        copii = true;
    else
        copii = false;
    cout<<endl<<"Genul spectacolului (comedie/actiune/drama): ";
    getline(cin,gen);
    string month;
    int hh,mm,dd,locuri;
    cout<<endl<<"Numarul de prezentari: ";
    cin>>nr_prezentari;
    delete prezentari;
    prezentari = new prezentare[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    {
        cout<<"Prezentarea "<<i+1<<": "<<endl;
        cout<<endl<<"Luna in care are loc prezentarea: ";
        cin.ignore();
        getline(cin,month);
        cout<<endl<<"Ziua in care are loc prezentarea: ";
        cin>>dd;
        cout<<endl<<"Ora: ";
        cin>>hh;
        cout<<endl<<"Minutul: ";
        cin>>mm;
        cout<<endl<<"Numarul de locuri: ";
        cin>>locuri;
        prezentari[i].luna.assign(month);
        prezentari[i].zi = dd;
        prezentari[i].ora = hh;
        prezentari[i].minute = mm;
        prezentari[i].nr_locuri = locuri;
    }
}
opera& opera::operator=(const spectacol& o)
{
    if(this != &o)
    {
        spectacol::operator=(o);
        durata_pauza = 0;
        nr_acte = 0;
        acte = new act;
        acte->solist_principal.nume = " ";
        acte->solist_principal.tip = " ";
        acte->durata_act = 0;
    }
    return *this;
}
opera& opera::operator=(const opera& o)
{
    if(this != &o)
    {
        spectacol::operator=(o);
        durata_pauza = o.durata_pauza;
        nr_acte = o.nr_acte;
        delete acte;
        acte = new act[nr_acte];
        for(int i = 0; i < nr_acte; i++)
        {
            acte[i].durata_act = o.acte[i].durata_act;
            acte[i].solist_principal.nume.assign(o.acte[i].solist_principal.nume);
            acte[i].solist_principal.tip.assign(o.acte[i].solist_principal.tip);
        }
    }
    return *this;
}
istream& operator>>(istream& in, opera& o)
{
    in.clear();
    getline(in,o.nume);
    in>>o.durata_pauza;
    in>>o.nr_acte;
    o.aloca_act(o.nr_acte);
    o.durata = (o.nr_acte-1)*o.durata_pauza;
    for(int i = 0; i < o.nr_acte; i++)
    {
        in>>o.acte[i].durata_act;
        o.durata += o.acte[i].durata_act;
        in.ignore();
        getline(in,o.acte[i].solist_principal.nume);
        getline(in,o.acte[i].solist_principal.tip);
    }
    string categorie_varsta;
    getline(in,categorie_varsta);
    if(categorie_varsta.compare("adulti")==0)
        o.copii = false;
    else
        o.copii = true;
    getline(in,o.gen);
    string month;
    int hh,mm,dd,locuri;
    in>>o.nr_prezentari;
    delete o.prezentari;
    o.prezentari = new prezentare[o.nr_prezentari];
    for(int i = 0; i < o.nr_prezentari; i++)
    {
        in>>hh>>mm>>dd;
        in.ignore();
        getline(in,month);
        in>>locuri;
        o.prezentari[i].luna.assign(month);
        o.prezentari[i].zi = dd;
        o.prezentari[i].ora = hh;
        o.prezentari[i].minute = mm;
        o.prezentari[i].nr_locuri = locuri;
    }
    return in;
}
ostream& operator<<(ostream& out,const opera& o)
{
    out<<"OPERA "<<endl;
    out<<"Titlu: "<<o.nume<<endl;
    out<<"Durata: "<<o.durata<<" minute"<<endl;
    out<<"Gen: "<<o.gen<<endl;
    out<<"Varsta: ";
    if(o.copii == true)
        out<<"Orice varsta"<<endl;
    else
        out<<"Adulti"<<endl;
    out<<"Numar acte:"<<o.nr_acte<<endl;
    out<<"Prezentari:"<<endl;
    for(int i = 0; i < o.nr_prezentari; i++)
    {
        out<<"Data:"<<o.prezentari[i].zi<<" "<<o.prezentari[i].luna<<" ";
        if(o.prezentari[i].ora < 10)
            out<<"0"<<o.prezentari[i].ora<<":";
        else
            out<<o.prezentari[i].ora<<":";
        if(o.prezentari[i].minute < 10)
            out<<"0"<<o.prezentari[i].minute<<endl;
        else
            out<<o.prezentari[i].minute<<endl;
        out<<"Locuri:"<<o.prezentari[i].nr_locuri<<endl<<endl;
    }
    return out;
}
class teatru:public spectacol
{
    bool interactiv;
    int *durata_variabila;//pentru fiecare prezentare in parte
public:
    teatru();
    teatru(const teatru& t);
    bool este_interactiv(){return interactiv;}
    ~teatru();
    teatru& operator=(const spectacol& t);
    teatru& operator=(const teatru& t);
    void calcul_durata_variabila();
    void creare_obiect();
    void adaugare_prezentare();
    friend istream& operator>>(istream& in, teatru& t);
    friend ostream& operator<<(ostream& out, const teatru& t);
};
teatru::teatru()
{
    interactiv = false;
    durata_variabila = new int;
    durata_variabila = 0;
}
teatru::teatru(const teatru& t):spectacol(t)
{
    interactiv = t.interactiv;
    delete durata_variabila;
    durata_variabila = new int[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    durata_variabila[i] = t.durata_variabila[i];
}
teatru::~teatru()
{
    delete []durata_variabila;
}
teatru& teatru::operator=(const spectacol& t)
{
    if(this != &t)
    {
        spectacol::operator=(t);
        interactiv = false;
        durata_variabila = new int;
        durata_variabila = 0;
    }
    return *this;
}
teatru& teatru::operator=(const teatru& t)
{
    if(this != &t)
    {
        spectacol::operator=(t);
        interactiv = t.interactiv;
        delete durata_variabila;
        durata_variabila = new int[nr_prezentari];
        for(int i = 0; i < nr_prezentari; i++)
            durata_variabila[i] = t.durata_variabila[i];
    }
    return *this;
}
void teatru::calcul_durata_variabila()
{
    if(interactiv == false)
    for(int i = 0; i < nr_prezentari; i++)
        durata_variabila[i] = durata;
    else
    if(copii == false)
        for(int i = 0; i < nr_prezentari; i++)
        durata_variabila[i] = durata + prezentari[i].nr_locuri;
    else
        for(int i = 0; i < nr_prezentari; i++)
        durata_variabila[i] = durata + 2*prezentari[i].nr_locuri;
}
void teatru::creare_obiect()
{
    cout<<"Titlul spectacolului de teatru: ";
    getline(cin,nume);
    cout<<endl<<"Durata: ";
    cin>>durata;
    cout<<endl<<"Categoria de varsta (adulti/toate): ";
    string categorie_varsta;
    cin.ignore();
    getline(cin,categorie_varsta);
    if(categorie_varsta.compare("adulti")==0)
        copii = false;
    else
        copii = true;
    cout<<endl<<"Genul spectacolului: ";
    getline(cin,gen);
    string verif_interactiv;
    cout<<endl<<"Tipul spectacolului (interactiv/neinteractiv): ";
    getline(cin,verif_interactiv);
    if(verif_interactiv.compare("interactiv")==0)
        interactiv = true;
    else
        interactiv = false;
    string month;
    int hh,mm,dd,locuri;
    cout<<endl<<"Numarul de prezentari: ";
    cin>>nr_prezentari;
    delete prezentari;
    prezentari = new prezentare[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    {
        cout<<endl<<"Prezentarea "<<i+1<<": "<<endl;
        cout<<endl<<"Luna in care are loc prezentarea: ";
        cin.ignore();
        getline(cin,month);
        cout<<endl<<"Ziua in care are loc prezentarea: ";
        cin>>dd;
        cout<<endl<<"Ora: ";
        cin>>hh;
        cout<<endl<<"Minutul: ";
        cin>>mm;
        cout<<endl<<"Numarul de locuri: ";
        cin>>locuri;
        prezentari[i].luna.assign(month);
        prezentari[i].zi = dd;
        prezentari[i].ora = hh;
        prezentari[i].minute = mm;
        prezentari[i].nr_locuri = locuri;
    }
    delete durata_variabila;
    durata_variabila = new int[nr_prezentari];
    calcul_durata_variabila();
}
void teatru::adaugare_prezentare()
{
    spectacol::adaugare_prezentare();
    if(!interactiv)
        durata_variabila[nr_prezentari-1] = durata;
    else
    if(copii == false)
        durata_variabila[nr_prezentari-1] = durata + prezentari[nr_prezentari-1].nr_locuri;
    else
        durata_variabila[nr_prezentari-1] = durata + 2*prezentari[nr_prezentari-1].nr_locuri;
}

istream& operator>>(istream& in, teatru& t)
{
    getline(in,t.nume);
    in>>t.durata;
    string categorie_varsta;
    in.ignore();
    getline(in,categorie_varsta);
    if(categorie_varsta.compare("adulti")==0)
        t.copii = false;
    else
        t.copii = true;
    getline(in,t.gen);
    string verif_interactiv;
    getline(in,verif_interactiv);
    if(verif_interactiv.compare("interactiv")==0)
        t.interactiv = true;
    else
        t.interactiv = false;
    string month;
    int hh,mm,dd,locuri;
    in>>t.nr_prezentari;
    delete t.prezentari;
    t.prezentari = new prezentare[t.nr_prezentari];
    for(int i = 0; i < t.nr_prezentari; i++)
    {
        in>>hh>>mm>>dd;
        in.ignore();
        getline(in,month);
        in>>locuri;
        t.prezentari[i].luna.assign(month);
        t.prezentari[i].zi = dd;
        t.prezentari[i].ora = hh;
        t.prezentari[i].minute = mm;
        t.prezentari[i].nr_locuri = locuri;
    }
    delete t.durata_variabila;
    t.durata_variabila = new int[t.nr_prezentari];
    t.calcul_durata_variabila();
    return in;
}
ostream& operator<<(ostream& out, const teatru& t)
{
    out<<"TEATRU "<<endl;
    out<<"Titlu: "<<t.nume<<endl;
    out<<"Durata: "<<t.durata<<" minute"<<endl;
    out<<"Gen: "<<t.gen<<endl;
    out<<"Varsta: ";
    if(t.copii == true)
        out<<"Orice varsta"<<endl;
    else
        out<<"Adulti"<<endl;
    if(t.interactiv)
        out<<"Spectacolul este interactiv"<<endl;
    else
        out<<"Spectacolul nu este interactiv"<<endl;
    out<<"Prezentari:"<<endl;
    for(int i = 0; i < t.nr_prezentari; i++)
    {
        out<<"Data:"<<t.prezentari[i].zi<<" "<<t.prezentari[i].luna<<" ";
        if(t.prezentari[i].ora < 10)
            out<<"0"<<t.prezentari[i].ora<<":";
        else
            out<<t.prezentari[i].ora<<":";
        if(t.prezentari[i].minute < 10)
            out<<"0"<<t.prezentari[i].minute<<endl;
        else
            out<<t.prezentari[i].minute<<endl;
        out<<"Locuri:"<<t.prezentari[i].nr_locuri<<endl;
        if(t.interactiv)
            out<<"Durata maxima:"<<t.durata_variabila[i]<<endl;
        out<<endl;
    }
    return out;
}

class circ:public spectacol
{
    struct prestatie
    {
        string nume;
        int nr_animale;
        vector <string> animale;
        bool copii;
    };
    int nr_prestatii;
    prestatie *prestatii;
public:
    circ();
    circ(const circ& c);
    ~circ();
    circ& operator=(const spectacol& c);
    circ& operator=(const circ& c);
    bool animale_periculoase();
    bool include_animal(string animal);
    void aloca_prestatii(int dimensiune);
    void creare_obiect();
    friend istream& operator>>(istream& in, circ& c);
    friend ostream& operator<<(ostream& out, const circ& c);
};
circ::circ()
{
    nr_prestatii = 0;
    gen.assign("comedie");
    prestatii = new prestatie;
    prestatii->nume.assign(" ");
    prestatii->nr_animale = 0;
    prestatii->copii = true;
}
circ::circ(const circ& c):spectacol(c)
{
    nr_prestatii = c.nr_prestatii;
    prestatii = new prestatie[nr_prestatii];
    for(int i = 0; i < c.nr_prestatii; i++)
    {
        prestatii[i].nume.assign(c.prestatii[i].nume);
        prestatii[i].nr_animale = c.prestatii[i].nr_animale;
        prestatii[i].animale.resize(prestatii[i].nr_animale);
        for(int j = 0; j < prestatii[i].nr_animale; j++)
            prestatii[i].animale[j] = c.prestatii[i].animale[j];
        prestatii[i].copii = c.prestatii[i].copii;
    }
}
circ::~circ()
{
    delete []prestatii;
}
circ& circ::operator=(const spectacol& c)
{
    if(this != &c)
    {
        spectacol::operator=(c);
        nr_prestatii = 0;
        gen.assign("comedie");
        prestatii = new prestatie;
        prestatii->nume.assign(" ");
        prestatii->nr_animale = 0;
        prestatii->copii = true;
    }
    return *this;
}
circ& circ::operator=(const circ& c)
{
    if(this != &c)
    {
        spectacol::operator=(c);
        nr_prestatii = c.nr_prestatii;
        delete prestatii;
        prestatii = new prestatie[nr_prestatii];
        for(int i = 0; i < c.nr_prestatii; i++)
        {
            prestatii[i].nume.assign(c.prestatii[i].nume);
            prestatii[i].nr_animale = c.prestatii[i].nr_animale;
            prestatii[i].animale.resize(prestatii[i].nr_animale);
            for(int j = 0; j < prestatii[i].nr_animale; j++)
                prestatii[i].animale[j] = c.prestatii[i].animale[j];
            prestatii[i].copii = prestatii[i].copii;
        }
    }
    return *this;
}
bool circ::animale_periculoase()
{
    for(int i = 0; i < nr_prestatii; i++)
        for(int j = 0; j < prestatii[i].nr_animale; j++)
        if(!prestatii[i].animale[j].compare("leu") || !prestatii[i].animale[j].compare("tigru") || !prestatii[i].animale[j].compare("sarpe") || !prestatii[i].animale[j].compare("crocodil"))
        return true;
    return false;
}
bool circ::include_animal(string animal)
{
    for(int i = 0; i < nr_prestatii; i++)
        for(int j = 0; j < prestatii[i].nr_animale; j++)
        if(!prestatii[i].animale[j].compare(animal))
        return true;
    return false;
}
void circ::aloca_prestatii(int dimensiune)
{
    prestatii = new prestatie[dimensiune];
}
void circ::creare_obiect()
{
    cout<<"Titlul spectacolului de circ: ";
    getline(cin,nume);
    gen.assign("comedie");
    cout<<endl<<"Durata: ";
    cin>>durata;
    cout<<endl<<"Numarul de prestatii: ";
    cin>>nr_prestatii;
    delete prestatii;
    aloca_prestatii(nr_prestatii);
    bool copii_ok = true;
    cin.ignore();
    for(int i = 0; i < nr_prestatii; i++)
    {
        cout<<endl<<"Titlul prestatiei: ";
        getline(cin,prestatii[i].nume);
        cout<<endl<<"Numarul de animale implicate in prestatie: ";
        cin>>prestatii[i].nr_animale;
        cin.ignore();
        prestatii[i].animale.resize(prestatii[i].nr_animale);
        if(prestatii[i].nr_animale != 0)
            cout<<endl<<"Animalele implicate: ";
        for(int j = 0; j < prestatii[i].nr_animale; j++)
        {
            getline(cin,prestatii[i].animale[j]);
        }
        string categorie_varsta;
        cout<<endl<<"Categoria de varsta (adulti/toate): ";
        getline(cin,categorie_varsta);
        if(categorie_varsta.compare("adulti") == 0)
        {
            prestatii[i].copii = false;
            copii_ok = false;
        }
        else
            prestatii[i].copii = true;
    }
    if(copii_ok == true)
        copii = true;
    else
        copii = false;
    string month;
    int hh,mm,dd,locuri;
    cout<<endl<<"Numarul de prezentari: ";
    cin>>nr_prezentari;
    delete prezentari;
    prezentari = new prezentare[nr_prezentari];
    for(int i = 0; i < nr_prezentari; i++)
    {
        cout<<endl<<"Prezentarea "<<i+1<<": "<<endl;
        cout<<endl<<"Luna in care are loc prezentarea: ";
        cin.ignore();
        getline(cin,month);
        cout<<endl<<"Ziua in care are loc prezentarea: ";
        cin>>dd;
        cout<<endl<<"Ora: ";
        cin>>hh;
        cout<<endl<<"Minutul: ";
        cin>>mm;
        cout<<endl<<"Numarul de locuri: ";
        cin>>locuri;
        prezentari[i].luna.assign(month);
        prezentari[i].zi = dd;
        prezentari[i].ora = hh;
        prezentari[i].minute = mm;
        prezentari[i].nr_locuri = locuri;
    }
}
istream& operator>>(istream& in, circ& c)
{
    getline(in,c.nume);
    c.gen.assign("comedie");
    in>>c.durata;
    in>>c.nr_prestatii;
    delete c.prestatii;
    c.aloca_prestatii(c.nr_prestatii);
    bool copii_ok = true;
    in.ignore();
    for(int i = 0; i < c.nr_prestatii; i++)
    {
        getline(in,c.prestatii[i].nume);
        in>>c.prestatii[i].nr_animale;
        in.ignore();
        c.prestatii[i].animale.resize(c.prestatii[i].nr_animale);
        for(int j = 0; j < c.prestatii[i].nr_animale; j++)
        {
            getline(in,c.prestatii[i].animale[j]);
        }
        string categorie_varsta;
        getline(in,categorie_varsta);
        if(categorie_varsta.compare("adulti") == 0)
        {
            c.prestatii[i].copii = false;
            copii_ok = false;
        }
        else
            c.prestatii[i].copii = true;
    }
    if(copii_ok == true)
        c.copii = true;
    else
        c.copii = false;
    string month;
    int hh,mm,dd,locuri;
    in>>c.nr_prezentari;
    delete c.prezentari;
    c.prezentari = new prezentare[c.nr_prezentari];
    for(int i = 0; i < c.nr_prezentari; i++)
    {
        in>>hh>>mm>>dd;
        in.ignore();
        getline(in,month);
        in>>locuri;
        c.prezentari[i].luna.assign(month);
        c.prezentari[i].zi = dd;
        c.prezentari[i].ora = hh;
        c.prezentari[i].minute = mm;
        c.prezentari[i].nr_locuri = locuri;
    }
    return in;
}
ostream& operator<<(ostream& out, const circ& c)
{
    cout<<"CIRC "<<endl;
    cout<<"Titlu: "<<c.nume<<endl;
    cout<<"Durata: "<<c.durata<<" minute"<<endl;
    cout<<"Varsta: ";
    if(c.copii == true)
        cout<<"Orice varsta"<<endl;
    else
        cout<<"Adulti"<<endl;
    cout<<"Prestatii:"<<endl;
    for(int i = 0; i < c.nr_prestatii; i++)
    {
        cout<<c.prestatii[i].nume<<endl;
        if(c.prestatii[i].nr_animale == 0)
            cout<<"Prestatia nu implica animale."<<endl;
        else
        {
            cout<<"Prestatia implica urmatoarele animale:";
            for(int j = 0; j < c.prestatii[i].nr_animale - 1; j++)
                cout<<c.prestatii[i].animale[j]<<", ";
            cout<<c.prestatii[i].animale[c.prestatii[i].nr_animale-1]<<endl;
        }
    }
    cout<<"Prezentari:"<<endl;
    for(int i = 0; i < c.nr_prezentari; i++)
    {
        cout<<"Data:"<<c.prezentari[i].zi<<" "<<c.prezentari[i].luna<<" ";
        if(c.prezentari[i].ora < 10)
            cout<<"0"<<c.prezentari[i].ora<<":";
        else
            cout<<c.prezentari[i].ora<<":";
        if(c.prezentari[i].minute < 10)
            cout<<"0"<<c.prezentari[i].minute<<endl;
        else
            cout<<c.prezentari[i].minute<<endl;
        cout<<"Locuri:"<<c.prezentari[i].nr_locuri<<endl<<endl;
    }
    return out;
}
vector <opera> o;
vector <circ> c;
vector <teatru> t;
struct pofta
{
    bool satisfacuta;
    string gen;
    string tip;
    int durata_minima;
    bool cu_pauza;
    string tip_animale;
    bool teatru_interactiv;
    string tip_voce;
};
struct exigenta
{
    bool satisfacuta;
    string combinatie[2];
    int durata_maxima;
    bool animale_periculoase;
    int nr_maxim_spec;
};
bool satisface_pofte(pofta p,opera o)
{
    if(p.satisfacuta)
        return true;//nu exista pofte
    if(!p.gen.compare(o.get_gen()))
        return true;
    if(!p.tip.compare("opera"))
        return true;
    if(p.durata_minima != -1)
    {
        if(p.cu_pauza && o.get_durata()>= p.durata_minima)
            return true;
        else
        if(!p.cu_pauza && o.get_durata_fara_pauza() >= p.durata_minima)
            return true;
    }
    if(o.exista_solist(p.tip_voce))
        return true;
    return false;
}
bool satisface_exigente(exigenta e,opera o)
{
    if(e.satisfacuta)
    {
        o.afisare_prezentari();
        return true;//nu sunt exigente
    }
    if(!e.combinatie[0].compare("opera") && !e.combinatie[1].compare(o.get_gen()))
        return false;
    if(e.durata_maxima < o.get_durata() && e.durata_maxima != -1)
        return false;
    if(e.nr_maxim_spec != -1)
    {
        if(!o.afisare_prezentari(e.nr_maxim_spec))//se afiseaza in functie
        return false;
    }
    else
        o.afisare_prezentari();
    return true;
}
bool satisface_pofte(pofta p, teatru t)
{
    if(p.satisfacuta)
        return true;//nu exista pofte
    if(!p.gen.compare(t.get_gen()))
        return true;
    if(!p.tip.compare("teatru"))
        return true;
    if(t.get_durata() >= p.durata_minima && p.durata_minima != -1)
        return true;
    if(p.teatru_interactiv && t.este_interactiv())
        return true;
    return false;
}
bool satisface_exigente(exigenta e,teatru t)
{
    if(e.satisfacuta)
    {
        t.afisare_prezentari();
        return true;//nu sunt exigente
    }
    if(!e.combinatie[0].compare("teatru") && !e.combinatie[1].compare(t.get_gen()))
        return false;
    if(e.durata_maxima < t.get_durata() && e.durata_maxima != -1)
        return false;
    if(e.nr_maxim_spec != -1)
    {
        if(!t.afisare_prezentari(e.nr_maxim_spec))
        return false;
    }
    else
        t.afisare_prezentari();
    return true;
}
bool satisface_pofte(pofta p, circ c)
{
    if(p.satisfacuta)
        return true;//nu exista pofte
    if(!p.gen.compare("comedie"))
        return true;
    if(!p.tip.compare("circ"))
        return true;
    if(c.get_durata()>= p.durata_minima && p.durata_minima != -1)
        return true;
    if(c.include_animal(p.tip_animale))
        return true;
    return false;
}
bool satisface_exigente(exigenta e, circ c)
{
    if(e.satisfacuta)
    {
        c.afisare_prezentari();
        return true;//nu sunt exigente
    }
    if(!e.combinatie[0].compare("circ") && e.combinatie[1].compare("comedie"))
        return false;
    if(!(e.animale_periculoase) && c.animale_periculoase())
        return false;
    if(e.durata_maxima < c.get_durata() && e.durata_maxima != -1)
        return false;
    if(e.nr_maxim_spec != -1)
    {
        if(!c.afisare_prezentari(e.nr_maxim_spec))
        return false;
    }
    else
        c.afisare_prezentari();
    return true;
}
void afisare_prezentari()
{
    pofta p;
    exigenta e;
    string nume;
    int varsta;
    cout<<"Numele: ";
    getline(cin,nume);
    cout<<"Buna, "<<nume<<"! "<<endl<<"Varsta: ";
    cin>>varsta;
    p.satisfacuta = true;
    cout<<"Pofte:"<<endl;
    cout<<"Doriti un anumit tip de spectacol?(da/nu)"<<endl;
    string raspuns;
     cin.ignore();
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Ce tip de spectacol doriti? (opera/teatru/circ)"<<endl;
        getline(cin,p.tip);
        p.satisfacuta = false;
    }
    else
        p.tip = " ";
    cout<<"Doriti un anumit gen spectacol?(da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Ce gen de spectacol doriti? (comedie/actiune/drama)"<<endl;
        getline(cin,p.gen);
        p.satisfacuta = false;
    }
    else
        p.gen = " ";
    cout<<"Doriti ca spectacolul sa aiba o durata minima?(da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Care preferati sa fie durata minima a unui spectacol? (in minute)"<<endl;
        cin>>p.durata_minima;
        cin.ignore();
        cout<<"Doriti sa fie incluse si pauzele in cele "<<p.durata_minima<<" minute? (da/nu)"<<endl;
        getline(cin,raspuns);
        if(!raspuns.compare("da"))
            p.cu_pauza = true;
        else
            p.cu_pauza = false;
        p.satisfacuta = false;
    }
    else
        {
            p.durata_minima = -1;
            p.cu_pauza = false;
        }
    cout<<"In cazul in care mergeti la un spectacol de circ, preferati sa vedeti un anumit tip de animale?(da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Ce tip de animale ati dori sa vedeti? (ex: iepure, elefant, girafa, etc.)"<<endl;
        getline(cin,p.tip_animale);
        p.satisfacuta = false;
    }
    else
        p.tip_animale = " ";
    cout<<"In cazul in care mergeti la un spectacol de teatru, preferati ca acesta sa fie interactiv?(da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        p.teatru_interactiv = true;
        p.satisfacuta = false;
    }
    else
        p.teatru_interactiv = false;
    cout<<"In cazul in care mergeti la un spectacol de opera, preferati un anumit tip de voce?(da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Ce tip de voce ai prefera? (tenor/bariton/bass)"<<endl;
        getline(cin,p.tip_voce);
        p.satisfacuta = false;
    }
    else
        p.tip_voce = " ";
    cout<<endl<<"Exigente: "<<endl;
    e.satisfacuta = true;
    cout<<"Doriti sa evitati o anumita combinatie de tip si gen? (da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Ce combinatie doriti sa evitati? (opera + comedie/ teatru + drama etc)"<<endl;
        getline(cin,e.combinatie[0]);
        getline(cin,e.combinatie[1]);
        e.satisfacuta = false;
    }
    else
    {
        e.combinatie[0] = " ";
        e.combinatie[1] = " ";
    }
    cout<<"Doriti ca spectacolul sa aiba o durata maxima? (da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        cout<<"Care doriti sa fie durata maxima a spectacolului? (in minute)"<<endl;
        cin>>e.durata_maxima;
        cin.ignore();
        e.satisfacuta = false;
    }
    else
        e.durata_maxima = -1;
    cout<<"In cazul spectacolelor de circ, doriti ca numarul sa nu includa si animale periculoase? (da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
    {
        e.animale_periculoase = false;
        e.satisfacuta = false;
    }
    else
        e.animale_periculoase = true;
    cout<<"Doriti ca spectacolul sa aiba un numar maxim de spectatori? (da/nu)"<<endl;
    getline(cin,raspuns);
    if(!raspuns.compare("da"))
        {
            cout<<"Care este numarul maxim de spectatori?"<<endl;
            cin>>e.nr_maxim_spec;
            e.satisfacuta = false;
            cin.ignore();
        }
    else
        e.nr_maxim_spec = -1;
    //selectia propriu-zisa

    bool exista = false;
    for(int i = 0; i < (int)c.size(); i++)
    {
        //verific daca se potriveste varstei si daca satisface una din pofte
        if((varsta < 18 && c[i].potrivit_copii()) || varsta >= 18)
        if(satisface_pofte(p,c[i]))
            if(satisface_exigente(e,c[i]))//odata gasite, se afiseaza aici
            exista = true;
    }
    for(int i = 0; i < (int)t.size(); i++)
    {
        //verific daca se potriveste varstei si daca satisface una din pofte
        if((varsta < 18 && t[i].potrivit_copii()) || varsta >= 18)
        if(satisface_pofte(p,t[i]))
            if(satisface_exigente(e,t[i]))//odata gasite, se afiseaza aici
            exista = true;
    }
    for(int i = 0; i < (int)o.size(); i++)
    {
        //verific daca se potriveste varstei si daca satisface una din pofte
        if((varsta < 18 && o[i].potrivit_copii()) || varsta >= 18)
        if(satisface_pofte(p,o[i]))
            if(satisface_exigente(e,o[i]))//odata gasite, se afiseaza aici
            exista = true;
    }

    if(!exista)
        cout<<"Nu au fost gasite prezentari potrivite."<<endl;

    return;
}
void citire_tastatura()
{
    cout<<"Ce tip de spectacol doresti sa adaugi?"<<endl;
    string tip;
    getline(cin,tip);
    if(!tip.compare("opera"))
    {
        opera var;
        var.creare_obiect();
        o.push_back(var);
    }
    else
    if(!tip.compare("teatru"))
    {
        teatru var;
        var.creare_obiect();
        t.push_back(var);
    }
    else
    if(!tip.compare("circ"))
    {
        circ var;
        var.creare_obiect();
        c.push_back(var);
    }
    return;
}
void introducere_prezentare()
{
    cout<<"Pentru ce spectacol doriti sa adaugati prezentarea?"<<endl;
    int nr;
    for(int i = 0; i < (int)o.size(); i++)
        cout<<i+1<<". "<<o[i].get_nume()<<endl;
    for(int i = 0; i < (int)t.size(); i++)
        cout<<i+(int)o.size()+1<<". "<<t[i].get_nume()<<endl;
    for(int i = 0; i < (int)c.size(); i++)
        cout<<i+(int)o.size()+(int)t.size()+1<<". "<<c[i].get_nume()<<endl;
    cin>>nr;
    nr--;
    if(nr < (int)o.size())
    {
        cout<<o[nr].get_nume()<<": "<<endl;
        o[nr].adaugare_prezentare();
    }
    else
    if((int)o.size() <= nr && nr < (int)t.size()+(int)o.size())
    {
        cout<<t[nr-(int)o.size()].get_nume()<<": "<<endl;
        t[nr-(int)o.size()].adaugare_prezentare();
    }
    else
    if(nr >= (int)t.size()+(int)o.size())
    {
        cout<<c[nr-(int)t.size()-(int)o.size()].get_nume()<<": "<<endl;
        c[nr-(int)t.size()-(int)o.size()].adaugare_prezentare();
    }
    return;
}
void afisare_spectacole()
{
    for(int i = 0; i < (int)o.size(); i++)
        cout<<o[i]<<endl;
    for(int i = 0; i < (int)t.size(); i++)
        cout<<t[i]<<endl;
    for(int i = 0; i < (int)c.size(); i++)
        cout<<c[i]<<endl;
}
void meniu()
{
    cout<<"Buna! Alege una din urmatoarele optiuni:"<<endl;
    cout<<"1. Afisarea prezentarilor pentru un spectator."<<endl;
    cout<<"2. Introducerea unui spectacol."<<endl;
    cout<<"3. Introducerea unei prezentari pentru un spectacol."<<endl;
    cout<<"4. Afisarea spectacolelor."<<endl;
    cout<<"5. Inchiderea programului."<<endl;
    cout<<"Raspuns: ";
    int r;
    cin>>r;
    cin.ignore();
    switch(r)
    {
        case 1: afisare_prezentari(); break;
        case 2: citire_tastatura(); break;
        case 3: introducere_prezentare();break;
        case 4: afisare_spectacole();break;
        case 5: return;
        default: cout<<" Raspunsul nu este corect! "<<endl<<endl; meniu();
    }
    cout<<endl<<endl;
        meniu();
}
void citire(int n)
{
    string tip;
    f1.ignore();
    for(int i = 0; i < n; i++)
    {

        getline(f1,tip);
        if(!tip.compare("opera"))
        {
            opera var;
            f1>>var;
            o.push_back(var);
            if(i != n-1)
            {
                getline(f1,tip);
                f1.ignore();
            }
        }
        else
        if(!tip.compare("teatru"))
        {
            teatru var;
            f1>>var;
            t.push_back(var);
            if(i != n-1)
            {
                getline(f1,tip);
                f1.ignore();
            }
        }
        else
        if(!tip.compare("circ"))
        {
            circ var;
            f1>>var;
            c.push_back(var);
            if(i != n-1)
            {
                getline(f1,tip);
                f1.ignore();
            }
        }
    }
    return;
}

int main()
{
    int n;
    f1>>n;
    citire(n);
    meniu();
    f1.close();
    return 0;
}
