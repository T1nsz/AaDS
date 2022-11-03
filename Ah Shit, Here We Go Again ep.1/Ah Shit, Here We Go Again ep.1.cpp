#include <iostream>
#include <math.h>

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
				std::cout << g << "\t";
				g++;
			}
			std::cout << std::endl;
			for (int j = 0; j < 10; j++) {
				std::cout << Array[h] << "\t";
				h++;
			}
			std::cout << std::endl << std::endl;
		}
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < kolvo % 10; j++) {
				std::cout << g << "\t";
				g++;
			}
			std::cout << std::endl;
			for (int j = 0; j < kolvo % 10; j++) {
				std::cout << Array[h] << "\t";
				h++;
			}
			std::cout << std::endl << std::endl;
		}
	}
	else {
		for (int i = 0; i < kolvo / 10; i++) {
			for (int j = 0; j < kolvo % 10; j++) {
				std::cout << g << "\t";
				g++;
			}
			std::cout << std::endl;
			for (int j = 0; j < 10; j++) {
				std::cout << Array[h] << "\t";
				h++;
			}
			std::cout << std::endl << std::endl;
		}
	}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	const int m = 5, n = 55, r = 83;
	int Numbers[n], Hash[r];

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

	std::cout << "Исходный массив чисел:" << std::endl << std::endl;
	vivod(Numbers, n);
	std::cout << std::endl << std::endl << "Хеш-таблица:" << std::endl << std::endl;
	vivod(Hash, r);
	std::cout << std::endl << "Среднее количество проб -> " << KolvoProb / n;
	std::cout << std::endl << "Коэффициент заполненности -> " << Zapolnennost / r << std::endl;

}