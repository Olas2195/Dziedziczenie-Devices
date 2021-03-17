#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

struct Telefon {
	string aparat;
};

struct Laptop{
	string dysk;
	string karta_graf;
};

struct Device:public Laptop, public Telefon {
	string typ;
	string nazwa;
	string ram;
	string procesor;	
};

class operacje {
	vector <Device> spis;
	vector <string> json;
	
	public:
		void wczytaj();
		void wyszukaj();
		void dodaj();
		void zapisJson();		
		void zapisz();
};

void operacje::wczytaj() {
	ifstream plik1;
	struct Device wprowadzany;
	
	plik1.open("we.txt");
	if(plik1.good())
		while(!plik1.eof()) {
			getline(plik1, wprowadzany.typ);
			getline(plik1, wprowadzany.nazwa);
			getline(plik1, wprowadzany.ram);
			getline(plik1, wprowadzany.procesor);
			
			if(wprowadzany.typ=="Telefon") {
				getline(plik1, wprowadzany.aparat);
			}
			
			if(wprowadzany.typ=="Laptop") {
				getline(plik1, wprowadzany.dysk);
				getline(plik1, wprowadzany.karta_graf);
			}
			
			spis.push_back(wprowadzany);	
		}
	cout<<"Wczytywanie z pliku powiodlo sie!\n\n";	
	plik1.close();
}

void operacje::wyszukaj() {
	int x=0;
	string szukane;	
	cout<<"Jakiego urzadzenia szukasz? (nazwa)\n";
	cin>>szukane;
	
	for (vector<Device>::iterator it = spis.begin(); it != spis.end(); ++it) {
		int pozycja = it->nazwa.find(szukane);
		if(pozycja!=string::npos) {
			x++;
			cout<<"Nazwa: "<<it->nazwa<<"\n"
				<<"RAM: "<<it->ram<<"\n"
				<<"Procesor: "<<it->procesor<<"\n";
			if(it->typ == "Telefon")
				cout<<"Aparat: "<<it->aparat<<"\n\n";
			if(it->typ == "Laptop")	{
				cout<<"Dysk: "<<it->dysk<<"\n"
					<<"Karta graficzna: "<<it->karta_graf<<"\n\n";
			}
		}
	}
	
	if(x==0) {
		cout<<"Nie ma zadnego dopasowania\n\n";
	}
}

void operacje::dodaj() {
	struct Device wprowadzany;
	int n;
	regex wzor("^[A-Z]{1}(.*)$");	
		
	cout<<"Jakie urzqdzenie chcesz dodac?\n"
		<<"1. Telefon\n"
		<<"2. Laptop\n\n";
		
	do {
		cin>>n;
		if (n!=1 && n!=2) {
			cout<<"Bledny wybor!\n\n";
		}		
	}while(n!=1 && n!=2);
	
	do {
		cout<<"Nazwa: ";
		cin>>wprowadzany.nazwa;
		if(!regex_match(wprowadzany.nazwa, wzor)) {
			cout<<"Nieprawidlowa nazwa\n (Nazwa powinna zaczynac sie od wielkiej litery)\n\n";
		}
	}while(!regex_match(wprowadzany.nazwa, wzor));

	cout<<"RAM: ";
	cin>>wprowadzany.ram;
	cout<<"Procesor: ";
	cin>>wprowadzany.procesor;
	
	switch (n) {
		case 1:
			wprowadzany.typ = "Telefon";
			cout<<"Aparat: ";
			cin>>wprowadzany.aparat;
			break;
			
		case 2:
			wprowadzany.typ = "Laptop";
			cout<<"Dysk: ";
			cin>>wprowadzany.dysk;
			cout<<"Karta graficzna: ";
			cin>>wprowadzany.karta_graf;			
			break;
	}
	
	spis.push_back(wprowadzany);
	cout<<"Wprowadzono!\n\n";	
}

void operacje::zapisJson() {
	string nowe;
    for (vector<Device>::iterator it = spis.begin(); it != spis.end(); ++it)
    {
    	if(it->typ == "Telefon")
    		nowe = "{\"nazwa\":"+it->nazwa+",\"ram\":"+it->ram+",\"procesor\":"+it->procesor+",\"aparat\":"+it->aparat+"},\n";
		if(it->typ == "Laptop")
			nowe = "{\"nazwa\":"+it->nazwa+",\"ram\":"+it->ram+",\"procesor\":"+it->procesor+",\"dysk\":"+it->dysk+",\"karta graficzna\":"+it->karta_graf+"},\n";
		json.push_back(nowe);
    }
    cout<<"Zapisano jako JASON!\n\n";
}

void operacje::zapisz() {
	ofstream plik2;
	plik2.open("wy.txt");
	plik2<<"[\n";
	for (int i = 0; i < json.size(); i++) {
    	plik2<<json[i];
	}
	plik2<<"]";
	plik2.close();
	
	cout<<"Zapisano do pliku!\n\n";
}


int main(int argc, char** argv) {
	operacje o1;
	int wybor;
	
	cout<<"Menu:\n"
		<<"1. Wczytaj\n"
		<<"2. Wyszukaj\n"
		<<"3. Dodaj\n"
		<<"4. Zapisz jako JSON\n"
		<<"5. Zapisz do pliku (jako JSON)\n"
		<<"0. Koniec\n\n";
		
	do {
		cin>>wybor;
		
		switch(wybor) {
			case 1:
				o1.wczytaj();
				break;
			case 2:
				o1.wyszukaj();
				break;
			case 3:
				o1.dodaj();
				break;
			case 4:
				o1.zapisJson();
				break;
			case 5:
				o1.zapisz();
				break;
			case 0:	
				cout<<"Dziekuje!";
				break;
			default:
				cout<<"Bledny wybor!\n";
				break;
		}
	}while(wybor!=0);
	
	return 0;
}
