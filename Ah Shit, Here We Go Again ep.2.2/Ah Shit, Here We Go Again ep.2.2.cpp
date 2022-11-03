#include <iostream>
#include <math.h>

using std::cin; using std::cout; using std::endl;

float KolvoProb = 0, Zapolnennost = 0, Yvelichenie = 0;
int n, m, r; // m - размерность, n - кол-во чисел, r - размерность хеш-таблицы

int randomizer(int razmernost, int* Numbers) {
	int a = 0, b = 0;
Back:
	for (int i = 0; i < razmernost; i++) {
		if (i == 0) {
			while (a == 0)  a = rand() % 10;
		}
		else {
			b = rand() % 10;
			if (b == 0) a = a * 10;
			else a += (b * (int)pow(10, i));
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

void hash_vivod(int* Hash) {
	cout << endl << endl << endl << "  Хеш-таблица:" << endl << endl;
	vivod(Hash, r);
	cout << endl << "  Коэффициент заполненности -> " << Zapolnennost / r << endl;
}

int hash_add(int Key, int razmernost, int*& Hash) {
	int func = (((Key / (int)pow(10, (razmernost - 1))) + (Key / (int)pow(10, (razmernost - 2)) % 10) + (Key % 10)) % r);
	if ((Hash[func] == 0) || (Hash[func] == -1)) {
		Hash[func] = Key;
		KolvoProb++;
		Zapolnennost++;
		return func;
	}
	else {
		int oprobivanie = 1, func0 = func;
		while ((Hash[func0] != 0) && (Hash[func0] != -1)) {
			func0 = (func + oprobivanie * oprobivanie) % r;
			KolvoProb++;
			oprobivanie++;
		}
		Hash[func0] = Key;
		Zapolnennost++;
		return func0;
	}
}

int razmer(int Key) {
	int a = 0;
	while (Key != 0) {
		a++;
		Key = Key / 10;
	}
	return a;
}

int hash_search(int Key, int* Hash) {
	int x, func, func0, oprobivanie = 1;
	x = razmer(Key);
	func = (((Key / (int)pow(10, (x - 1))) + (Key / (int)pow(10, (x - 2)) % 10) + (Key % 10)) % r);
	if (Hash[func] == Key) {
		return func;
	}
	else {
		func0 = func;
		while ((Hash[func0] != Key) && (Hash[func0] != 0)) {
			func0 = (func + oprobivanie * oprobivanie) % r;
			oprobivanie++;
		}
		if (Hash[func0] == Key) {
			return func0;
		}
		else return -2;
	}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	n = 55;
	m = 5;
	r = 84;
	int* Numbers = new int[n];
	int* Hash = new int[r];

	for (int i = 0; i < r; i++) {
		Hash[i] = 0;
		if (i < n) Numbers[i] = randomizer(m, Numbers);
	}

	for (int i = 0; i < n; i++) {
		hash_add(Numbers[i], m, Hash);
	}

	cout << "  Исходный массив чисел:" << endl << endl;
	vivod(Numbers, n);
	hash_vivod(Hash);
	cout << "  Среднее количество проб -> " << KolvoProb / n << endl;


	int x, y, z, func, func0, oprobivanie = 1, Key;
Manti:
	cout << endl << "Ввести новый ключ - 1" << endl << "Удалить ключ - 2" << endl << "Заменить ключ - 3" << endl << "Выйти - 4" << endl << "  Выбор -> ";
Shayrma:
	cin >> x;
	switch (x) { //x - выбор функции
	case 1: { //новый ключ
		cout << endl << "Ввести вручную - 1" << endl << "Ввести автоматически - 2" << endl << "Назад - 3";
		cout << endl << "  Выбор -> ";
	Kartoshka:
		cin >> x;
		switch (x) { //x - вручную/автоматически
		case 1: { //ручной ввод
			bool flag = false;
			cout << endl << "  Введите значение ключа, размерность которого не меньше 3 и не больше 7 -> ";
		Chebyrek:
			cin >> Key;
			x = razmer(Key); //x - размерность
			if (x < 3) {
				cout << endl << "  Размерность ключа меньше 3. Попробуйте заново -> ";
				goto Chebyrek;
			}
			if (x > 7) {
				cout << endl << "  Размерность ключа больше 7. Попробуйте заново -> ";
				goto Chebyrek;
			}
			y = hash_search(Key, Hash);
			if (y == -2) {
				x = hash_add(Key, x, Hash); //x - индекс; в функцию пошла размерность
				cout << endl << endl << "\tКлюч - " << Key << " - был добавлен в хеш-таблицу в индекс - " << x;
				hash_vivod(Hash);
				cout << "  Среднее количество проб -> " << KolvoProb / n;
			}
			else {
				cout << endl << endl << "\tКлюч - " << Key << " - найден в хеш-таблице. Его индекс - " << y << endl;
			}
			cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
		Pecenka:
			cin >> x;
			switch (x) {
			case 1:
				goto Manti;
			case 2:
				return 0;
			default:
				cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
				goto Pecenka;
			}
		}
		case 2: { //автоматический ввод
			cout << endl << "  Введите размерность ключа (не меньше 3 и не больше 7) -> ";
		Salo:
			cin >> x;
			if (x < 3) {
				cout << endl << "  Размерность ключа меньше 3. Попробуйте заново -> ";
				goto Salo;
			}
			if (x > 7) {
				cout << endl << "  Размерность ключа больше 7. Попробуйте заново -> ";
				goto Salo;
			}
			Key = randomizer(x, Numbers);
			x = hash_add(Key, x, Hash);
			cout << endl << endl << "\tКлюч - " << Key << " - был добавлен под индекс - " << x;
			hash_vivod(Hash);
			cout << endl << "  Среднее количество проб -> " << KolvoProb / n;
			cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
		Kryasan:
			cin >> x;
			switch (x) {
			case 1:
				goto Manti;
			case 2:
				return 0;
			default:
				cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
				goto Kryasan;
			}
		}
		case 3: {
			goto Manti;
		}
		default:
			cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
			goto Kartoshka;
		}
	}
	case 2: { // удаление ключа
		cout << endl << "  Какой какой ключ подлежит удалению -> ";
		cin >> Key;
		y = hash_search(Key, Hash);
		if (y == -2) {
			cout << endl << endl << "\tКлюч - " << Key << " - не был найден" << endl;
			cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
		Belka:
			cin >> x;
			switch (x) {
			case 1:
				goto Manti;
			case 2:
				return 0;
			default:
				cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
				goto Belka;
			}
		}
		else {
			Hash[y] = -1;
			Zapolnennost--;
			cout << endl << endl << "\tКлюч - " << Key << " - найденный под индексом - " << y << " - был успешно удален.";
			hash_vivod(Hash);
			cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
		Oladyshek:
			cin >> x;
			switch (x) {
			case 1:
				goto Manti;
			case 2:
				return 0;
			default:
				cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
				goto Oladyshek;
			}
		}
	}
	case 3: { //замена
		cout << endl << "  Какой ключ следует заменить -> ";
	Zima:
		cin >> Key;
		if ((Key == 0) || (Key == -1)) {
			if (Key == 0) {
				cout << endl << "0 не является ключом" << endl << "  Попробуйте заново -> ";
			}
			else {
				cout << endl << "-1 не является ключом" << endl << "  Попробуйте заново -> ";
			}
			goto Zima;
		}
		y = hash_search(Key, Hash);
		if (y == -2) {
			cout << endl << endl << "\tКлюч - " << Key << " - не был найден" << endl;
			cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
		Fu:
			cin >> x;
			switch (x) {
			case 1:
				goto Manti;
			case 2:
				return 0;
			default:
				cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
				goto Fu;
			}
		}
		else {
			cout << endl << endl << "\tКлюч - " << Key << " - найден под индексом - " << y << endl << endl << endl << "На какой ключ его требуется заменить?" << endl << "Ввести вручную - 1" << endl << "Ввести автоматически - 2" << endl << "  Выбор -> ";
			int Key2;
		Aloe:
			cin >> x;
			switch (x) {
			case 1: {   //ручной
				cout << endl << "  Введите новый ключ, размерность которого не меньше 3 и не больше 7 -> ";
			More:
				cin >> Key2;
				x = razmer(Key2); //x - размерность
				if (x < 3) {
					cout << endl << "  Размерность ключа меньше 3. Попробуйте заново -> ";
					goto More;
				}
				if (x > 7) {
					cout << endl << "  Размерность ключа больше 7. Попробуйте заново -> ";
					goto More;
				}
				z = hash_search(Key2, Hash);
				if (z == -2) {
					Hash[y] = -1;
					x = hash_add(Key2, x, Hash);
					cout << endl << endl << "\tКлюч - " << Key << " - находящийся под индексом - " << y << " - был заменён на ключ - " << Key2 << " - и помещен в индекс - " << x;
					hash_vivod(Hash);
					cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
				Krem:
					cin >> x;
					switch (x) {
					case 1:
						goto Manti;
					case 2:
						return 0;
					default:
						cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
						goto Krem;
					}
				}
				else {
					cout << endl << "Введен ключ индентичный тому, что итак находится под индексом - " << z << endl << "  Введите новый ключ -> ";
					goto More;
				}
			}
			case 2: {
				cout << endl << "  Введите размерность ключа (не меньше 3 и не больше 7) -> ";
			Pesok:
				cin >> x;
				if (x < 3) {
					cout << endl << "  Размерность ключа меньше 3. Попробуйте заново -> ";
					goto Pesok;
				}
				if (x > 7) {
					cout << endl << "  Размерность ключа больше 7. Попробуйте заново -> ";
					goto Pesok;
				}
				Key2 = randomizer(x, Numbers);
				Hash[y] = Key2;
				cout << endl << endl << "\tКлюч - " << Key << " - находящийся под индексом - " << y << " - заменен на ключ - " << Key2;
				cout << endl << endl << "Вернуться к выбору функций?" << endl << "Да - 1\t\tНет - 2" << endl << "  Выбор -> ";
			Ka:
				cin >> x;
				switch (x) {
				case 1:
					goto Manti;
				case 2:
					return 0;
				default:
					cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
					goto Ka;
				}
			}
			}
		}
	case 4: {
		return 0;
	}
	default:
		cout << endl << "Введено неверное значение." << endl << "  Попробуйте заново -> ";
		goto Shayrma;
	}
	}
	delete[] Numbers;
	delete[] Hash;
}





































/*#include <iostream>
#include <math.h>
#include <string>

using std::cin; using std::cout; using std::endl;

float KolvoProb = 0, Zapolnennost = 0, Yvelichenie = 0;
int n, m, r; // m - размерность, n - кол-во чисел, r - размерность хеш-таблицы

void create_r() {
	if (n % 2 == 0) {
		r = n * 1.5;
	}
	else {
		n++;
		r = n * 1.5;
	}
}

int randomizer(int razmernost, int* Numbers) {
	int a = 0, b = 0;
Back:
	for (int i = 0; i < razmernost; i++) {
		if (i == 0) {
			while (a == 0)  a = rand() % 10;
		}
		else {
			b = rand() % 10;
			if (b == 0) a = a * 10;
			else a += (b * (int)pow(10, i));
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

void full_vivod(int* Numbers, int* Hash) {
	cout << "Исходный массив чисел:" << endl << endl;
	vivod(Numbers, n);
	cout << endl << endl << "Хеш-таблица:" << endl << endl;
	vivod(Hash, r);
	cout << endl << "Среднее количество проб -> " << KolvoProb / n;
	cout << endl << "Коэффициент заполненности -> " << Zapolnennost / r << endl;
}

int hash_add(int Key, int razmernost, int*& Hash) {
	int func = (((Key / (int)pow(10, (razmernost - 1))) + (Key / (int)pow(10, (razmernost - 2)) % 10) + (Key % 10)) % r);
	if (Hash[func] == 0) {
		Hash[func] = Key;
		KolvoProb++;
		Zapolnennost++;
		return func;
	}
	else {
		int oprobivanie = 1, func0 = func;
		while (Hash[func0] != 0) {
			func0 = (func + oprobivanie * oprobivanie) % r;
			KolvoProb++;
			oprobivanie++;
		}
		Hash[func0] = Key;
		Zapolnennost++;
		return func0;
	}
}

void hash_delete(int*& Hash, int detele) { //detele - ключ, что нужно удалить
	for (int i = 0; i < r; i++) {
		if (Hash[i] == detele) Hash[i] = 0;
	}
}

void hash_rep(int*& Hash, int rep) { //rep - ключ, который нужно поменять

}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	n = 55;
	m = 5;
	create_r();
	int* Numbers = new int[n];
	int* Hash = new int[r];

	for (int i = 0; i < r; i++) {
		Hash[i] = 0;
		if (i < n) Numbers[i] = randomizer(m, Numbers);
	}

	for (int i = 0; i < n; i++) {
		hash_add(Numbers[i], m, Hash);
	}

	full_vivod(Numbers, Hash);

	{
	Manti:
		cout << endl << "Ввести новый элемент - 1" << endl << "Удалить элемент - 2" << endl << "Заменить элемент - 3" << endl << "Выйти - 4" << endl << "Выбор -> ";
	Shayrma:
		int x, Key;
		cin >> x;
		switch (x) { //x - выбор функции
		case 1: { //новый элемент
			cout << endl << "Ввести вручную - 1" << endl << "Ввести автоматически";
			cout << endl << "Выбор -> ";
		Kartoshka:
			cin >> x;
			switch (x) { //x - вручную/автоматически
			case 1: { //ручной ввод
				bool flag = false;
				cout << endl << "Введите значение элемента, размерность которого больше 2 -> ";
			Chebyrek:
				cin >> Key;
				x = std::size(std::to_string(Key)); //x - размерность
				if (x < 3) {
					cout << endl << "Размерность числа меньше 3. Попробуйте заново -> ";
					goto Chebyrek;
				}
				for (int i = 0; i < r; i++) {
					if (Hash[i] == Key) {
						cout << endl << "Данное число найдено в хеш-таблице. Его индекс -> " << i;
						flag = true;
					}
				}
				if (flag == false) {
					if (Yvelichenie = 0) {
						n++;
					}
					else Yvelichenie--;
					create_r();
					x = hash_add(Key, x, Hash); //x - индекс; в функцию пошла размерность
					cout << "Число было добавлено в хеш-таблицу в индекс - " << x;
					full_vivod(Numbers, Hash);
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

	delete[] Numbers;
	delete[] Hash;
}*/