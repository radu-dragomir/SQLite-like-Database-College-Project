#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<algorithm>
#include<vector>
#include<filesystem>
using namespace std;

class InvalidCommandException {
	string mesaj = "Comanda necunoscuta";
public:
	string getMesaj() {
		return mesaj;
	}
};

class Coloana {
	string valoareImplicita;
	string numeColoana;
	string tipData;
	int dimensiune;
	vector<string> valoare;
public:
	string getValoareImplicita() {
		return valoareImplicita;
	}
	string getNumeColoana() {
		return numeColoana;
	}
	string getTipData() {
		return tipData;
	}
	int getDimensiune() {
		return dimensiune;
	}
	vector<string> getValoare() {
		return valoare;
	}
	string getValoareIndex(int index) {
		return valoare[index];
	}
	void setValoareImplicita(string val) {
		valoareImplicita = val;
	}
	void setNumeColoana(string nume) {
		if (nume.length() > 0)
			numeColoana = nume;
	}
	void setTipData(string tip) {
		if (tip.length() > 0)
			tipData = tip;
	}
	void setDimensiune(int dim) {
		if (dim > 0)
			dimensiune = dim;
	}
	void setValoare(vector<string> val) {
		valoare = val;
	}
	void setValoareIndex(string val, int index) {
		if (val.length() > 0)
			valoare[index] = val;
	}
	void adaugareValoare(string val) {
		valoare.push_back(val);
	}
	void insertValoareImplicita() {
		valoare.push_back(valoareImplicita);
	}
	Coloana() {
		numeColoana = "Nume coloana";
		tipData = "integer";
		dimensiune = 0;
		valoareImplicita = "0";
	}
	Coloana(string nume, string tip, int dim, vector<string> val, string valImplicita) {
		numeColoana = nume;
		tipData = tip;
		dimensiune = dim;
		valoare = val;
		valoareImplicita = valImplicita;
	}
	Coloana(const Coloana& c) {
		numeColoana = c.numeColoana;
		tipData = c.tipData;
		dimensiune = c.dimensiune;
		valoare = c.valoare;
		valoareImplicita = c.valoareImplicita;
	}
	Coloana& operator=(const Coloana& c) {
		numeColoana = c.numeColoana;
		tipData = c.tipData;
		dimensiune = c.dimensiune;
		valoare = c.valoare;
		valoareImplicita = c.valoareImplicita;
		return *this;
	}
	friend istream& operator>>(istream& in, Coloana& c) {
		cout << "Numele coloanei:";
		in >> c.numeColoana;
		for (int i = 0; i < c.valoare.size(); ++i) {
			cout << "Tipul de data(text/integer/float):";
			in >> c.tipData;
			cout << " Dimensiunea:";
			in >> c.dimensiune;
			cout << "Valoaree: ";
			in >> c.valoare[i];
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, Coloana c) {
		out << "Numele coloanei: " << c.getNumeColoana() << endl;
		out << "Tipul de data: " << c.getTipData() << endl;
		out << "Dimensiunea: " << c.getDimensiune() << endl;
		for (int i = 0; i < c.valoare.size(); ++i) {
			out << "Valoare: " << c.getValoareIndex(i) << endl;
		}
		return out;
	}
};

class Tabel {
	string numeTabel;
	vector<Coloana> coloane;
	static int nrTabele;
public:
	string getNumeTabel() {
		return numeTabel;
	}
	vector<Coloana> getColoane() {
		return coloane;
	}
	void setNumeTabel(string nume) {
		if (nume.length() > 0)
			numeTabel = nume;
	}
	void setColoane(vector<Coloana> col) {
		coloane = col;
	}
	void setColoaneIndex(Coloana col, int index) {
		coloane[index] = col;
	}
	Tabel() {
		numeTabel = "Tabel";
		nrTabele++;
	}
	Tabel(string nume, int nrCol, vector<Coloana> col) {
		numeTabel = nume;
		coloane = col;
		nrTabele++;
	}
	Tabel(const Tabel& t) {
		numeTabel = t.numeTabel;
		coloane = t.coloane;
		nrTabele++;
	}
	~Tabel() {
		--nrTabele;
	}
	Tabel& operator=(const Tabel& t) {
		numeTabel = t.numeTabel;
		coloane = t.coloane;
		return *this;
	}
	friend istream& operator>>(istream& in, Tabel& t) {
		cout << " Nume tabel: ";
		in >> t.numeTabel;
		cout << " Numar coloane: ";
		int nrColoane;
		in >> nrColoane;
		for (int i = 0; i < nrColoane; i++) {
			cout << "Date coloana " << i + 1 << endl;
			in >> t.coloane[i];
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, Tabel t) {
		out << "Nume tabel: " << t.getNumeTabel() << endl;
		out << "Numar coloane: " << t.coloane.size() << endl;
		for (int i = 0; i < t.coloane.size(); i++) {
			out << "Coloana " << i + 1 << endl;
			out << t.coloane[i];
		}
		return out;
	}
	Coloana& operator[] (int i) {
		if (i < coloane.size() && i >= 0) {
			return coloane[i];
		}
		cout << "Coloana invalida";
		exit(-1);
	}
	bool operator!() {
		return !coloane.size();
	}
	bool operator >= (Tabel& t) {
		return this->coloane.size() >= t.coloane.size();
	}
	bool operator==(Tabel& t) {
		return this->coloane.size() == t.coloane.size();
	}
	explicit operator int() {
		return coloane.size();
	}
	explicit operator string() {
		return numeTabel;
	}
};
int Tabel::nrTabele = 0;

class BazaDeDate;

class Comanda {
	string cod;
	string textComanda;

public:
	string getTextComanda() {
		return textComanda;
	}
	string getCod() {
		return cod;
	}
	void setTextComanda(string comanda) {
		if (comanda.length() > 0)
			textComanda = comanda;
		else {
			textComanda = "";
		}
	}
	void setCod() {
		if (textComanda == "") {
			cod = "ERR";
			cout << "Comenzile acceptate sunt:" << endl << "- CREATE" << endl << "- DROP" << endl << "- DISPLAY" << endl << "- INSERT" << endl << "- DELETE" << endl << "- SELECT" << endl << "- UPDATE" << endl;
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 6) == "CREATE") {
			cod = "CREATE";
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 4) == "DROP") {
			cod = "DROP";
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 7) == "DISPLAY") {
			cod = "DISPLAY";
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 6) == "INSERT") {
			cod = "INSERT";
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 6) == "DELETE") {
			cod = "DELETE";
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 6) == "SELECT") {
			cod = "SELECT";
		}
		else if (textComanda.substr(textComanda.find_first_not_of(" "), 6) == "UPDATE") {
			cod = "UPDATE";
		}
		else if (textComanda == "EXIT") {
			cod = "EXIT";
			cout << "Program incheiat" << endl;
		}
		else {
			try {
				cod = "ERR";
				throw InvalidCommandException();
			}
			catch (InvalidCommandException err) {
				cout << err.getMesaj() << endl;
			}
			cout << "Comenzile acceptate sunt:" << endl << "- CREATE" << endl << "- DROP" << endl << "- DISPLAY" << endl << "- INSERT" << endl << "- DELETE" << endl << "- SELECT" << endl << "- UPDATE" << endl << "- EXIT" << endl;
		}
	}
	Comanda() {
		cod = "NEW";
		textComanda = " ";
	}
	Comanda(string text) {
		textComanda = text;
		setCod();
	}
	Comanda(const Comanda& c) {
		cod = c.cod;
		textComanda = c.textComanda;
	}
	//~Comanda() {

	//}
	bool sintaxaCorecta() {
		if (cod == "CREATE") {
			regex reg1("(\\s*)CREATE(\\s+)TABLE(\\s+)[[:w:]]+(\\s*)\\((\\s*)[[:w:]]+(\\s*),(\\s*)(text|integer|float)(\\s*),(\\s*)[[:digit:]]+(\\s*),(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*)\\)");
			regex reg2("(\\s*)CREATE(\\s+)TABLE(\\s+)[[:w:]]+(\\s*)\\((\\s*)(\\((\\s*)[[:w:]]+(\\s*),(\\s*)(text|integer|float)(\\s*),(\\s*)[[:digit:]]+(\\s*),(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*)\\)(\\s*),(\\s*))*(\\s*)\\((\\s*)[[:w:]]+(\\s*),(\\s*)(text|integer|float)(\\s*),(\\s*)[[:digit:]]+(\\s*),(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*)\\)(\\s*)\\)(\\s*)");
			if ((regex_match(textComanda, reg1) || regex_match(textComanda, reg2)) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "CREATE TABLE nume_tabel ((nume_coloana_1, tip[text/float/integer], dimensiune[number], valoare_implicita), (nume_coloana_2, tip[text/float/integer], dimensiune[number], valoare_implicita), ...)" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg1) || regex_match(textComanda, reg2);
		}
		else if (cod == "DROP") {
			regex reg("(\\s*)DROP(\\s+)TABLE(\\s+)[[:w:]]+(\\s*)");
			if (regex_match(textComanda, reg) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "DROP TABLE table_name" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg);
		}
		else if (cod == "DISPLAY") {
			regex reg("(\\s*)DISPLAY(\\s+)TABLE(\\s+)[[:w:]]+(\\s*)");
			if (regex_match(textComanda, reg) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "DISPLAY TABLE table_name" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg);
		}
		else if (cod == "INSERT") {
			regex reg("(\\s*)INSERT(\\s+)INTO(\\s+)[[:w:]]+(\\s+)VALUES(\\s*)\\(((\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*),(\\s*))*([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*)\\)(\\s*)");
			if (regex_match(textComanda, reg) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "INSERT INTO nume_tabela VALUES(val1, val2, val3, ...)" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg);
		}
		else if (cod == "DELETE") {
			regex reg("(\\s*)DELETE(\\s+)FROM(\\s+)[[:w:]]+(\\s+)WHERE(\\s+)[[:w:]]+(\\s*)=(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*)");
			if (regex_match(textComanda, reg) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "DELETE FROM nume_tabela WHERE nume_coloana = valoare" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg);
		}
		else if (cod == "SELECT") {
			regex reg("(\\s*)SELECT((\\s*)\\((\\s*)((\\s*)[[:w:]]+(\\s*),(\\s*))*(\\s*)[[:w:]]+(\\s*)\\)|(\\s+)ALL)(\\s+)FROM(\\s+)[[:w:]]+(\\s*)((\\s+)WHERE(\\s+)[[:w:]]+(\\s*)=(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*))?(\\s*)");
			if (regex_match(textComanda, reg) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "SELECT (cel_putin_o_coloana, ...) | ALL FROM nume_tabela [WHERE valoare_coloana = valoare]" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg);
		}
		else if (cod == "UPDATE") {
			regex reg("(\\s*)UPDATE(\\s+)[[:w:]]+(\\s+)SET(\\s+)[[:w:]]+(\\s*)=(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s+)WHERE(\\s+)[[:w:]]+(\\s*)=(\\s*)([+-]?([[:digit:]]+[.])?[[:digit:]]+|[[:w:]]+)(\\s*)");
			if (regex_match(textComanda, reg) == 0) {
				cout << "Sintaxa gresita. Sintaxa corecta are forma:" << endl;
				cout << "UPDATE nume_tabela SET nume_coloana = valoare WHERE nume_coloana = valoare" << endl;
				return false;
			}
			else {
				return true;
			}
			//return regex_match(textComanda, reg);
		}

	}
	void implementareComanda(BazaDeDate&);

	void CREATE(BazaDeDate&);

	void DROP(BazaDeDate&);

	void DISPLAY(BazaDeDate&);

	void INSERT(BazaDeDate&);

	void DELETE(BazaDeDate&);

	void SELECT(BazaDeDate&);

	void UPDATE(BazaDeDate&);

	void eliminareSpatii(string& string) {
		string = string.substr(string.find_first_not_of(" "), (string.find_last_not_of(" ") - string.find_first_not_of(" ") + 1));
	}

	vector<string> tokenize(string str, const regex re) {
		regex_token_iterator<string::iterator> it(str.begin(), str.end(), re, -1);
		vector<string> tokenized(it, {});
		return tokenized;
	}

	Comanda& operator=(const Comanda& c) {
		cod = c.cod;
		textComanda = c.textComanda;
		return *this;
	}
	friend istream& operator>>(istream& in, Comanda& c) {
		cout << "Comanda: ";
		getline(in, c.textComanda);
		c.setCod();
		return in;
	}
	friend ostream& operator<<(ostream& out, Comanda c) {
		out << "Codul comenzii: " << c.getCod() << endl;
		out << "Comanda: " << c.getTextComanda() << endl;
		return out;
	}
	explicit operator string() {
		return textComanda;
	}
};

class Fisier
{
private:
public:
	void exportDateTabele(BazaDeDate&);
	void importDateTabele(BazaDeDate&);
	void exportInregistrariTabele(BazaDeDate&);
	void exportDisplay(Tabel);
	void dropDisplay();
	void dropSelect();
};

class BazaDeDate {
	vector<Tabel> tabele;
	char* numeBD;
	float versiune;
	const string* autori;
public:
	vector<Tabel>& getTabele() {
		return tabele;
	}
	const char* getNume() {
		return numeBD;
	}
	float getVersiune() {
		return versiune;
	}
	string getAutor(int i) {
		return autori[i];
	}
	void setTabel(Tabel t, int index) {
		this->tabele[index] = t;
	}
	void setTabele(vector<Tabel> t) {
		this->tabele = t;
	}
	void setNume(const char* nume) {
		if (strlen(nume) > 0) {
			if (numeBD != NULL) {
				delete[]numeBD;
			}
			numeBD = new char[strlen(nume) + 1];
			strcpy_s(numeBD, strlen(nume) + 1, nume);
		}
	}
	void setVersiune(float v) {
		if (v > 1)
			versiune = v;
	}
	void adaugareTabel(Tabel t) {
		tabele.push_back(t);
	}
	int isTable(string nume) {
		bool found = false;
		int indexTable = -1;
		for (int i = 0; i < tabele.size(); ++i)
			if (tabele[i].getNumeTabel() == nume) {
				found = true;
				indexTable = i;
				break;
			}
		return indexTable;
	}
	BazaDeDate() : autori(new string[3]{ "Dragomir Radu", "Druta Adrian","Dura Ioan Tudor" }) {
		numeBD = new char[strlen("The Best C-based Database Ever Created") + 1];
		strcpy_s(numeBD, strlen("The Best C-based Database Ever Created") + 1, "The Best C-based Database Ever Created");
		versiune = 1.0;
	}
	BazaDeDate(const char* nume, float v) : autori(new string[3]{ "Dragomir Radu", "Druta Adrian","Dura Ioan Tudor" }) {
		numeBD = new char[strlen(nume) + 1];
		strcpy_s(numeBD, strlen(nume) + 1, nume);
		versiune = v;
	}
	BazaDeDate(const BazaDeDate& b) :autori(b.autori) {
		numeBD = new char[strlen(b.numeBD) + 1];
		strcpy_s(numeBD, strlen(b.numeBD) + 1, b.numeBD);
		versiune = b.versiune;
	}
	~BazaDeDate() {
		if (this->autori != nullptr) {
			delete[]this->autori;
		}
		this->autori = nullptr;
		if (this->numeBD != nullptr) {
			delete[]this->numeBD;
		}
		this->numeBD = nullptr;
	}

	void startAppFile(char* argv) {
		ifstream g;
		g.open(argv, ios::in);
		Fisier f;
		f.dropSelect();
		f.dropDisplay();
		f.importDateTabele(*this);
		Comanda c;
		string s;
		while (!g.eof()) {
			getline(g, s);
			c.setTextComanda(s);
			c.setCod();
			if (c.sintaxaCorecta())
				c.implementareComanda(*this);
			cout << endl;
		}
		g.close();
	}

	void startApp() {
		Fisier f;
		f.dropSelect();
		f.dropDisplay();
		f.importDateTabele(*this);
		Comanda c;
		while (c.getTextComanda() != "EXIT") {
			cout << "Introduceti comanda:" << endl;
			string comanda;
			getline(cin, comanda);
			c.setTextComanda(comanda);
			c.setCod();
			if (c.sintaxaCorecta())
				c.implementareComanda(*this);
			cout << endl;
		}
		if (c.getTextComanda() == "EXIT") {
			f.exportDateTabele(*this);
			f.exportInregistrariTabele(*this);
			cout << "Program incheiat";
			exit(0);
		}
	}
	BazaDeDate& operator=(const BazaDeDate& b) {
		if (numeBD != nullptr) {
			delete[]numeBD;
		}
		this->numeBD = new char[strlen(b.numeBD) + 1];
		strcpy_s(this->numeBD, strlen(b.numeBD) + 1, b.numeBD);
		this->versiune = b.versiune;
		return *this;
	}
	friend istream& operator>>(istream& in, BazaDeDate& b) {
		cout << "Numele bazei de date:";
		char buffer[30];
		in.get(buffer, 30);
		if (b.numeBD) {
			delete[]b.numeBD;
		}
		b.numeBD = new char[strlen(buffer) + 1];
		strcpy_s(b.numeBD, strlen(buffer) + 1, buffer);
		cout << "Versiunea bazei de date:";
		in >> b.versiune;
		if (b.versiune < 1) {
			b.versiune = 1;
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, BazaDeDate b) {
		out << "Numele bazei de date: " << b.getNume() << endl;
		out << "Versiune: " << b.getVersiune() << endl;
		out << "Autori: ";
		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				out << b.getAutor(i);
			}
			else {
				out << b.getAutor(i) << ", ";
			}
		}
		out << endl << endl;
		return out;
	}
	explicit operator char* () {
		return numeBD;
	}
	explicit operator float() {
		return versiune;
	}
	BazaDeDate operator++() {
		versiune++;
		return *this;
	}
	BazaDeDate operator++(int i) {
		BazaDeDate copie = *this;
		versiune++;
		return copie;
	}
};

void Fisier::exportDateTabele(BazaDeDate& b) {
	ofstream tFileNames("NumeTabele.txt");
	vector<Tabel> tOutput = b.getTabele();
	for (int i = 0; i < tOutput.size(); ++i) {
		tFileNames << tOutput[i].getNumeTabel();
		if (i != tOutput.size() - 1)
			tFileNames << "\n";
		ofstream tFileName(tOutput[i].getNumeTabel() + ".txt");
		vector<Coloana> colTOutput = tOutput[i].getColoane();
		for (int j = 0; j < colTOutput.size(); ++j) {
			tFileName << colTOutput[j].getNumeColoana() << " ";
			tFileName << colTOutput[j].getTipData() << " ";
			tFileName << colTOutput[j].getDimensiune() << " ";
			tFileName << colTOutput[j].getValoareImplicita();
			if (j != colTOutput.size() - 1)
				tFileName << "\n";
		}
		tFileName.close();
	}
	tFileNames.close();
}

void Fisier::importDateTabele(BazaDeDate& b) {
	ifstream tFileNames("NumeTabele.txt");
	if (tFileNames.good()) {
		tFileNames.seekg(0, ios::end);
		if (tFileNames.tellg() != 0) {
			tFileNames.seekg(0, ios::beg);
			vector<string> tNames;
			while (!tFileNames.eof()) {
				string tempName;
				tFileNames >> tempName;
				tNames.push_back(tempName);
			}
			tFileNames.close();
			vector<Tabel> t;
			Tabel tTemp;
			for (int i = 0; i < tNames.size(); ++i) {
				Tabel tTemp;
				tTemp.setNumeTabel(tNames[i]);
				t.push_back(tTemp);
			}
			for (int i = 0; i < t.size(); ++i) {
				vector<Coloana> col;
				ifstream tFileName;
				tFileName.open(t[i].getNumeTabel() + ".txt");
				tFileName.seekg(0, ios::end);
				if (tFileName.tellg() != 0 && tFileName.good()) {
					tFileName.seekg(0, ios::beg);
					while (!tFileName.eof()) {
						Coloana colTemp;
						string tempNume;
						string tempTip;
						int tempDimensiune;
						string tempValImplicita;
						tFileName >> tempNume;
						tFileName >> tempTip;
						tFileName >> tempDimensiune;
						tFileName >> tempValImplicita;
						colTemp.setNumeColoana(tempNume);
						colTemp.setTipData(tempTip);
						colTemp.setDimensiune(tempDimensiune);
						colTemp.setValoareImplicita(tempValImplicita);
						col.push_back(colTemp);

					}
				}
				tFileName.close();
				t[i].setColoane(col);
			}
			for (int i = 0; i < t.size(); ++i) {
				ifstream colTOutput(t[i].getNumeTabel() + ".bin", ios::binary);
				streampos begin, end;
				begin = colTOutput.tellg();
				colTOutput.seekg(0, ios::end);
				end = colTOutput.tellg();
				streampos size = end - begin;
				int nrInreg = size / sizeof(string);
				if (colTOutput.good() && size != 0) {
					colTOutput.seekg(0, ios::beg);
					vector<Coloana> colTemp = t[i].getColoane();
					for (int j = 0; j < colTemp.size(); ++j) {
						vector<string> tempVal;
						for (int i = 0; i < nrInreg / colTemp.size(); ++i) {
							string* tempStr = new string;
							colTOutput.read((char*)tempStr, sizeof(string));
							tempVal.push_back(*tempStr);
						}
						colTemp[j].setValoare(tempVal);
					}
					t[i].setColoane(colTemp);
				}
				colTOutput.close();
			}
			b.setTabele(t);
		}
	}
}

void Fisier::exportInregistrariTabele(BazaDeDate& b) {
	vector<Tabel> tOutput = b.getTabele();
	for (int i = 0; i < tOutput.size(); ++i) {
		ofstream colTOutput(tOutput[i].getNumeTabel() + ".bin", ios::binary);
		vector<Coloana> colTemp = tOutput[i].getColoane();
		for (int j = 0; j < colTemp.size(); ++j) {
			vector<string> tempVal = colTemp[j].getValoare();
			if (tempVal.size() > 0)
				for (int k = 0; k < tempVal.size(); ++k)
					colTOutput.write((char*)&tempVal[k], sizeof(tempVal[k]));
		}
		colTOutput.close();
	}
}

void Fisier::exportDisplay(Tabel t) {
	static unsigned int i = 1;
	ofstream exportDisplay("DISPLAY_" + to_string(i++) + ".txt");
	exportDisplay << t;
	exportDisplay.close();
}

void Fisier::dropDisplay() {
	ifstream dropT;
	unsigned int i = 1;
	do
	{
		dropT.open("DISPLAY_" + to_string(i) + ".txt");
		if (dropT.fail())
			break;
		else {
			dropT.close();
			remove(("DISPLAY_" + to_string(i++) + ".txt").c_str());
		}
	} while (true);
}

void Fisier::dropSelect() {
	ifstream dropS;
	unsigned int i = 1;
	do
	{
		dropS.open("SELECT_" + to_string(i) + ".txt");
		if (dropS.fail())
			break;
		else {
			dropS.close();
			remove(("SELECT_" + to_string(i++) + ".txt").c_str());
		}
	} while (true);
}

void Comanda::CREATE(BazaDeDate& b) {
	string numeTabel;
	vector<string> tokens;
	const regex re(R"([|\s|,|(|)]+)");
	tokens = tokenize(textComanda, re);
	vector<Coloana> coloane;
	numeTabel = tokens[2];
	int steps = tokens.size() - 3;
	for (int i = 3; i < tokens.size(); ++i) {
		Coloana colTemp;
		colTemp.setNumeColoana(tokens[i]);
		++i;
		colTemp.setTipData(tokens[i]);
		++i;
		colTemp.setDimensiune(stoi(tokens[i]));
		++i;
		colTemp.setValoareImplicita(tokens[i]);
		coloane.push_back(colTemp);
	}
	Tabel t(numeTabel, (tokens.size() - 3) / 4, coloane);
	b.adaugareTabel(t);
}

void Comanda::INSERT(BazaDeDate& b) {
	string numeTabel;
	vector<string> tokens;
	const regex re(R"([|\s|,|(|)]+)");
	tokens = tokenize(textComanda, re);
	numeTabel = tokens[2];
	vector<string> valori;
	int nrValori = tokens.size() - 4;
	for (int i = 4; i < tokens.size(); ++i)
		valori.push_back(tokens[i]);
	int indexTable = b.isTable(numeTabel);
	if (indexTable != -1)
		if (b.getTabele()[indexTable].getColoane().size() != nrValori)
			cout << "Ati introdus un numar incorect de valori";
		else {
			Tabel t = b.getTabele()[indexTable];
			vector<Coloana> c = t.getColoane();
			for (int i = 0; i < nrValori; ++i)
				c[i].adaugareValoare(valori[i]);
			t.setNumeTabel(numeTabel);
			t.setColoane(c);
			b.setTabel(t, indexTable);
		}
	else cout << "Nu exista acest tabel";
}

void Comanda::DROP(BazaDeDate& b) {
	vector<Tabel> tabele = b.getTabele();
	string numeTabel;
	numeTabel = textComanda.substr(textComanda.find("TABLE") + 6, textComanda.length() - textComanda.find("TABLE") - 6);
	eliminareSpatii(numeTabel);
	int indexTable = b.isTable(numeTabel);
	if (indexTable != -1) {
		tabele.erase(tabele.begin() + indexTable);
		b.setTabele(tabele);
		remove((numeTabel + ".txt").c_str());
		remove((numeTabel + ".bin").c_str());
	}
	else
		cout << "Nu exista acest tabel";
}

void Comanda::DISPLAY(BazaDeDate& b) {
	string numeTabel;
	numeTabel = textComanda.substr(textComanda.find("TABLE") + 6, textComanda.length() - textComanda.find("TABLE") - 6);
	eliminareSpatii(numeTabel);
	int indexTable = b.isTable(numeTabel);
	if (indexTable != -1) {
		cout << b.getTabele()[indexTable];
		Fisier f;
		f.exportDisplay(b.getTabele()[indexTable]);
	}
	else
		cout << "Nu exista acest tabel";
}

void Comanda::DELETE(BazaDeDate& b) {
	string numeTabel;
	string numeColoana;
	string valoare;
	vector<string> tokens;
	const regex re(R"([|\s|,|(|)|=]+)");
	tokens = tokenize(textComanda, re);
	numeTabel = tokens[2];
	numeColoana = tokens[4];
	valoare = tokens[5];
	int indexTable = b.isTable(numeTabel);
	bool foundCol = false;
	int indexCol;
	if (indexTable != -1) {
		Tabel t = b.getTabele()[indexTable];
		vector<Coloana> c = t.getColoane();
		for (int i = 0; i < c.size(); ++i)
			if (numeColoana == c[i].getNumeColoana()) {
				foundCol = true;
				indexCol = i;
				break;
			}
		if (foundCol) {
			vector<int> indexes;
			vector<string> valoriFoundCol = c[indexCol].getValoare();
			for (int i = 0; i < valoriFoundCol.size(); ++i)
				if (valoriFoundCol[i] == valoare)
					indexes.push_back(i);
			for (int i = 0; i < c.size(); ++i) {
				vector<string> tempValori = c[i].getValoare();
				for (int j = 0; j < indexes.size(); ++j)
					tempValori.erase(tempValori.begin() + indexes[j]);
				c[i].setValoare(tempValori);
			}
			t.setColoane(c);
			b.setTabel(t, indexTable);
		}
		else
			cout << "Nu exista aceasta coloana";
	}
	else
		cout << "Nu exista acest tabel";
}

void Comanda::SELECT(BazaDeDate& b) {
	static unsigned int iSelect = 1;
	Fisier f;
	int nrColoane = 0;
	string numeTabel;
	string numeColoana;
	string valoare;
	vector<string> tokens;
	const regex re(R"([|\s|,|(|)|=]+)");
	tokens = tokenize(textComanda, re);
	if (textComanda.find("ALL") != string::npos)
		if (textComanda.find("WHERE") != string::npos) {
			numeTabel = tokens[3];
			numeColoana = tokens[5];
			valoare = tokens[6];
			int indexTable = b.isTable(numeTabel);
			if (indexTable != -1) {
				vector<Coloana> c = b.getTabele()[indexTable].getColoane();
				bool foundCol = false;
				int indexCol;
				for (int i = 0; i < c.size(); ++i)
					if (numeColoana == c[i].getNumeColoana()) {
						foundCol = true;
						indexCol = i;
						break;
					}
				if (foundCol) {
					ofstream exportSelect("SELECT_" + to_string(iSelect++) + ".txt");
					vector<int> indexes;
					vector<string> valoriFoundCol = c[indexCol].getValoare();
					for (int i = 0; i < valoriFoundCol.size(); ++i)
						if (valoriFoundCol[i] == valoare)
							indexes.push_back(i);
					for (int i = 0; i < c.size(); ++i) {
						cout << "Nume coloana: " << c[i].getNumeColoana() << "\n";
						exportSelect << "Nume coloana: " << c[i].getNumeColoana() << "\n";
						cout << "Tip coloana: " << c[i].getTipData() << "\n";
						exportSelect << "Tip coloana: " << c[i].getTipData() << "\n";
						cout << "Dimensiune coloana: " << c[i].getDimensiune() << "\n";
						exportSelect << "Dimensiune coloana: " << c[i].getDimensiune() << "\n";
						for (int j = 0; j < indexes.size(); ++j) {
							cout << "Valoare: " << c[i].getValoareIndex(indexes[j]) << "\n";
							exportSelect << "Valoare: " << c[i].getValoareIndex(indexes[j]) << "\n";
						}
					}
					exportSelect.close();
				}
				else
					cout << "Nu exista aceasta coloana";
			}
			else
				cout << "Nu exista acest tabel";
		}
		else {
			numeTabel = tokens.back();
			int indexTable = b.isTable(numeTabel);
			if (indexTable != -1) {
				ofstream exportSelect("SELECT_" + to_string(iSelect++) + ".txt");
				vector<Coloana> c = b.getTabele()[indexTable].getColoane();
				for (int i = 0; i < c.size(); ++i) {
					cout << c[i];
					exportSelect << c[i];
				}
				exportSelect.close();
			}
			else
				cout << "Nu exista acest tabel";
		}
	else
		if (textComanda.find("WHERE") != string::npos) {
			vector<string> numeColoane;
			for (int i = 1; i < tokens.size() - 5; ++i)
				numeColoane.push_back(tokens[i]);
			numeTabel = tokens[tokens.size() - 4];
			numeColoana = tokens[tokens.size() - 2];
			valoare = tokens.back();
			int indexTable = b.isTable(numeTabel);
			if (indexTable != -1) {
				if (nrColoane > b.getTabele()[indexTable].getColoane().size())
					cout << "Ati introdus un numar incorect de coloane";
				else {
					vector<Coloana> c = b.getTabele()[indexTable].getColoane();
					bool foundCol = false;
					int indexCol;
					for (int i = 0; i < c.size(); ++i)
						if (numeColoana == c[i].getNumeColoana()) {
							foundCol = true;
							indexCol = i;
							break;
						}
					if (foundCol) {
						ofstream exportSelect("SELECT_" + to_string(iSelect++) + ".txt");
						vector<int> colIndexes;
						for (int i = 0; i < numeColoane.size(); ++i)
							for (int j = 0; j < c.size(); ++j)
								if (c[j].getNumeColoana() == numeColoane[i])
									colIndexes.push_back(j);
						vector<int> indexes;
						vector<string> valoriFoundCol = c[indexCol].getValoare();
						for (int i = 0; i < valoriFoundCol.size(); ++i)
							if (valoriFoundCol[i] == valoare)
								indexes.push_back(i);
						for (int i = 0; i < colIndexes.size(); ++i) {
							cout << "Nume coloana: " << c[colIndexes[i]].getNumeColoana() << "\n";
							exportSelect<< "Nume coloana: " << c[colIndexes[i]].getNumeColoana() << "\n";
							cout << "Tip coloana: " << c[colIndexes[i]].getTipData() << "\n";
							exportSelect << "Tip coloana: " << c[colIndexes[i]].getTipData() << "\n";
							cout << "Dimensiune coloana: " << c[colIndexes[i]].getDimensiune() << "\n";
							exportSelect << "Dimensiune coloana: " << c[colIndexes[i]].getDimensiune() << "\n";
							for (int j = 0; j < indexes.size(); ++j) {
								cout << "Valoare: " << c[colIndexes[i]].getValoareIndex(indexes[j]) << "\n";
								exportSelect << "Valoare: " << c[colIndexes[i]].getValoareIndex(indexes[j]) << "\n";
							}
						}
						exportSelect.close();
					}
					else
						cout << "Nu exista aceasta coloana";
				}
			}
			else
				cout << "Nu exista acest tabel";
		}
		else {
			vector<string> numeColoane;
			for (int i = 1; i < tokens.size() - 2; ++i)
				numeColoane.push_back(tokens[i]);
			numeTabel = tokens.back();
			int indexTable = b.isTable(numeTabel);
			if (indexTable != -1) {
				if (nrColoane > b.getTabele()[indexTable].getColoane().size())
					cout << "Ati introdus un numar incorect de coloane";
				else {
					ofstream exportSelect("SELECT_" + to_string(iSelect++) + ".txt");
					vector<Coloana> c = b.getTabele()[indexTable].getColoane();
					vector<int> colIndexes;
					for (int i = 0; i < numeColoane.size(); ++i)
						for (int j = 0; j < c.size(); ++j)
							if (c[j].getNumeColoana() == numeColoane[i])
								colIndexes.push_back(j);
					for (int i = 0; i < colIndexes.size(); ++i) {
						cout << c[colIndexes[i]];
						exportSelect << c[colIndexes[i]];
					}
					exportSelect.close();
				}
			}
			else
				cout << "Nu exista acest tabel";
		}
}

void Comanda::UPDATE(BazaDeDate& b) {
	string numeTabel;
	string numeCol1;
	string numeCol2;
	string valCol1;
	string valCol2;
	vector<string> tokens;
	const regex re(R"([|\s|,|(|)|=]+)");
	tokens = tokenize(textComanda, re);
	numeTabel = tokens[1];
	numeCol1 = tokens[3];
	valCol1 = tokens[4];
	numeCol2 = tokens[6];
	valCol2 = tokens[7];
	int indexTable = b.isTable(numeTabel);
	if (indexTable != -1) {
		bool foundCol1 = false;
		bool foundCol2 = false;
		int indexCol1;
		int indexCol2;
		Tabel t = b.getTabele()[indexTable];
		vector<Coloana> c = t.getColoane();
		for (int i = 0; i < c.size(); ++i)
			if (c[i].getNumeColoana() == numeCol1) {
				foundCol1 = true;
				indexCol1 = i;
			}
		for (int i = 0; i < c.size(); ++i)
			if (c[i].getNumeColoana() == numeCol2) {
				foundCol2 = true;
				indexCol2 = i;
			}
		if (foundCol1) {
			if (foundCol2) {
				vector<int> colIndexes;
				vector<string> tempValori = c[indexCol2].getValoare();
				for (int i = 0; i < tempValori.size(); ++i)
					if (tempValori[i] == valCol2)
						colIndexes.push_back(i);
				for (int i = 0; i < colIndexes.size(); ++i)
					c[indexCol1].setValoareIndex(valCol1, colIndexes[i]);
			}
			else
				cout << "Coloana " << numeCol2 << " nu exista";
		}
		else cout << "Coloana " << numeCol1 << " nu exista";
		t.setColoane(c);
		b.setTabel(t, indexTable);
	}
	else cout << "Nu exista acest tabel";
}

void Comanda::implementareComanda(BazaDeDate& b) {
	if (cod == "CREATE") {
		CREATE(b);
	}
	else if (cod == "DROP") {
		DROP(b);
	}
	else if (cod == "DISPLAY") {
		DISPLAY(b);
	}
	else if (cod == "INSERT") {
		INSERT(b);
	}
	else if (cod == "DELETE") {
		DELETE(b);
	}
	else if (cod == "SELECT") {
		SELECT(b);
	}
	else if (cod == "UPDATE") {
		UPDATE(b);
	}
}

int main(int argc, char* argv[]){
	BazaDeDate b;
	cout << b;
	if (argc == 1) {
		b.startApp();
	}
	else
	{
		for (int i = 1; i <= argc && i <= 5; i++) {
			b.startAppFile(argv[i]);
		}
	}
}