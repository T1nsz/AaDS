//24 шестизначных элемента, идеально сбалансированное дерево, 3 правосторонних обхода

#include <iostream>

using std::cin; using std::cout; using std::endl;

const int n = 24, m = 6;


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

struct node {
	int data;
	node* left;
	node* right;
};

node* Tree = NULL;

void node_add(int a, node **T) {
	if ((*T) == NULL) {
		(*T) = new node;
		(*T)->data = a;
		(*T)->left = NULL;
		(*T)->right = NULL;
		return;
	}
	if (a > (*T)->data) node_add(a, &(*T)->left);
	else node_add(a, &(*T)->right);
}

/*
void node_print(node* t, int u)
{
	if (t == NULL) return; //Если дерево пустое, то отображать нечего, выходим
	else //Иначе
	{
		node_print(t->left, ++u);//С помощью рекурсивного посещаем левое поддерево
		for (int i = 0; i < u; ++i) cout << "|";
		cout << t->data << endl; //И показываем элемент
		u--;
	}
	node_print(t->right, ++u); //С помощью рекурсии посещаем правое поддерево
}
*/

void node_print() {

}

int main() {
	int x;
	int Numbers[n];
	for (int i = 0; i < n; i++) {
		x = randomizer(m, Numbers);
		Numbers[i] = x;
		node_add(x, &Tree);
	}

	for (int i = 0; i < n; i++) {
		cout << Numbers[i] << " ";
	}
	cout << endl;
	node_print(Tree, 0);
}


/*
#include <iostream>
#include <math.h>

using std::cin; using std::cout; using std::endl;
const int n = 24, m = 6;
int n, nl, nr, a1, a2;

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

struct node {
	int data;
	struct node* left;
	struct node* right;
};

void tree_add(int data, node* tree) {
	if (tree == NULL) {
		tree = new node;
		tree->left = NULL;
		tree->right = NULL;
		return;
	}
}

int tree_depth() {
	int a = 0, b = 0, c = n;
	while (c > 0) {
		c = c - pow(2, a);
		a++;
		b++;
	}
	return b;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int* Array1 = new int[a1];
	int* Array2 = new int[a2];
	int* Numbers = new int[n];

	for (int i = 0; i < n; i++) {
		Numbers[i] = randomizer(m, Numbers);
	}

	for (int i = 0; i < n; i++) {

	}

	tree_add(3, );

}*/