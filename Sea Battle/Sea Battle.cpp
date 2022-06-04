#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

class Pole {
private:
	const int cols = 13;	//розмір колонок
	const int rows = 13;	//розмір рядків
	char** arr = new char* [rows];
	int x,y;//координати 
	char fourShip[4] = { '#','#' ,'#' ,'#' };
	char threeShip[3] = { '#' ,'#' ,'#' };
	char twoShip[2] = { '#' ,'#' };
	char oneShip[1] = { '#' };
	void placeShips(char** arr, char* ships, int decks, bool position);	//Метод який ставе корабель
	bool checkFree(char** arr, int x, int y, int decks, bool position);	//Метод перевірки чи вільна ячейка
	bool horizont(int lang);	//Метод вибору позиції Горизонт чи Вертикально
public:
	void alive();	//метод пошуку вбитого корабля та його окуцпації по кругу
	void createPole();	//метод створення пустого Поля
	void PrintPole();	//Метод виведеня поля
	void del();	//для чищення пям'яті
	void shoot(int lang);//Метод пострілу вручну
	void shoot(class Bot & bot); //перегрузка пострілу для рандому 
	void putShip(int lang);	//Метод розміщення кораблів на полі 
	void putShip(class Bot & bot);	//перегрузка методу розміщення кораблів для рандома
	void LikeMike(Pole& pReal, Pole& pFake);	//метод який позволяє приховати поле 
	int WINNER() {//метод для перевірки перемоги 
		int win=0;
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++){if (arr[i][j]=='X'){win++;}}
		}
		return win;
	}	
};

class Bot {	//Клас Бот 
public:
	int x1;int y1;
	bool v=false;
	int getX1(int first,int last) {	//Геттер рандомного Х
		x1 = first + rand() % last;
		return x1;
	}
	int getY1(int first, int last) {//Геттер рандомного У
		y1 = first + rand() % last;
		return y1;
	}
	bool getBool() {	//Геттер рандомного Бул
		v = rand() % 2 == 0;
		return v;
	}
};

void hello() { //Функція - заставка
	int t = 200;
	system("cls");
	for (int i = 0; i < 10; i++) { cout << endl; }
	cout << "\t\tB   ";Sleep(t); 
	cout << "a   "; Sleep(t);
	cout << "t   "; Sleep(t);
	cout << "t   "; Sleep(t);
	cout << "l   "; Sleep(t);
	cout << "e   "; Sleep(t);
	cout << "S   "; Sleep(t);
	cout << "h   "; Sleep(t);
	cout << "i   "; Sleep(t);
	cout << "p   "; Sleep(t);
	for (int i = 0; i < 10; i++) { cout << endl; }
	system("pause");
	system("cls");
}

void start() {	//функція для виводу рекомендацій по комфортній грі 
	system("cls");
	for (int i = 0; i < 10; i++) { cout << endl; }
	cout << "\tБудь ласка, змініть відношення вашого екрану до 20:9" << endl; 
	cout<<"\tпотім натисніть 'Enter' !" << endl;
	cout<<endl;
	cout << "\tPlease change the ratio of your screen to 20:9" << endl;
	cout<<"\tthen press 'Enter'" << endl;
	for (int i = 0; i < 10; i++) { cout << endl; }
	system("pause");
}

bool setting() {	//функція для вибору автоматичного чи самостійного розміщення кораблів
	for (int i = 0; i < 10; i++) { cout << endl; }
	cout << "\t\tРозміщення кораблів ?" << endl;
	cout << "\t\t[А в т о м а т и ч н о]" << endl;
	cout << "\t\tСамостійно " << endl;
	int v = true;
	while (true) {
		char step = _getch();
		if (step == 's') {
			v = false;
			system("cls");
			for (int i = 0; i < 10; i++) { cout << endl; }
			cout << "\t\tРозміщення кораблів ?" << endl;
			cout << "\t\tАвтоматично" << endl;
			cout << "\t\t[С а м о с т і й н о] " << endl;
		}
		if (step == 'w') {
			v = true;
			system("cls");
			for (int i = 0; i < 10; i++) { cout << endl; }
			cout << "\t\tРозміщення кораблів ?" << endl;
			cout << "\t\t[А в т о м а т и ч н о]" << endl;
			cout << "\t\tСамостійно " << endl;
		}
		if (step==13) {return v;}
	}
}

int language() {	//Функція для вибору мови 
	for (int i = 0; i < 10; i++) { cout << endl; }
	cout << "\t\tE n g l i s h " << endl;
	cout << "\t\t   Ukraine" << endl;
	int v = 1;
	while (true) {
		char step = _getch();
		if (step == 's') {
			v = 2;
			system("cls");
			for (int i = 0; i < 10; i++) { cout << endl; }
			cout << "\t\t   English" << endl;
			cout << "\t\tU k r a i n e " << endl;
		}
		if (step == 'w') {
			v = 1;
			system("cls");
			for (int i = 0; i < 10; i++) { cout << endl; }
			cout << "\t\tE n g l i s h " << endl;
			cout << "\t\t   Ukraine" << endl;
		}
		if (step == 13) { return v; }
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Bot bot;	//створюємо обєкт класу Бот 
	Pole MyPoleShip; //створюємо обєкт - Поле, для розміщення наших кораблів
	MyPoleShip.createPole();//Створюємо наше поле
	Pole MyPoleShoot;//створюємо обєкт - Поле, для наших пострілів
	MyPoleShoot.createPole();//Створюємо поле для пострілів
	Pole BotPoleReal;	//створюємо обєкт - Поле, для розміщення ворожих кораблів
	BotPoleReal.createPole();//Створюємо поле для ворожих кораблів
	BotPoleReal.putShip(bot);//Розміщуємо автоматично ворожі кораблі 
	//далі запуск гри
	start();	//рекомендації
	hello();	//заствка
	int lang = language();	//просимо обрати мову
	system("cls");	//очищення екрану
	bool AutoPlace = setting();	//просимо вибрати розміщення кораблів(авто чи сам)
	system("cls");
	if (AutoPlace == true) { MyPoleShip.putShip(bot); }	//роставляємо кораблі авто
	if (AutoPlace == false) { MyPoleShip.putShip(lang); }//роставляємо кораблі самостійно 
	//початко битви
	while (true) {
		cout << endl;
		if (lang == 1) { cout << "\t\t    M y   S h i p s !" << endl; }	//в залежності від мови виводимо надписи
		if (lang == 2) { cout << "\t\t    М і й  Ф л о т !" << endl; }
		cout << endl;
		MyPoleShip.PrintPole();	//виводимо поле з нашими кораблями
		cout << endl;
		if (lang == 1) { cout << "\tL e t ' s   k i l l   e n e m y   s h i p s ! " << endl; }
		if (lang == 2) { cout << "\tД а в а й т е  п е р е б ' є м о  Р у с н ю !" << endl; }
		
		cout << endl;
		MyPoleShoot.PrintPole(); //виводимо поле на якому видно наші постріли 	
		
		BotPoleReal.shoot(lang);	//Гравець стріляє по ворожому полю
		BotPoleReal.alive();		//перевірка чи немає знищених кораблів
		BotPoleReal.LikeMike(BotPoleReal, MyPoleShoot);	//виводимо ситуацію з ворожого поля на наше для пострілів
		MyPoleShip.shoot(bot);	//по полю гравця стріляє бот
		MyPoleShip.alive();
		system("cls");
		if (BotPoleReal.WINNER()==20)	//перевірка на виграш 
		{
			system("cls");
			for (int i = 0; i < 15; i++){cout << endl;}
			cout << "\tW I N N E R , W I N N E R  C h i k e n  D i n n e r !";
			for (int i = 0; i < 15; i++){cout << endl;}
			break;
		}
		if (MyPoleShip.WINNER() == 20)//перевірка на програш
		{
			system("cls");
			for (int i = 0; i < 15; i++) { cout << endl; }
			cout << "\tL O O Z Z E R !";
			for (int i = 0; i < 15; i++) { cout << endl; }
			break;
		}
	}
	cout << "by MaximDmytruk (gitHub)";
	system("pause");	
	MyPoleShip.del();	//далі очищаємо пям'ять 
	MyPoleShoot.del();
	BotPoleReal.del();
}

void Pole :: PrintPole() {						// Метод Виведення поля на екран
	
	for (int i = 0; i < cols; i++)
	{
		cout << "\t\t";
		for (int j = 0; j < rows; j++){cout << arr[i][j]<<" "; }
		cout << endl;
	}
}

void Pole ::createPole() {
	for (int i = 0; i < rows; i++) { arr[i] = new char[cols]; }
	for (int i = 0; i < cols; i++)	
	{
		if(i>1 && i<11){ arr[i][0] = 47+i; }
		for (int j = 0; j < rows; j++)
		{
			if (i == 11 && j == 0 || i == 0 && j == 11) { arr[i][j] = 'Х'; }
			if (i <= 1 && j <= 1 || i == 12 && j == 0 || i == 0 && j == 12) { arr[i][j] = ' '; }
			if (i == 1 && j!=0 || i == 12 && j != 0) { arr[i][j] = '~'; }
			if (i >=2 && i<12 && j == 1 || i >= 2 && i < 12 && j == 12) { arr[i][j] = '|'; }
			if (j > 1 && j < 11) { arr[0][j] = 47 + j; }
			if (i >= 2 && i <= 11 && j >= 2 && j <= 11) { arr[i][j] = '.'; }
		}
	}
}

void Pole:: shoot(int lang) {
	if (lang == 1) { cout << "Enter the coordinates of the shoot" << endl; }
	if (lang == 2) { cout << "Введіть координати пострілу Х та У :" << endl; }
	cin >> this->x >> this->y; x++; y++;
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (i == x && j == y){
				if(arr[i][j]=='#')arr[i][j] = 'X';
				if (arr[i][j] == '.')arr[i][j] = '*';
			}
		}
	}
}

void Pole::shoot(class Bot& bot) {
	this->x = bot.getX1(1, 10);
	this->y= bot.getY1(1, 10);
	x++; y++;
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (i == x && j == y) {
				if (arr[i][j] == '#')arr[i][j] = 'X';
				if (arr[i][j] == '.')arr[i][j] = '*';
			}
		}
	}
}

bool Pole::horizont(int lang) {
	char step;
	if (lang == 1) {
		cout << "Position horizontally = 'H'" << endl;
		cout << "Position vertically = 'V'" << endl;
	}
	if (lang == 2) {
		cout << "Розмістити Грозинтально  = 'H'" << endl;
		cout << "Розмістити Вертикально = 'V'" << endl;
	}
	step = _getch();
	if (step == 'H' or step == 'h') { return true; }
	if (step == 'V' or step == 'v') { return false; }
	while (true) {
		cout << endl;
		if (lang == 1) { cout << "Position of ship 'H' or 'V' !!! : " << endl; }
		if (lang == 2) { cout << "Спочатку вкажіть як розмістити ! ВВЕДІТЬ 'H' або 'V'!" << endl; }
		cout << endl;
		step = _getch();
		if (step == 'H' or step == 'h'){return true;}
		if (step == 'V' or step == 'v'){return false;}
	}
}

void Pole::placeShips(char** arr,  char *ships, int decks,bool position) {
	if (position == true)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				if (i ==this-> x && j == this->y) {
					for (int p = 0; p < decks; p++)
					{
						if (p == 0) {
							if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = 'x';
							if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = 'x';
							if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = 'x';
						}
						if (p == decks - 1) {
							if (arr[i][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = 'x';
							if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|') arr[i + 1][j + 1] = 'x';
							if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = 'x';
						}
						if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = 'x';
						if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = 'x';
						arr[i][j++] = ships[p];
					}
				}
			}
		}
	}
	if (position == false)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				if (i == this->x && j == this->y) {
					for (int p = 0; p < decks; p++)
					{
						if (p == 0) {
							if (arr[i-1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = 'x';
							if (arr[i-1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = 'x';
							if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = 'x';
						}
						if (p == decks - 1) {
							if (arr[i+1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i+1][j + 1] = 'x';
							if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|') arr[i + 1][j - 1] = 'x';
							if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = 'x';
						}
						if (arr[i][j+1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = 'x';
						if (arr[i][j-1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = 'x';
						arr[i++][j] = ships[p];
					}
				}
			}
		}
	}
}

void Pole::putShip(int lang) {
	bool position;
	PrintPole();
	
	if (lang == 1) { cout << "Enter the coordinates of the 1 \"Four Decks\" ship location : " << endl; }//введення 1го 4ох палубного
	if (lang == 2) { cout << "Введіть координати для 1 Чотирьох палубного корабля :" << endl; }
	position = horizont(lang);
	system("cls");
	PrintPole();
	if (lang == 1) { cout << "Position Selected = "; }
	if (lang == 2) { cout << "Розміщення вибрано = "; }
	if (position == true) {
		if (lang == 1) {
			cout << "Horizont" << endl;
			cout << "Enter coordinates of ship are :" << endl;
		}
		if (lang == 2) { 
			cout << "Горизонтально " << endl;
			cout << "Введіть координати де розмістити корабль :" << endl;
		}
		cin >> this->x >> this->y;
		while(this->x < 1 or this->x>11 or this->y < 1 or this->y>7)
		{
			if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
			if (lang == 2) { cout << "ВВедіть Координати в межах поля! "; }
			cin >> this->x >> this->y;
		}
		x++; y++;
		placeShips(arr, this->fourShip, 4,position);
	}
	if (position==false){
		if (lang == 1) {
			cout << "Vertically" << endl;
			cout << "Enter coordinates of ship are :" << endl;
		}
		if (lang == 2) {
			cout << "Вертикально ";
			cout << "Введіть координати де розмістити корабль :" << endl;
		}
		cin >> this->x >> this->y;
		while (this->x < 1 or this->x>7 or this->y < 1 or this->y>11)
		{
			if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
			if (lang == 2) { cout << "ВВедіть Координати в межах поля! "; }
			cin >> this->x >> this->y;
		}
		x++; y++;
		placeShips(arr, this->fourShip, 4, position);
	}
	system("cls");
	PrintPole();
	if (lang == 1) { cout << "Enter the coordinates 2 \"Three Decks\" ships location : " << endl; }//введення 2-ух 3ох палубних
	if (lang == 2) { cout << "Введіть координати для 2 Трьох палубних корабля :" << endl; }
	for (int i = 0; i < 2; i++)
	{
		if (lang == 1) { cout << i + 1 << " of 2  \"Three Decks\" ships location : " << endl; }
		if (lang == 2) { cout << i + 1 << " з 2 Трьох Палубних кораблів : "<<endl; }
		position = horizont(lang);
		system("cls");
		PrintPole();
		if (lang == 1) { cout << "Position Selected = "; }
		if (lang == 2) { cout << "Розміщення вибрано = "; }
		if (position == true){
			if (lang == 1) {
				cout << "Horizont" << endl;
				cout << "Enter coordinates of ship are :" << endl;
			}
			if (lang == 2) {
				cout << "Горизонтально "<<endl;
				cout << "Введіть координати де розмістити корабль :" << endl;
			}
			bool free = false;
			while (free == false) {
				cin >> this->x >> this->y;
				while (this->x < 1 or this->x>11 or this->y < 1 or this->y>8)
				{
					if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
					if (lang == 2) { cout << "ВВедіть Координати в межах поля! " << endl; }
					cin >> this->x >> this->y;
				}
				this->x++; this->y++;
				free = checkFree(arr, this->x, this->y, 3,position);
				if (free==false){cout << "Попереду корабель, введіть інші координати :" << endl;}
			}
			placeShips(this->arr, this->threeShip, 3, position);
		}
		if (position == false) {
			if (lang == 1) {
				cout << "Vertically" << endl;
				cout << "Enter coordinates of ship are :" << endl;
			}
			if (lang == 2) {
				cout << "Вертикально " << endl;
				cout << "Введіть координати де розмістити корабль :" << endl;
			}
			bool free = false;
			while (free == false) {
				cin >> this->x >> this->y;
				while (this->x < 1 or this->x>8 or this->y < 1 or this->y>11)
				{
					if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
					if (lang == 2) { cout << "ВВедіть Координати в межах поля! " << endl; }
					cin >> this->x >> this->y;
				}
				x++; y++;
				free = checkFree(arr, x, y, 3, position);
				if (free != true)
				{
					if (lang == 1) { cout << "Reserved, Enter new X, Y :" << endl; }
					if (lang == 2) { cout << "Ще б трішки і було б ДТП на морі, піпець короче, введіть інші координати  " << endl; }
				}
			}
			placeShips(this->arr, this->threeShip, 3, position);
		}
		system("cls");
		PrintPole();
	}
	cout << "Enter the coordinates 3 \"Two Decks\" ships location : " << endl;	//введення  3ох 2ух палубних
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << " of 3  \"Two Decks\" ships location : " << endl;
		position = horizont(lang);
		system("cls");
		PrintPole();
		cout << "Position Selected = ";
		if (position == true) {
			if (lang == 1) {
				cout << "Horizont" << endl;
				cout << "Enter coordinates of ship are :" << endl;
			}
			if (lang == 2) {
				cout << "Горизонтально " << endl;
				cout << "Введіть координати де розмістити корабль :<< endl" << endl;
			}
			bool free = false;
			while (free == false) {
				cin >> this->x >> this->y;
				while (this->x < 1 or this->x>11 or this->y < 1 or this->y>9)
				{
					if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
					if (lang == 2) { cout << "ВВедіть Координати в межах поля! " << endl; }
					cin >> this->x >> this->y;
				}
				x++; y++;
				free = checkFree(arr, this->x, this->y, 2, position);
				if (free == false)
				{
					if (lang == 1) { cout << "Reserved, Enter new X, Y :" << endl; }
					if (lang == 2) { cout << "Ще б трішки і було б ДТП на морі, піпець короче, введіть інші координати  " << endl; }
				}
			}
			placeShips(this->arr, this->twoShip, 2, position);
		}
		if (position == false) {
			if (lang == 1) {
				cout << "Vertically" << endl;
				cout << "Enter coordinates of ship are :" << endl;
			}
			if (lang == 2) {
				cout << "Вертикально " << endl;
				cout << "Введіть координати де розмістити корабль :" << endl;
			}
			bool free = false;
			while (free == false) {
				cin >> this->x >> this->y;
				while (this->x < 1 or this->x>9 or this->y < 1 or this->y>11)
				{
					if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
					if (lang == 2) { cout << "ВВедіть Координати в межах поля! "; }
					cin >> this->x >> this->y;
				}
				x++; y++;
				free = checkFree(arr, x, y, 2, position);
				cout << "free= " << free << endl;
				if (free != true){
					if (lang == 1) { cout << "Reserved, Enter new X, Y :" << endl; }
					if (lang == 2) { cout << "Ти що, шутиш ?  введіть інші координати, там же лінкор стоїть  " << endl; }
				}
			}
			placeShips(arr, this->twoShip, 2, position);
		}
		system("cls");
		PrintPole();
	}
	
	if (lang == 1) { cout << "Enter the coordinates 4 \"One Decks\" ships location : " << endl; }//введення  4ох 1 палубних,
	if (lang == 2) { cout << "ВВедіть координати 4-ох Однопалубних кораблів" << endl; }
	for (int i = 0; i < 4; i++)
	{
		
		if (lang == 1) { cout << i + 1 << " of 4  \"One Decks\" ships location : " << endl; }
		if (lang == 2) { cout << i + 1 << " з 4-ох Однопалубних кораблів " << endl; }
		bool free = false;
		while (free == false) {
			cin >> this->x >> this->y;
			while (this->x < 1 or this->x>11 or this->y < 1 or this->y>11)
			{
				if (lang == 1) { cout << "Enter the real coordinates within the field !" << endl; }
				if (lang == 2) { cout << "ВВедіть Координати в межах поля! "; }
				cin >> this->x >> this->y;
			}
			x++; y++;
			for (int i = 0; i < this->rows; i++)
			{
				for (int j = 0; j < this->cols; j++)
				{
					if (i == x and j == y)
					{
						if (arr[i][j] != '.') { 
							if (lang == 1) { cout << "Reserved, Enter new X, Y :" << endl; }
							if (lang == 2) { cout << "Катером в бойовий Фрегат ? ти нормальний? введіть інші координати  "; }
							free= false; 
						}
						if (arr[i][j] == '.')  { 
							if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = 'x';
							if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = 'x';
							if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = 'x';
							if (arr[i][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = 'x';
							if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|') arr[i + 1][j + 1] = 'x';
							if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = 'x';
							if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = 'x';
							if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = 'x';
							arr[i][j] = oneShip[0];
							free = true;
						}
					}
				}
			}
		}
		system("cls");
		PrintPole();
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (arr[i][j]=='x'){arr[i][j] = '.';}
		}
	}
	system("cls");
}

void Pole::putShip(class Bot& bot) {
	bool position;
	//введення 1го 4ох палубного корабля
	position = bot.getBool();
	if (position == true) {
		this->x = bot.getX1(1, 10);
		this->y = bot.getY1(1, 6);
		x++; y++;
		placeShips(arr, this->fourShip, 4, position);
	}
	if (position == false) {
		this->x = bot.getX1(1, 6);
		this->y = bot.getY1(1, 10);
		x++; y++;
		placeShips(arr, this->fourShip, 4, position);
	}
	//введення  2-ух 3 палубних кораблів
	for (int i = 0; i < 2; i++)
	{
		position = bot.getBool();
		if (position == true) {
			bool free = false;
			while (free == false) {
				this->x = bot.getX1(1, 10);
				this->y = bot.getY1(1, 7);
				this->x++; this->y++;
				free = checkFree(this->arr, this->x, this->y, 3, position);
			}
			placeShips(this->arr, this->threeShip, 3, position);
		}
		if (position == false) {
			bool free = false;
			while (free == false) {
				this->x = bot.getX1(1, 7);
				this->y = bot.getY1(1, 10);
				x++; y++;
				free = checkFree(arr, x, y, 3, position);
			}
			placeShips(this->arr, this->threeShip, 3, position);
		}
	}
	//введення  3ох 2 палубних кораблів
	for (int i = 0; i < 3; i++)
	{
		position = bot.getBool();
		if (position == true) {
			bool free = false;
			while (free == false) {
				this->x = bot.getX1(1, 10);
				this->y = bot.getY1(1, 8);
				x++; y++;
				free = checkFree(arr, this->x, this->y, 2, position);
			}
			placeShips(this->arr, this->twoShip, 2, position);
		}
		if (position == false) {
			bool free = false;
			while (free == false) {
				this->x = bot.getX1(1, 8);
				this->y = bot.getY1(1, 10);
				x++; y++;
				free = checkFree(arr, x, y, 2, position);
			}
			placeShips(arr, this->twoShip, 2, position);
		}
	}
	//введення  4ох 1 палубних кораблів
	for (int i = 0; i < 4; i++)
	{
		bool free = false;
		while (free == false) {
			this->x = bot.getX1(1, 10);
			this->y = bot.getY1(1, 10);
			x++; y++;
			for (int i = 0; i < this->rows; i++)
			{
				for (int j = 0; j < this->cols; j++)
				{
					if (i == x and j == y)
					{
						if (arr[i][j] != '.') { free = false; }
						if (arr[i][j] == '.') {
							if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = 'x';
							if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = 'x';
							if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = 'x';
							if (arr[i][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = 'x';
							if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|') arr[i + 1][j + 1] = 'x';
							if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = 'x';
							if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = 'x';
							if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = 'x';
							arr[i][j] = oneShip[0];
							free = true;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (arr[i][j] == 'x'){arr[i][j] = '.';}
		}
	}
}

void Pole::LikeMike(Pole& pReal, Pole& pFake) {
	for (int i = 0; i < this->cols; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (pReal.arr[i][j] == 'X'){pFake.arr[i][j] = 'X';}
			if (pReal.arr[i][j] == '*'){pFake.arr[i][j] = '*'; }
		}
	}
}

void Pole::alive() {
	//Пошук та перевірка 4ох палубного 
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (arr[i][j] == 'X' and arr[i][j + 1] == 'X' and arr[i][j + 2] == 'X' and arr[i][j + 3] == 'X')
			{
				for (int p = 0; p < 4; p++)
				{
					if (p == 0) {
						if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = '*';
						if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
						if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
						if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
						if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = '*';
					}
					if (p == 1) {
						if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i + 1][j + 1] = '*';
						if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
					}
					if (p == 2) {
						if (arr[i + 1][j + 2] != '~' and arr[i + 1][j + 2] != '|')arr[i + 1][j + 2] = '*';
						if (arr[i - 1][j + 2] != '~' and arr[i - 1][j + 2] != '|')arr[i - 1][j + 2] = '*';
					}
					if (p == 3) {
						if (arr[i + 1][j + 3] != '~' and arr[i + 1][j + 3] != '|')arr[i + 1][j + 3] = '*';
						if (arr[i + 1][j + 4] != '~' and arr[i + 1][j + 4] != '|')arr[i + 1][j + 4] = '*';
						if (arr[i - 1][j + 3] != '~' and arr[i - 1][j + 3] != '|')arr[i - 1][j + 3] = '*';
						if (arr[i - 1][j + 4] != '~' and arr[i - 1][j + 4] != '|')arr[i - 1][j + 4] = '*';
						if (arr[i][j + 4] != '~' and arr[i][j + 4] != '|')arr[i][j + 4] = '*';
					}
				}
			}
			//Перевірка 4ох палубного по вертикалі 
			if (arr[i][j] == 'X' and arr[i + 1][j] == 'X' and arr[i + 2][j ] == 'X' and arr[i + 3][j ] == 'X')
			{
				for (int p = 0; p < 4; p++)
				{
					if (p == 0) {
						if (arr[i-1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
						if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
						if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
						if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = '*';
						if (arr[i][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = '*';
					}
					if (p == 1) {
						if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i + 1][j + 1] = '*';
						if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
					}
					if (p == 2) {
						if (arr[i + 2][j + 1] != '~' and arr[i + 2][j + 1] != '|')arr[i + 2][j + 1] = '*';
						if (arr[i + 2][j - 1] != '~' and arr[i + 2][j - 1] != '|')arr[i + 2][j - 1] = '*';
					}
					if (p == 3) {
						if (arr[i + 3][j + 1] != '~' and arr[i + 3][j + 1] != '|')arr[i + 3][j + 1] = '*';
						if (arr[i + 4][j + 1] != '~' and arr[i + 4][j + 1] != '|')arr[i + 4][j + 1] = '*';
						if (arr[i + 3][j - 1] != '~' and arr[i + 3][j - 1] != '|')arr[i + 3][j - 1] = '*';
						if (arr[i + 4][j - 1] != '~' and arr[i + 4][j - 1] != '|')arr[i + 4][j -1] = '*';
						if (arr[i + 4][j] != '~' and arr[i + 4][j] != '|')arr[i + 4][j] = '*';
					}
				}
			}
			//Пошук та перевірка 3 палубного
			if (arr[i][j] == 'X' and arr[i][j + 1] == 'X' and arr[i][j + 2] == 'X'
				and arr[i][j + 3] != 'X' and arr[i][j + 3] != '#' and arr[i][j - 1] != 'X' and arr[i][j - 1] != '#')
			{
				for (int p = 0; p < 3; p++)
				{
					if (p == 0) {
						if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = '*';
						if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
						if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
						if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
						if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = '*';
					}
					if (p == 1) {
						if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i + 1][j + 1] = '*';
						if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
					}
					if (p == 2) {
						if (arr[i + 1][j + 2] != '~' and arr[i + 1][j + 2] != '|')arr[i + 1][j + 2] = '*';
						if (arr[i + 1][j + 3] != '~' and arr[i + 1][j + 3] != '|')arr[i + 1][j + 3] = '*';
						if (arr[i - 1][j + 2] != '~' and arr[i - 1][j + 2] != '|')arr[i - 1][j + 2] = '*';
						if (arr[i - 1][j + 3] != '~' and arr[i - 1][j + 3] != '|')arr[i - 1][j + 3] = '*';
						if (arr[i][j + 3] != '~' and arr[i][j + 3] != '|')arr[i][j + 3] = '*';
					}
				}
			}
			//Перевірка Вертикально 3ох палубних 
			if (arr[i][j] == 'X' and arr[i+1][j] == 'X' and arr[i+2][j] == 'X'
				and arr[i+3][j] != 'X' and arr[i+3][j] != '#' and arr[i-1][j] != 'X' and arr[i-1][j] != '#')
			{
				for (int p = 0; p < 3; p++)
				{
					if (p == 0) {
						if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
						if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
						if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
						if (arr[i ][j - 1] != '~' and arr[i ][j - 1] != '|')arr[i ][j - 1] = '*';
						if (arr[i ][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = '*';
					}
					if (p == 1) {
						if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i + 1][j + 1] = '*';
						if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
					}
					if (p == 2) {
						if (arr[i + 2][j + 1] != '~' and arr[i + 2][j + 1] != '|')arr[i + 2][j + 1] = '*';
						if (arr[i + 3][j + 1] != '~' and arr[i + 3][j + 1] != '|')arr[i + 3][j + 1] = '*';
						if (arr[i+2][j -1] != '~' and arr[i + 2][j - 1] != '|')arr[i + 2][j - 1] = '*';
						if (arr[i+3][j -1] != '~' and arr[i + 3][j - 1] != '|')arr[i + 3][j - 1] = '*';
						if (arr[i+3][j] != '~' and arr[i + 3][j] != '|')arr[i + 3][j] = '*';
					}
				}
			}
			//Пошук та перевірка 2 палубного
			if (arr[i][j] == 'X' and arr[i][j + 1] == 'X' and arr[i][j + 2] != 'X' and arr[i][j + 2] != '#' and arr[i][j - 1] != 'X' and arr[i][j - 1] != '#')
			{
				for (int p = 0; p < 2; p++)
				{
					if (p == 0) {
						if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = '*';
						if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
						if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
						if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
						if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = '*';
					}
					if (p == 1) {
						if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i + 1][j + 1] = '*';
						if (arr[i + 1][j + 2] != '~' and arr[i + 1][j + 2] != '|')arr[i + 1][j + 2] = '*';
						if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
						if (arr[i - 1][j + 2] != '~' and arr[i - 1][j + 2] != '|')arr[i - 1][j + 2] = '*';
						if (arr[i][j + 2] != '~' and arr[i][j + 2] != '|')arr[i][j + 2] = '*';
					}
				}
			}
			//вертикально 2палубні
			if (arr[i][j] == 'X' and arr[i+1][j] == 'X' and arr[i+2][j] != 'X' and arr[i+2][j] != '#' and arr[i-1][j] != 'X' and arr[i-1][j] != '#')
			{
				for (int p = 0; p < 2; p++)
				{
					if (p == 0) {
						if (arr[i-1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
						if (arr[i - 1][j +1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
						if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
						if (arr[i][j - 1] != '~' and arr[i ][j - 1] != '|')arr[i][j-1] = '*';
						if (arr[i ][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = '*';
					}
					if (p == 1) {
						if (arr[i + 2][j + 1] != '~' and arr[i + 2][j + 1] != '|')arr[i + 2][j + 1] = '*';
						if (arr[i + 2][j] != '~' and arr[i + 2][j] != '|')arr[i + 2][j] = '*';
						if (arr[i + 2][j - 1] != '~' and arr[i + 2][j - 1] != '|')arr[i + 2][j - 1] = '*';
						if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|')arr[i + 1][j + 1] = '*';
						if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
					}
				}
			}
			//Пошук та перевірка 1 палубного
			if (arr[i][j] == 'X' and arr[i][j + 1] != 'X' and arr[i][j + 1] != '#' and arr[i][j - 1] != 'X' and arr[i][j - 1] != '#' and i != 0
				and arr[i+1][j] != 'X' and arr[i+1][j] != '#' and arr[i-1][j] != 'X' and arr[i-1][j] != '#')
			{
				if (arr[i][j - 1] != '~' and arr[i][j - 1] != '|')arr[i][j - 1] = '*';
				if (arr[i + 1][j - 1] != '~' and arr[i + 1][j - 1] != '|')arr[i + 1][j - 1] = '*';
				if (arr[i - 1][j - 1] != '~' and arr[i - 1][j - 1] != '|')arr[i - 1][j - 1] = '*';
				if (arr[i][j + 1] != '~' and arr[i][j + 1] != '|')arr[i][j + 1] = '*';
				if (arr[i + 1][j + 1] != '~' and arr[i + 1][j + 1] != '|') arr[i + 1][j + 1] = '*';
				if (arr[i - 1][j + 1] != '~' and arr[i - 1][j + 1] != '|')arr[i - 1][j + 1] = '*';
				if (arr[i + 1][j] != '~' and arr[i + 1][j] != '|')arr[i + 1][j] = '*';
				if (arr[i - 1][j] != '~' and arr[i - 1][j] != '|')arr[i - 1][j] = '*';
			}
		}
	}
}

bool Pole::checkFree(char** arr, int x, int y, int decks,bool position) {
	if (position == true) {
		for (int i = 0; i < this->cols; i++) {
			for (int j = 0; j < this->rows; j++)
			{
				if (i == x and j == y)
				{
					if (arr[i][j] != '.' or arr[i][j++] != '.' or arr[i][j + decks-1] != '.') { return false; }
					if (arr[i][j] == '.' and arr[i][++j] == '.' and arr[i ][j + decks - 1] == '.') { return true; }
				}
			}
		}
	}
	if (position == false)
	{
		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++)
			{
				if (i==x and j== y)
				{
					if (arr[i][j] != '.' or arr[i + 1][j] != '.' or arr[i + decks - 1][j] != '.') { return false; }
					if (arr[i][j] == '.' and arr[i + 1][j] == '.' and arr[i + decks - 1][j] == '.') { return true; }
				}
			}
		}
	}
}

void Pole::del() {
	for (int i = 0; i < this->rows; i++)
	{
		delete[]arr[i];
	}
	delete[] arr[cols];
}