#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define numRow 5
#define numCol 5

typedef struct {
	short int vert;
	short int horiz;
} offsets;

offsets move[8] = {
		{-1, 0},
		{-1, 1},
		{0, 1},
		{1, 1},
		{1, 0},
		{1, -1},
		{0, -1},
		{-1, -1}
};

typedef struct position {
	short int row;
	short int col;
	short int dir;
}position;
typedef struct element* stackPtr;
typedef struct element {
	position data;
	stackPtr link;
}element;
stackPtr top;

typedef struct row* listPtr;
typedef struct row {
	short int col;
	listPtr link;
}row;
listPtr r[numRow + 1];

short int maze[numRow + 2][numCol + 2] = { 0 };
short int mark[numRow + 2][numCol + 2] = { 0 };
short int check_maze[numRow + 2][numCol + 2] = { 0 };

void setup_maze();
void askIfContinue();
void initializeLinkedList();
void insert(listPtr* first, listPtr x, int row, int column);
void path();
void printMaze();
void push(position item);
position pop();

void setup_maze() {
	short int maze0[numRow][numCol] = {
		{0, 1, 1, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0},
		{0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0}
	};

	for (int i = 0; i < numRow + 2; i++) {
		maze[i][0] = 1;
		maze[i][numRow + 1] = 1;
	}
	for (int j = 0; j < numCol + 2; j++) {
		maze[0][j] = 1;
		maze[numCol + 1][j] = 1;
	}

	for (int i = 1; i < numRow + 1; i++)
	{
		for (int j = 1; j < numCol + 1; j++)
			maze[i][j] = maze0[i - 1][j - 1];
	}
}

void askIfContinue() {
	char c;
	printf("continue(Y/N)? : ");
	c = getchar();
	getchar();
	if (c != 'Y' && c != 'y') {
		printf("\nterminating the program...\n");
		exit(1);
	}
	putchar('\n');
}

void initializeLinkedList() {
	for (int i = 1; i < numRow + 1; i++) {
		r[i] = (listPtr)malloc(sizeof(struct row));
		r[i] = NULL;
	}
}
void insert(listPtr* first, listPtr x, int row, int column) {
	listPtr temp;
	temp = (listPtr)malloc(sizeof(*temp));
	temp->col = column;
	if (*first) {
		temp->link = x->link;
		x->link = temp;
	}
	else {
		temp->link = NULL;
		*first = temp;
		if (row != numRow || column != numCol) {
			printMaze();
			askIfContinue();
		}
	}
}

void path() {
	int row, col, nextRow, nextCol, dir;
	bool found = false;
	position pos;
	mark[1][1] = 1;
	top = NULL; pos.row = 1; pos.col = 1; pos.dir = 1; push(pos);
	row = pos.row; col = pos.col; dir = pos.dir;
	initializeLinkedList();

	while (dir < 8 && found != true) {
		nextRow = row + move[dir].vert;
		nextCol = col + move[dir].horiz;

		if (nextRow == numRow && nextCol == numCol) {
			insert(&r[row], r[row], row, col);
			found = true;
		}
		else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {

			pos.row = row; pos.col = col; pos.dir = ++dir;

			insert(&r[row], r[row], row, col);

			mark[nextRow][nextCol] = 1;

			push(pos);

			row = nextRow; col = nextCol; dir = 0;
		}
		else ++dir;
	}
	insert(&r[nextRow], r[nextCol], nextRow, nextCol);
	printMaze();
	askIfContinue();
}

void printMaze() {
	printf("row/col ");
	for (int i = 1; i < numCol + 1; i++)
	{
		printf("%d ", i);
	}
	putchar('\n');
	for (int i = 1; i < numRow + 1; i++)
	{
		for (listPtr t = r[i]; t != NULL; t = t->link) {
			check_maze[i][t->col] = 1;
		}
		printf("   %d    ", i);
		for (int j = 1; j < numCol + 1; j++) {
			if (r[i] != NULL) {
				if (maze[i][j] == 1)
					printf("x ");
				if (maze[i][j] == 0 && check_maze[i][j] == 1)
					printf("* ");
				if (maze[i][j] == 0 && check_maze[i][j] == 0)
					printf("  ");
			}
			else if (r[i] == NULL) {
				if (maze[i][j] == 1)
					printf("x ");
				if (maze[i][j] == 0 && check_maze[i][j] == 0)
					printf("  ");
			}
		}
		putchar('\n');
	}
}

void push(position item) {
	stackPtr temp;
	temp = (stackPtr)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = top;
	top = temp;
}

position pop() {
	stackPtr temp = top;
	position item;
	if (!temp)
		return top->data;
	item = temp->data;
	top = temp->link;
	free(temp);
	return item;
}

int main() {
	setup_maze();
	path();

	return 0;
}