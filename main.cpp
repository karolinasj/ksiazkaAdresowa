#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <cstring>
#include <algorithm>


using namespace std;

struct Kontakt
{
    string imie;
    string nazwisko;
    int id;
    string adres, numerTelefonu, email;
};

int policzLiczbeKontaktow()
{
    string linia;
    int licznik = 0;
    int liczbaKontaktow;
    fstream plik;
    plik.open("wektory.txt" , ios::in);

    if(!plik.good())
    {
        liczbaKontaktow = 0;
        return liczbaKontaktow;
    }

    while (!plik.eof())
    {
        getline(plik, linia);
        licznik++;
    }
    liczbaKontaktow = licznik;

    plik.close();
    return liczbaKontaktow;
}
void podzialNaSlowaIDodanieDoKsiazki(string linia, vector <Kontakt> &listaOsob )
{
    Kontakt roboczyDoDodania;
    string polaKsiazkiAdresowej[6];
    string slowo = "";
    int j=0;

    for (auto x : linia)
    {
        if (x == '|')
        {
            polaKsiazkiAdresowej[j] = slowo;
            j++;
            slowo = "";
        }
        else
        {
            slowo = slowo + x;
        }
    }
int idKontaktu = stoi(polaKsiazkiAdresowej[0]);
roboczyDoDodania.id = idKontaktu;
roboczyDoDodania.imie = polaKsiazkiAdresowej[1];
roboczyDoDodania.nazwisko = polaKsiazkiAdresowej[2];
roboczyDoDodania.numerTelefonu = polaKsiazkiAdresowej[3];
roboczyDoDodania.email = polaKsiazkiAdresowej[4];
roboczyDoDodania.adres = polaKsiazkiAdresowej[5];

listaOsob.push_back(roboczyDoDodania);

}

void wczytywanieWszystkichKontaktowZPliku(vector <Kontakt> &listaOsob, int liczbaKontaktow)
{
    system( "cls" );
    int nrLinii=1;
    string linia;

    fstream plik;
    plik.open("wektory.txt",ios::in);
    if (plik.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku!";
    }
    else
    {
        for(int i=0; i<liczbaKontaktow; i++)
        {
            while(getline(plik,linia))
            {
                podzialNaSlowaIDodanieDoKsiazki(linia, listaOsob);
                nrLinii++;
            }
        }
        plik.close();
    }
}

void dodajNowy(vector <Kontakt> &listaOsob)
{
    int noweOstatnieId=0;
    system( "cls" );
    cout << "Dodawanie nowego kontaktu..."<<endl;

    int liczbaOsobPrzedDodaniem = listaOsob.size();
    string imie, nazwisko, email, adres, numerTelefonu;

    Kontakt Roboczy;

    cout << "Podaj imie: ";
    cin.clear();
    cin.sync();
    getline( cin, imie );

    cout << "Podaj nazwisko: ";
    cin.clear();
    cin.sync();
    getline( cin, nazwisko );

    cout << "Podaj adres email: ";
    cin.clear();
    cin.sync();
    getline( cin, email );

    cout << "Podaj adres: ";
    cin.clear();
    cin.sync();
    getline( cin, adres );

    cout << "Podaj numer telefonu: ";
    cin.clear();
    cin.sync();
    getline( cin, numerTelefonu );

    Roboczy.imie = imie;
    Roboczy.nazwisko = nazwisko;
    Roboczy.email = email;
    Roboczy.adres = adres;
    Roboczy.numerTelefonu = numerTelefonu;

    if (listaOsob.size()!=0)
    {
        noweOstatnieId=listaOsob[liczbaOsobPrzedDodaniem-1].id+1;
    }
    else
    {
        noweOstatnieId=1;
    }

    Roboczy.id=noweOstatnieId;

    listaOsob.push_back(Roboczy);
    fstream plik;
    plik.open("wektory.txt" , ios::out | ios::app);
    plik <<endl<<noweOstatnieId<<"|"<<imie <<"|"<<nazwisko<<"|"<<numerTelefonu<<"|"<<email<<"|"<<adres<<"|";

    plik.close();
}

void wyswietlanieWszystkichKontaktow(vector <Kontakt> &listaOsob)
{
    system( "cls" );
    cout << "Liczba kontaktow: "<< listaOsob.size()<<endl;
    for(int i=0; i<listaOsob.size(); i++)
    {
        cout << listaOsob[i].id;
        cout << " "<<listaOsob[i].imie<<" ";
        cout << listaOsob[i].nazwisko<<endl;
        cout << "Adres: "<<listaOsob[i].adres<<endl;
        cout << "E-mail: "<<listaOsob[i].email<<endl;
        cout << "Numer telefonu: " << listaOsob[i].numerTelefonu<<endl<<endl;
    }
    system("pause");
}

int wyszukiwanieKontaktuPoId(vector <Kontakt> &listaOsob)
{
    int szukanyIndeks=-1;
    int id;
    cout << "Podaj ID: ";
    cin >> id;

    for( std::vector<Kontakt>::iterator i = listaOsob.begin(); i < listaOsob.end(); i++)
    {
        if(i->id == id)
        {
            szukanyIndeks=distance(listaOsob.begin(), i);
        }
    }
    return szukanyIndeks;

}

void wyszukiwanieKontaktuPoImieniu(vector <Kontakt> &listaOsob)
{
    string imie;
    system( "cls" );
    cout << "Wyszukiwanie kontaktu po imieniu..."<<endl;
    cout << "Podaj imie: ";
    cin >> imie;
    int liczbaZnalezionychKontaktow=0;
    for( std::vector<Kontakt>::iterator i = listaOsob.begin(); i < listaOsob.end(); i++)
    {
        if(i->imie == imie)
        {
            cout << listaOsob[distance(listaOsob.begin(), i)].id <<" "<<listaOsob[distance(listaOsob.begin(), i)].imie <<" "<<listaOsob[distance(listaOsob.begin(), i)].nazwisko<<endl;
            cout << listaOsob[distance(listaOsob.begin(), i)].email <<endl<<listaOsob[distance(listaOsob.begin(), i)].adres <<endl<<listaOsob[distance(listaOsob.begin(), i)].numerTelefonu<< endl ;

            liczbaZnalezionychKontaktow++;
        }
    }
    cout << "Znaleziono "<<liczbaZnalezionychKontaktow <<" pasujacych kontaktow"<<endl;
    system("pause");

}

void wyszukiwanieKontaktuPoNazwisku(vector <Kontakt> &listaOsob)
{
    string nazwisko;
    system( "cls" );
    cout << "Wyszukiwanie kontaktu po nazwisku..."<<endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    int liczbaZnalezionychKontaktow=0;

    for( std::vector<Kontakt>::iterator i = listaOsob.begin(); i < listaOsob.end(); i++)
    {
        if(i->nazwisko == nazwisko)
        {
            cout << listaOsob[distance(listaOsob.begin(), i)].id <<" "<<listaOsob[distance(listaOsob.begin(), i)].imie <<" "<<listaOsob[distance(listaOsob.begin(), i)].nazwisko<<endl;
            cout << listaOsob[distance(listaOsob.begin(), i)].email <<endl<<listaOsob[distance(listaOsob.begin(), i)].adres <<endl<<listaOsob[distance(listaOsob.begin(), i)].numerTelefonu <<endl;
            liczbaZnalezionychKontaktow++;
        }
    }
    cout << "Znaleziono "<<liczbaZnalezionychKontaktow <<" pasujacych kontaktow"<<endl;
    system("pause");

}

void aktualizujPlik(vector <Kontakt> &listaOsob)
{
    int wielkoscWektora = listaOsob.size();
    if(wielkoscWektora == 0)
    {
        remove( "wektory.txt" );
        return ;
    }

    fstream plik;
    plik.open("wektory.txt" , ios::out);
    int i=0;
    plik <<listaOsob[i].id<<"|"<<listaOsob[i].imie <<"|"<<listaOsob[i].nazwisko<<"|"<<listaOsob[i].numerTelefonu<<"|"<<listaOsob[i].email<<"|"<<listaOsob[i].adres<<"|";

    for(i=1; i<wielkoscWektora; i++)
    {
        plik <<endl<<listaOsob[i].id<<"|"<<listaOsob[i].imie <<"|"<<listaOsob[i].nazwisko<<"|"<<listaOsob[i].numerTelefonu<<"|"<<listaOsob[i].email<<"|"<<listaOsob[i].adres<<"|";
    }
    plik.close();
}

int usuwanieKontaktu(vector <Kontakt> &listaOsob)
{
    int indeksUsuwanegoKontaktu;
    indeksUsuwanegoKontaktu = wyszukiwanieKontaktuPoId(listaOsob);
    int wielkoscWektora = listaOsob.size();
    char znakBezpieczenstwa;
    if(indeksUsuwanegoKontaktu==-1)
    {
        cout << "Nie znaleziono kontaktu o podanym ID";
        Sleep(1000);
        return wielkoscWektora;
    }
    cout << "Czy na pewno chcesz usunac kontakt? t/n ";
    cin >> znakBezpieczenstwa;
    if(znakBezpieczenstwa=='t')
    {

        for(int i=indeksUsuwanegoKontaktu; i<wielkoscWektora-1; i++)
        {
            listaOsob[i].id=listaOsob[i+1].id;
            listaOsob[i].imie=listaOsob[i+1].imie;
            listaOsob[i].nazwisko=listaOsob[i+1].nazwisko;
            listaOsob[i].email=listaOsob[i+1].email;
            listaOsob[i].adres=listaOsob[i+1].adres;
            listaOsob[i].numerTelefonu=listaOsob[i+1].numerTelefonu;
        }
        listaOsob.pop_back();
        wielkoscWektora = listaOsob.size();
        cout<< "Kontakt zostal usuniety"<<endl;
        system("pause");
        return wielkoscWektora;
    }
    else if (znakBezpieczenstwa =='n')
    {
        cout << "Kontakt nie zostal usuniety";
        Sleep(1000);
        return wielkoscWektora;
    }
    else
    {
        cout << "Nierozpoznany znak, prosze sie zdecydowac";
        Sleep(1000);
        return wielkoscWektora;
    }

}

void modyfikowanieKontaktu(vector <Kontakt> &listaOsob)
{
    char wybor;
    int indeksEdytowanegoKontaktu;
    indeksEdytowanegoKontaktu = wyszukiwanieKontaktuPoId(listaOsob);

    if (indeksEdytowanegoKontaktu==-1)
    {
        cout << "Nie ma takiego kontaktu"<<endl;
        Sleep(600);
    }
    else
    {
        while(true)
        {
            system("cls");
            cout << "Co chesz edytowac? "<<endl;
            cout << "1. Imie"<<endl;
            cout << "2. Nazwisko"<<endl;
            cout << "3. Numer telefonu"<<endl;
            cout << "4. email"<<endl;
            cout << "5. Adres"<<endl;
            cout << "9. powrot do menu"<<endl;
            cin >> wybor;

            switch(wybor)
            {
            case '1':
            {
                string noweImie="";
                cout << "Podaj nowe dane: ";
                cin >> noweImie;
                listaOsob[indeksEdytowanegoKontaktu].imie = noweImie;
                cout << "Kontakt zostal zmodyfikowany";
                aktualizujPlik(listaOsob);
                Sleep(500);
                break;
            }
            case '2':
            {
                string noweNazwisko="";
                cout << "Podaj nowe dane: ";
                cin >> noweNazwisko;
                listaOsob[indeksEdytowanegoKontaktu].nazwisko = noweNazwisko;
                cout << "Kontakt zostal zmodyfikowany";
                aktualizujPlik(listaOsob);
                Sleep(500);
                break;
            }
            case '3':
            {
                string nowyNumerTelefonu="";
                cout << "Podaj nowe dane: ";
                cin >> nowyNumerTelefonu;
                listaOsob[indeksEdytowanegoKontaktu].numerTelefonu = nowyNumerTelefonu;
                cout << "Kontakt zostal zmodyfikowany";
                aktualizujPlik(listaOsob);
                Sleep(500);
                break;
            }
            case '4':
            {
                string nowyEmail="";
                cout << "Podaj nowe dane: ";
                cin >> nowyEmail;
                listaOsob[indeksEdytowanegoKontaktu].email = nowyEmail;
                cout << "Kontakt zostal zmodyfikowany";
                aktualizujPlik(listaOsob);
                Sleep(500);
                break;
            }
            case '5':
            {
                string bowyAdres="";
                cout << "Podaj nowe dane: ";
                cin >> bowyAdres;
                listaOsob[indeksEdytowanegoKontaktu].adres = bowyAdres;
                cout << "Kontakt zostal zmodyfikowany";
                aktualizujPlik(listaOsob);
                Sleep(500);
                break;
            }
            case '9':
            {
                return;
            }
            }

        }
    }
}

void wyszukiwanieKontaktuWKsiazce(vector <Kontakt> &listaOsob)
{
    system("cls");

    int indeksKontaktu=-1;
    indeksKontaktu=wyszukiwanieKontaktuPoId(listaOsob);

    if (indeksKontaktu==-1)
    {
        cout << "Nie ma takiego kontaktu"<<endl;
        system("pause");
    }
    else
    {
        cout << "Dane kontaktu: "<<endl;
        cout << listaOsob[indeksKontaktu].id<<" "<<listaOsob[indeksKontaktu].imie<<" "<<listaOsob[indeksKontaktu].nazwisko<<endl;
        system("pause");
    }
}
int main()
{

    vector <Kontakt> listaOsob;
    int liczbaKontaktow=0;

    liczbaKontaktow = policzLiczbeKontaktow();

    wczytywanieWszystkichKontaktowZPliku(listaOsob,liczbaKontaktow);

  char wybor;

    while(true)
    {
        system("cls");
        cout << "Wybierz opcje: "<<endl;
        cout << "1. Dodaj nowy kontakt"<<endl;
        cout << "2. Wyszukaj kontaktu po imieniu"<<endl;
        cout << "3. Wyszukaj kontaktu po naziwsku"<<endl;
        cout << "4. Wyswietl wszytkie kontakty"<<endl;
        cout << "5. Modyfikacja"<<endl;
        cout << "6. Usuwanie kontaktu"<<endl;
        cout << "9. Zakoncz dzialanie programu"<<endl;
        cin >> wybor;

        switch(wybor)
        {
        case '1':
        {
            dodajNowy(listaOsob);
            liczbaKontaktow++;
            cout << "Kontakt zostal dodany";
            Sleep(500);
            aktualizujPlik(listaOsob);
            break;
        }
        case '2':
        {
            wyszukiwanieKontaktuPoImieniu(listaOsob);
            break;
        }
        case '3':
        {
            wyszukiwanieKontaktuPoNazwisku(listaOsob);
            break;
        }
        case '4':
        {
            wyswietlanieWszystkichKontaktow(listaOsob);
            break;
        }
          case '5':
        {
            modyfikowanieKontaktu(listaOsob);
            break;
        }
            case '6':
        {
            liczbaKontaktow = usuwanieKontaktu(listaOsob);
            aktualizujPlik(listaOsob);
            break;
        }
        case '9':
        {
            aktualizujPlik(listaOsob);
            exit(0);
            break;
        }
        }

    }
    return 0;
}
