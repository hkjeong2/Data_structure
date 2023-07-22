#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 11
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
#define MAX_QUEUE 20

typedef struct element {
	int key;
	int numberOfPerson;
}element;

element heap[MAX_ELEMENTS];
int n = 0;
int waitingNumber = 9;
int waitingTable = 0;
int numberOfWaitingPerson = 0;
element queue[MAX_ELEMENTS - 1];
int rear = -1;
int front = -1;

void getCustomer();
void giveTables();
void pushHeap(element item, int* n);
element popHeap(int* n);
void pushQ(element item);
element popQ();
void startProgram();
void chooseOption();

void getCustomer() {
	int nInput = 0;
	element temp;
	printf("대기번호: %d\n", waitingNumber);
	printf("인원수?: ");
	scanf_s("%d", &nInput);
	getchar();
	temp.key = waitingNumber;
	temp.numberOfPerson = nInput;
	pushHeap(temp, &n);
	printf("식탁 대기수: %d\n", ++waitingTable);
	waitingNumber--;
	numberOfWaitingPerson++;
}

void giveTables() {
	int nTableSize = 0;
	element temp;
	printf("식탁 크기?: ");
	scanf_s("%d", &nTableSize);
	getchar();
	temp = popHeap(&n);
	if (temp.numberOfPerson <= nTableSize) {
		printf("배정:: 대기번호: %d 인원수: %d\n", temp.key, temp.numberOfPerson);
		printf("식탁 대기수: %d\n", --waitingTable);
		numberOfWaitingPerson--;
		return;
	}
	else {
		int count = 0;
		pushQ(temp);
		if (numberOfWaitingPerson == 1) {
			printf("배정불가::\n");
			printf("식탁 대기수: %d\n", waitingTable);
		}
		for (int i = 0; i < numberOfWaitingPerson - 1; i++) {
			temp = popHeap(&n);
			if (temp.numberOfPerson <= nTableSize) {
				printf("배정:: 대기번호: %d 인원수: %d\n", temp.key, temp.numberOfPerson);
				printf("식탁 대기수: %d\n", --waitingTable);
				numberOfWaitingPerson--;
				break;
			}
			else {
				pushQ(temp);
				count++;
				if (i == numberOfWaitingPerson - 2) {
					printf("배정불가::\n");
					printf("식탁 대기수: %d\n", waitingTable);
				}
			}
		}
		for (int i = 0; i < count + 1; i++) {
			temp = popQ();
			pushHeap(temp, &n);
		}
	}
}

void pushHeap(element item, int* n) {
	int i;
	if (HEAP_FULL(*n)) {
		printf("힙 용량이 초과했습니다\n");
		exit(-1);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element popHeap(int* n) {
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		printf("힙이 비어있습니다\n");
		exit(-1);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void pushQ(element item) {
	queue[++rear] = item;

}

element popQ() {
	return queue[++front];
}

void startProgram() {
	printf("Start of Program\n");
	printf("기능:\n");
	printf("0.종료 1.대기접수 2.식탁배정\n");
	printf("식탁 대기수: %d\n", waitingTable);
}

void chooseOption() {
	char cInput = 0;
	printf("-------------\n");
	printf("기능 선택?: ");
	cInput = getchar();
	getchar();
	if (cInput == '1')
		getCustomer();
	else if (cInput == '2')
		giveTables();
	else if (cInput == '0') {
		printf("End of Program\n");
		exit(0);
	}
}

int main() {
	startProgram();
	while (1) {
		chooseOption();
	}

	return 0;
}