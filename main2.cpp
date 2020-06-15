#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

class Device {
	public: 	
		string typ;
		string nazwa;
		string ram;
		string procesor;
			
		virtual void wyswietl() = 0;
		virtual string wpis(string przed_) = 0;
};

class Telefon:public Device {	
	public:
		string aparat;
		
		Telefon(string typ_, string nazwa_, string ram_, string procesor_, string aparat_) {
			typ = typ_;
			nazwa = nazwa_;
			ram = ram_;
			procesor = procesor_;
			aparat = aparat_;
		}
		
		void wyswietl() {
			cout<<"Aparat: "<<aparat<<"\n\n";			
		}
		string wpis(string przed_) {
			return aparat;
		}
};

class Laptop:public Device{
	string dysk;
	string karta_graf;
	
	public:
		Laptop(string typ_, string nazwa_, string ram_, string procesor_, string dysk_, string karta_graf_) {
			typ = typ_;
			nazwa = nazwa_;
			ram = ram_;
			procesor = procesor_;
			dysk = dysk_;
			karta_graf = karta_graf_;
		}
			
		void wyswietl() {
			cout<<"Dysk: "<<dysk<<"\n";
			cout<<"Karta graficzna: "<<karta_graf<<"\n\n";			
		}	
		string wpis(string przed_) {
			if(przed_=="dysk")
				return dysk;				
			if(przed_=="karta_graf")
				return karta_graf;
		}
};



class Kolekcja {
	vector <Device*> spis;
	vector <string> json;
	
	public:
		void wczytaj();
		void wyszukaj();
		void dodaj();
		void zapisJson();		
		void zapisz();
};

void Kolekcja::wczytaj() {
	ifstream plik1;	
	plik1.open("we.txt");
	if(plik1.good())
		while(!plik1.eof()) {
			string typ, nazwa, ram, procesor;
			getline(plik1, typ);
			getline(plik1, nazwa);
			getline(plik1, ram);
			getline(plik1, procesor);
			
			if(typ=="Telefon") {
				string aparat;
				getline(plik1, aparat);
				spis.push_back(new Telefon(typ, nazwa, ram, procesor, aparat));		
			}
			
			if(typ=="Laptop") {
				string dysk, karta_graf;
				getline(plik1, dysk);
				getline(plik1, karta_graf);
				spis.push_back(new Laptop(typ, nazwa, ram, procesor, dysk, karta_graf));	
			}
		}
	cout<<"Wczytywanie z pliku powiodlo sie!\n\n";
}

void Kolekcja::wyszukaj() {
	int x=0;
	string szukane;	
	cout<<"Jakiego urzadzenia szukasz? (nazwa)\n";
	cin>>szukane;
	
	for (vector<Device*>::iterator it = spis.begin(); it != spis.end(); ++it) {
		int pozycja = (*it)->nazwa.find(szukane);
		if(pozycja!=string::npos) {
			x++;
			cout<<"Nazwa: "<<(*it)->nazwa<<"\n"
				<<"RAM: "<<(*it)->ram<<"\n"
				<<"Procesor: "<<(*it)->procesor<<"\n";
			if((*it)->typ == "Telefon")
				(*it)->wyswietl();
			if((*it)->typ == "Laptop")
				(*it)->wyswietl();
		}
	}
	if(x==0) {
			cout<<"Nie ma zadnego dopasowania\n\n";
	}

}

void Kolekcja::dodaj() {
	int n;
	string typ, nazwa, ram, procesor;	
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
		cin>>nazwa;
		if(!regex_match(nazwa, wzor)) {
			cout<<"Nieprawidlowa nazwa\n (Nazwa powinna zaczynac sie od wielkiej litery)\n\n";
		}
	}while(!regex_match(nazwa, wzor));

	cout<<"RAM: ";
	cin>>ram;
	cout<<"Procesor: ";
	cin>>procesor;
	
	switch (n) {
		case 1: {
			string aparat;
			typ = "Telefon";
			cout<<"Aparat: ";
			cin>>aparat;
			spis.push_back(new Telefon(typ, nazwa, ram, procesor, aparat));	
			break;
		}
			
		case 2: {
			string dysk, karta_graf;
			typ = "Laptop";
			cout<<"Dysk: ";
			cin>>dysk;
			cout<<"Karta graficzna: ";
			cin>>karta_graf;
			spis.push_back(new Laptop(typ, nazwa, ram, procesor, dysk, karta_graf));		
			break;
		}
	}
	cout<<"Wprowadzono!\n\n";	
}

void Kolekcja::zapisJson() {
	string nowe;
    for (vector<Device*>::iterator it = spis.begin(); it != spis.end(); ++it)
    {
    	if((*it)->typ == "Telefon")
    		nowe = "{\"nazwa\":"+(*it)->nazwa+",\"ram\":"+(*it)->ram+",\"procesor\":"+(*it)->procesor+",\"aparat\":"+(*it)->wpis("aparat")+"},\n";
		if((*it)->typ == "Laptop")
			nowe = "{\"nazwa\":"+(*it)->nazwa+",\"ram\":"+(*it)->ram+",\"procesor\":"+(*it)->procesor+",\"dysk\":"+(*it)->wpis("dysk")+",\"karta graficzna\":"+(*it)->wpis("karta_graf")+"},\n";
		json.push_back(nowe);
    }
    cout<<"Zapisano jako JASON!\n\n";
}

void Kolekcja::zapisz() {
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
	Kolekcja k1;
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
				k1.wczytaj();
				break;
			case 2:
				k1.wyszukaj();
				break;
			case 3:
				k1.dodaj();
				break;
			case 4:
				k1.zapisJson();
				break;
			case 5:
				k1.zapisz();
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
