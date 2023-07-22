#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 30

typedef struct node* treePtr;
typedef struct node {
	char name;
	treePtr father, mother;
}node;
treePtr root = NULL;

treePtr queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

void insert(treePtr ptr, char name1, char link, char name2);
void checkIfFRootNull(treePtr ptr, char name1, char link, char name2);
void checkIfFirstNameOverlap(treePtr ptr, char name1, char link, char name2);
void checkIfNewRoot(treePtr ptr, char name1, char link, char name2);
void addq(treePtr ptr);
treePtr deleteq();
void levelOrder(treePtr ptr);
void input();

void insert(treePtr ptr, char name1, char link, char name2) {

	checkIfFRootNull(ptr, name1, link, name2);
	checkIfNewRoot(ptr, name1, link, name2);
	checkIfFirstNameOverlap(ptr, name1, link, name2);
}

void checkIfFRootNull(treePtr ptr, char name1, char link, char name2) {
	if (ptr == NULL) {
		treePtr temp1, temp2;
		temp1 = (treePtr)malloc(sizeof(node));
		temp1->name = name1;
		temp1->father = NULL;
		temp1->mother = NULL;
		temp2 = (treePtr)malloc(sizeof(node));
		temp2->name = name2;
		temp2->father = NULL;
		temp2->mother = NULL;
		if (link == 'F')
			temp1->father = temp2;
		else if (link == 'M')
			temp1->mother = temp2;
		root = temp1;
	}
}

void checkIfNewRoot(treePtr ptr, char name1, char link, char name2) {
	if (root->name == name2) {
		treePtr tmp;
		tmp = (treePtr)malloc(sizeof(node));
		tmp->name = name1;
		tmp->father = NULL;
		tmp->mother = NULL;
		if (link == 'F')
			tmp->father = ptr;
		else if (link == 'M')
			tmp->mother = ptr;
		root = tmp;
	}
}

void checkIfFirstNameOverlap(treePtr ptr, char name1, char link, char name2) {
	treePtr temp;
	temp = (treePtr)malloc(sizeof(node));
	temp->name = name2;
	temp->father = NULL;
	temp->mother = NULL;
	if (ptr) {
		if (ptr->name == name1) {
			if (link == 'F')
				ptr->father = temp;
			else if (link == 'M')
				ptr->mother = temp;
			return;
		}
		checkIfFirstNameOverlap(ptr->father, name1, link, name2);
		checkIfFirstNameOverlap(ptr->mother, name1, link, name2);
	}
}

void addq(treePtr ptr) {
	queue[++rear] = ptr;
}

treePtr deleteq() {
	return queue[++front];
}

void levelOrder(treePtr ptr) {
	if (!ptr)
		return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%c", ptr->name);
			if (ptr->father)
				addq(ptr->father);
			if (ptr->mother)
				addq(ptr->mother);
		}
		else {
			putchar('\n');
			front = 0, rear = 0;
			break;
		}
	}
}

void input() {
	char c[4] = { 0 };
	printf(">>\n");
	while (1) {
		printf(">>");
		gets_s(c, sizeof(c));
		if (c[0] == '$' && c[1] == '$' && c[2] == '$') {
			printf("terminating...\n");
			exit(0);
		}
		insert(root, c[0], c[1], c[2]);
		levelOrder(root);
	}
}

int main() {

	input();

	return 0;
}