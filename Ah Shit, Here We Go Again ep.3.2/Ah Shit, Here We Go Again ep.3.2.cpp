//24 шестизначных элемента, идеально сбалансированное дерево, 3 правосторонних обхода

#include <iostream>
#include <math.h>

using std::cin; using std::cout; using std::endl;

int m = 6, n = 24;
int level;

void gaps(int a) { // а пробелов поставить
	for (int i = 0; i < a; i++) {
		cout << " ";
	}
}

void tree_show(int* tree) {
	int a = (int)(pow(2, (level - 1))); //a - кол-во пробелов, (gaps (m пробелов))
	int b = 0, c, d = 0; // b - пробелы (gaps) между ветками, с - колво чисел на уровне, d - корень, который выводится
	int e, f;
	for (int i = 0; i < level - 2; i++) {
		b = b + (int)(pow(2, i));
	}
	for (int i = 0; i < level; i++) {
		c = (int)(pow(2, i));
		for (int l = 0; l < a; l++) {
			gaps(6);
		}
		for (int j = 0; j < c; j++) {
			if (j != 0) {
				for (int l = 0; l < a - 1; l++) {
					gaps(6);
				}
			}
			if (tree[d] == 0)
				if (d % 2 == 0) cout << "    0 ";
				else cout << " 0    ";
			else cout << tree[d];
			d++;
			if (i != level - 1) {
				for (int l = 0; l < a - 1; l++) {
					gaps(6);
				}
			}
			gaps(6);
		}

		/*	e = 1 + (int)(pow(2, (level - 1 - i))); */

		if (i < level - 1) {
			cout << endl;
		}
		a = a / 2;
	}
}

int randomizer(int razmernost, int* Array) {
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
		if (Array[i] == a) goto Back;
	}
	return a;
}

int  tree_levels(int n) {
	int i = 0;
	while (n > 0) {
		n = n - (int)pow(2, i);
		i++;
	}
	return i;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	level = tree_levels(n);
	int razmer = 0;
	for (int i = 0; i < level; i++) {
		razmer = razmer + (int)(pow(2, i));
	}
	int* tree = new int[razmer];

	for (int i = 0; i < razmer; i++) {
		if (i < n) {
			tree[i] = randomizer(6, tree);
		}
		else tree[i] = 0;
	}

	cout << level << endl;
	for (int i = 0; i < razmer; i++) cout << tree[i] << " "; cout << endl << endl;

	for (int i = 0; i < 8; i++) {
		gaps(6);
		cout << "111111";
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		cout << "111111";
		gaps(6);
	}
	cout << endl << endl;

	tree_show(tree);

/*

	int chisel = 1;
	int f = 0;
	int h = 16;
	int k = 1;
	int u = 1;
	int b = 5;
	for (int i = 0; i < level; i++) {

		for (int j = 0; j < chisel; j++) {
			for (int l = 0; l < h; l++) {
				cout << "      ";
			}
			if (tree[f] == 0)
				if (f % 2 == 0) cout << "    0 ";
				else cout << " 0    ";
			else cout << tree[f];
			f++;
			for (int l = 0; l < (h - 1); l++) {
				cout << "      ";
			}
		}
		cout << endl;
		if (i != level - 1) {
			b = 5;
			for (int p = 0; p < 3; p++) {
				for (int j = 0; j < chisel; j++) {
					for (int l = 0; l < (h / 2); l++) cout << "      "; //da
					for (int l = 0; l < b; l++) cout << " ";
					cout << "/";


					for (int l = 0; l < (h / 2); l++) cout << "      "; //da


					cout << R"(\)";
					for (int l = 0; l < b; l++) cout << " ";
				}
				b--;
				cout << endl;
			}

		}
		chisel = (int)(pow(2, (i+1)));
		h = h / 2;
		k = k * 2;
	}
*/
}

