#include <iostream>
#include <math.h>
#include <string>

using std::cin; using std::cout; using std::endl;


int randomizer(int* Numbers, int m, int n) {
	int a = 0;
	int b = 0;
Back:
	for (int i = 0; i < m; i++) {
		if (i == 0) {
			while (a == 0)  a = rand() % 10;
		}
		else {
			b = rand() % 10;
			if (b == 0) a = a * 10;
			else a = a + (b * pow(10, i));
		}
	}
	for (int i = 0; i < n; i++) {
		if (Numbers[i] == a) goto Back;
	}
	return a;
}

void vivod(int* Array, int kolvo) {
	int g = 0, h = 0;
	if (kolvo % 10 != 0) {
		for (int i = 0; i < kolvo / 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << g << "\t";
				g++;
			}
			cout << endl;
			for (int j = 0; j < 10; j++) {
				cout << Array[h] << "\t";
				h++;
			}
			cout << endl << endl;
		}
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < kolvo % 10; j++) {
				cout << g << "\t";
				g++;
			}
			cout << endl;
			for (int j = 0; j < kolvo % 10; j++) {
				cout << Array[h] << "\t";
				h++;
			}
			cout << endl << endl;
		}
	}
	else {
		for (int i = 0; i < kolvo / 10; i++) {
			for (int j = 0; j < kolvo % 10; j++) {
				cout << g << "\t";
				g++;
			}
			cout << endl;
			for (int j = 0; j < 10; j++) {
				cout << Array[h] << "\t";
				h++;
			}
			cout << endl << endl;
		}
	}
}

void add_hesh(int &Hesh, int a, int b, float& KolvoProb, float& Zapolnennost) { //hesh - хеш-таблица, a - число, что нужно добавить, b - размерность этого числа
	int func;
	func = (((a / (int)pow(10, (b - 1))) + (a / (int)pow(10, (b - 2)) % 10) + (a % 10)) % b);

}

void da(float &KolvoProb, float &Zapolnennost) {

}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int m = 5, n = 55, r; //  m - размерность, n - кол-во элементов в исх. массиве, r - размерность хеш-таблицы
	if (n % 2 == 0) {
		r = n * 1.5;
	}
	else {
		n++;
		r = n * 1.5;
	}
	int* Numbers = new int[n];
	int* Hash = new int[r];

	for (int i = 0; i < n; i++) {
		Numbers[i] = randomizer(Numbers, m, n);
	}

	float KolvoProb = 0, Zapolnennost = 0;
	for (int i = 0; i < r; i++) {
		Hash[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int l = 1, func;
		func = (((Numbers[i] / (int)pow(10, (m - 1))) + (Numbers[i] / (int)pow(10, (m - 2)) % 10) + (Numbers[i] % 10)) % r);
		if (Hash[func] == 0) {
			KolvoProb++;
			Hash[func] = Numbers[i];
			Zapolnennost++;
		}
		else {
			int func0 = func;
			while (Hash[func0] != 0) {
				KolvoProb++;
				l++;
				func0 = (func + l * l) % r;
			}
			Hash[func0] = Numbers[i];
			Zapolnennost++;
		}
	}

	cout << "Исходный массив чисел:" << endl << endl;
	vivod(Numbers, n);
	cout << endl << endl << "Хеш-таблица:" << endl << endl;
	vivod(Hash, r);
	da(KolvoProb, Zapolnennost);
	cout << endl << "Среднее количество проб -> " << KolvoProb / n;
	cout << endl << "Коэффициент заполненности -> " << Zapolnennost / r << endl;
	{
	Manti:
		cout << endl << "Ввести новый элемент - 1" << endl << "Удалить элемент - 2" << endl << "Заменить элемент - 3" << endl << "Выйти - 4" << endl << "Выбор -> ";
	Shayrma:
		int x, y;
		cin >> x;
		switch (x) {
		case 1: { //новый элемент
			cout << endl << "Ввести вручную - 1" << endl << "Ввести автоматически";
			cout << endl << "Выбор -> ";
		Kartoshka:
			cin >> x;
			switch (x) {
			case 1: { //ручной ввод
				bool flag = false;
				cout << endl << "Введите значение элемента, размерность которого больше 2 -> ";
			Chebyrek:
				cin >> y;
				x = std::size(std::to_string(y));
				if (x < 3) {
					cout << endl << "Размерность числа меньше 3. Попробуйте заново -> ";
					goto Chebyrek;
				}
				for (int i = 0; i < r; i++) {
					if (Hash[i] == y) {
						cout << endl << "Данное число найдено в хеш-таблице. Его индекс -> " << i;
						flag = true;
					}
				}
				if (flag == false) {
					add_hesh(Hash, y, x);
					cout << "Число было добавлено в хеш-таблицу.";
				}
			Pecenka:
				cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1" << "Нет - 2" << "Выбор -> ";
				cin >> x;
				switch (x) {
				case 1: 
					goto Manti;
				case 2: 
					break;
				default:
					cout << endl << "Введено неверное значение." << endl << "Попробуйте заново -> ";
					goto Pecenka;
				}
			}
			case 2: { //автоматический ввод
				break;
			}
			default:
				cout << endl << "Введено неверное значение." << endl << "Попробуйте заново -> ";
				goto Kartoshka;
			}
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			cout << endl << "Досвидания" << endl;
			break;
		}
		default:
			cout << endl << "Введено неверное значение." << endl << "Попробуйте заново -> ";
			goto Shayrma;
			break;
		}
	}
}