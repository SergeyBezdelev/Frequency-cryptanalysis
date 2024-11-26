#include <windows.h>
#include <iostream>
#include <fstream >
#include <string>
using namespace std;

struct Frc {
	char c;
	double f;
};
// таблица букв и их частотность
Frc F[32] =
{
{'о',0.1097},
{'е',0.0871},
{'а',0.0946},
{'и',0.0630},
{'н',0.0655},
{'т',0.0515},
{'с',0.0430},
{'р',0.0435},
{'в',0.0470},
{'л',0.0525},
{'к',0.0335},
{'м',0.0245},
{'д',0.0300},
{'п',0.0240},
{'у',0.0285},
{'я',0.0255},
{'ы',0.0195},
{'ь',0.0165},
{'г',0.0195},
{'з',0.0215},
{'б',0.0159},
{'ч',0.0140},
{'й',0.0100},
{'х',0.0095},
{'ж',0.0070},
{'ш',0.0120},
{'ю',0.0080},
{'ц',0.0070},
{'щ',0.0050},
{'э',0.0040},
{'ф',0.0015},
{'ъ',0.0001}
};

const  char Azbuka[] = "абвгдежзийклмнопрстуфхцчшщъыьэюяабвгдежзийклмнопрстуфхцчшщъыьэюя";
const char Txt1[] = "Везде Толстой старается схватить стихийное, бессознательное начало человеческой жизни. Вся философия романа сводится к тому, что успех и неуспех в исторической жизни зависит не от воли и талантов отдельных людей, а от того, насколько они отражают в своей деятельности стихийную подкладку исторических событий.";
string s = "";
string cod, decod;
void Coder();
void Decoder();
int Menu();
int NumBukv(string str);
char Search(char x);
void AzBuk(int l);

int main(){
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		if (Menu() == -100) break;
		cout << "ОРИГИНАЛ" << endl << s << endl << endl;
		AzBuk(s.length());
		Coder();
		s.clear();
		Decoder();
		cod.clear();
		decod.clear();
	}
	system("pause");
	return 1;
};

void Coder() {
	cout << "ШИФРОВКА" << endl;

	char t = ' ';
	for (int i = 0; i < s.length(); i++) {
		t = s.at(i);
		if (t >= 'А' && t <= 'Я')	t = t + 32;//преобразование в строчную букву
		if (t >= 'а' && t <= 'я')	cod.push_back(Search(t));
		else	cod.push_back(t);
	}
	cout << cod << endl << endl;
}

void Decoder() {
	int l = cod.length(), fr1 = 0;
	char t = ' ';
	double count = 0, frequency = 0, min = 2, f;
	int NumBukvCod = NumBukv(cod);
	cout << "РАСШИФРОВКА" << endl;
	//перебор всех символов кода
	for (int i = 0; i < l; i++) {
		t = cod.at(i);
		//проверка что символ есть в азбуке
		bool flag = false;
		if (t >= 'а' && t <= 'я')
			flag = true;
		if (flag) {
			//подсчёт количества вхождений этого символа в тексте кода
			for (int j = 0; j < l; j++) {
				if (t == cod.at(j))
					count++;
			}
			//частота вхождений этого символа в тексте кода
			frequency = count / NumBukvCod;
			//поиск максимального совпадения частоты символа кода с частотой символа азбуки
			for (int fr = 0; fr < 33; fr++) {
				f = fabs(F[fr].f - frequency);
				if (f < min) {
					min = f;
					fr1 = fr;
				}
			}
			decod.push_back(F[fr1].c);
			fr1 = 0;
			count = 0;
			min = 2;
		}
		else
			decod.push_back(t);
	}
	cout << decod << endl << endl;
}

char Search(char x) {
	for (int az = 0; az < 33; az++)
		if (Azbuka[az] == x)	return Azbuka[az + 4];
	return x;
}

int NumBukv(string str) {
	int count = 0;
	char t = ' ';
	for (int i = 0; i < str.length(); i++) {
		t = str.at(i);
		if ((t >= 'А' && t <= 'Я') || (t >= 'а' && t <= 'я'))	count++;
	}
	return count;
}

void AzBuk(int l) {
	int Num = NumBukv(s);
	double count = 0, frequency = 0;
	char A = ' ', t = ' ';
	for (int j = 0; j < 32; j++) {
		A = Azbuka[j];
		for (int i = 0; i < l; i++) {
			t = s.at(i);
			if (t == 'ё' || t == 'Ё') {
				t = 'е';
				s.at(i) = t;
			}
			if (t == A || t == (A - 32))	count++;
		}
		frequency = count / Num;
		for (int f = 0; f < 32; f++) {
			if (A == F[f].c)		F[f].f = frequency;
		}
		count = 0;
	}
}

//Выбор действия
int Menu() {
	bool Exit = true;
	char buf[100] = {};
	while (Exit){
		char Key = '0';
		cout << endl;
		cout << "======================МЕНЮ======================" << endl;
		cout << "Везде Толстой старается схватить стихийное, бессознательное начало человеческой жизни: 1" << endl;
		cout << "Безделёв Сергей Владимирович: 2" << endl;
		cout << "Ввести текст от руки: 3" << endl;
		cout << "Завершить работу : 4" << endl;
		cout << "Введите номер пункта : ";
		Key = getchar();
		cin.ignore(1);
		int A = 0;
		if (Key < '1' || Key>'4')
			Key = '5';
		switch (Key){
		case '1':
			s = Txt1;
			Exit = false;
			break;
		case '2':
			s = "Безделёв Сергей Владимирович";
			Exit = false;
			break;
		case '3':
			cout << "Допустимые символы - буквы руского алфавита, пробел и  , . : ; !" << endl;
			getline(cin, s);
			Exit = false;
			break;
		case '4':
			return -100;
		default:
			cout << "Неверный номер меню!" << endl;
			break;
		}
	}
	return 1;
}