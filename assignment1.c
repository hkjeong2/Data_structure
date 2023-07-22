#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEGREE 100
#define MAX_TERMS 100

typedef struct {
	int degree;
	int coef[MAX_DEGREE + 1];
}Polynomial_CoefArray;

typedef struct {
	int exp;
	int coef;
}Term;

typedef struct {
	int num_terms;
	Term term[MAX_TERMS];
}Polynomial_TermArray;

void padd_h(Polynomial_TermArray* polynomial, Polynomial_CoefArray* b, int startA, int finishA, int startB, int startD);
Polynomial_TermArray attach_TermArray(Polynomial_TermArray* polynomial, int startD, int coefficient, int exponent);
int IsZero_CoefArray(int startB);
int Coef_TermArray(Polynomial_TermArray* polynomial, int exp);
int Coef_CoefArray(Polynomial_CoefArray* b, int exp);
int LeadExp_CoefArray(Polynomial_CoefArray* b, int startB);
int Remove_CoefArray(Polynomial_CoefArray* b, int startB);
int COMPARE(int a, int b);

void padd_h(Polynomial_TermArray* polynomial, Polynomial_CoefArray* b, int startA, int finishA, int startB, int startD)
{
	int coefficient = 0;

	while (IsZero_CoefArray(startB) == 0 && startA <= finishA)
	{
		switch (COMPARE(polynomial->term[startA].exp, LeadExp_CoefArray(b, startB)))
		{
		case -1:
		{
			*polynomial = attach_TermArray(polynomial, startD, Coef_CoefArray(b, LeadExp_CoefArray(b, startB)), LeadExp_CoefArray(b, startB));
			startB = Remove_CoefArray(b, startB);
			startD++;
			break;
		}

		case 0:
		{
			coefficient = Coef_TermArray(polynomial, startA) + Coef_CoefArray(b, LeadExp_CoefArray(b, startB));

			if (coefficient != 0)
			{
				attach_TermArray(polynomial, startD, coefficient, polynomial->term[startA].exp);
				startD++;
			}
			startA++;
			startB = Remove_CoefArray(b, startB);
			break;
		}

		case 1:
		{
			*polynomial = attach_TermArray(polynomial, startD, polynomial->term[startA].coef, polynomial->term[startA].exp);
			startA++;
			startD++;
		}
		}
	}

	for (; startA <= finishA; startA++)
	{
		*polynomial = attach_TermArray(polynomial, startD, polynomial->term[startA].coef, polynomial->term[startA].exp);
		startD++;
	}
	while (IsZero_CoefArray(startB) == 0)
	{
		*polynomial = attach_TermArray(polynomial, startD, Coef_CoefArray(b, LeadExp_CoefArray(b, startB)), LeadExp_CoefArray(b, startB));
		startB = Remove_CoefArray(b, startB);
		startD++;
	}

}
Polynomial_TermArray attach_TermArray(Polynomial_TermArray* polynomial, int startD, int coefficient, int exponent)
{
	polynomial->term[startD].coef = coefficient;
	polynomial->term[startD].exp = exponent;

	return *polynomial;
}

int IsZero_CoefArray(int startB)
{
	if (startB == -1)
		return 1;
	else
		return 0;
}
int Coef_TermArray(Polynomial_TermArray* a, int exp)
{
	return a->term[exp].coef;
}
int Coef_CoefArray(Polynomial_CoefArray* b, int exp)
{
	return b->coef[(b->degree) - 1 - exp];
}

int LeadExp_CoefArray(Polynomial_CoefArray* b, int startB)
{
	return (b->degree) - 1 - startB;
}

int Remove_CoefArray(Polynomial_CoefArray* b, int startB)
{
	startB++;

	while (1)
	{
		if (startB > (b->degree) - 1)
		{
			return -1;
			break;
		}
		else if (b->coef[startB] != 0)
		{
			return startB;
			break;
		}
		else
			startB++;
	}
}

int COMPARE(int a, int b)
{
	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}

int main()
{
	Polynomial_TermArray Polynomial = { 0 };
	Polynomial_CoefArray B = { 0 };

	int CoefArray_NumofTerms = 0;
	int TempForCoef = 0;
	int TempForExp = 0;
	int startA = 0, finishA = 0, startB = 0, startD = 0;

	while (1)
	{
		printf("Enter A(x): (입력한 항의 개수가 0일 시 종료)\n");
		printf("계수가 0이 아닌 항의 수?: ");
		scanf_s("%d", &Polynomial.num_terms);

		if (Polynomial.num_terms == 0)
		{
			printf("프로그램을 종료합니다\n");
			break;
		}

		for (int i = 0; i < Polynomial.num_terms; i++)
		{
			printf("계수?: ");
			scanf_s("%d", &Polynomial.term[i].coef);
			printf("지수?: ");
			scanf_s("%d", &Polynomial.term[i].exp);
		}

		printf("\n");
		printf("Enter B(x): \n");
		printf("계수가 0이 아닌 항의 수?: ");
		scanf_s("%d", &CoefArray_NumofTerms);

		for (int i = 0; i < CoefArray_NumofTerms; i++)
		{
			printf("계수?: ");
			scanf_s("%d", &TempForCoef);
			printf("지수?: ");
			scanf_s("%d", &TempForExp);

			if (i == 0)
				B.degree = TempForExp + 1;

			B.coef[B.degree - 1 - TempForExp] = TempForCoef;
		}

		printf("\n");
		printf("A(x) 입력 결과\n\n");
		printf("   계수    지수\n");

		for (int i = 0; i < Polynomial.num_terms; i++)
		{
			printf("%7d\t%7d\n", Polynomial.term[i].coef, Polynomial.term[i].exp);
		}

		printf("\n");
		printf("B(x) 입력 결과\n\n");
		printf("   계수    지수\n");

		for (int i = 0; i < B.degree; i++)
		{
			if (B.coef[i] != 0)
				printf("%7d\t%7d\n", B.coef[i], B.degree - i - 1);
		}

		startA = 0;
		finishA = Polynomial.num_terms - 1;
		startB = 0;
		startD = finishA + 1;

		Polynomial.num_terms = Polynomial.num_terms + CoefArray_NumofTerms;

		padd_h(&Polynomial, &B, startA, finishA, startB, startD);

		printf("\n");
		printf("D(x) = A(x) + B(x) 결과\n\n");
		printf("   계수    지수\n");
		for (int i = startD; i < startD + Polynomial.num_terms; i++)
		{
			if (Polynomial.term[i].coef == 0)
				break;
			printf("%7d\t%7d\n", Polynomial.term[i].coef, Polynomial.term[i].exp);
		}
		printf("\n");

		for (int i = 0; i < MAX_DEGREE + 1; i++)
		{
			B.coef[i] = 0;
		}
		for (int i = 0; i < MAX_TERMS; i++)
		{
			Polynomial.term[i].coef = 0;
			Polynomial.term[i].exp = 0;
		}
	}

}

