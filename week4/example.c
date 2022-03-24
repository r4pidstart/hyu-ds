#define _CRT_SECURE_NO_WARNINGS

#define BUFFSIZE 1024
#define MAX_EXP 100

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct poly_ {
	int coeffs[MAX_EXP + 1];
	int check[MAX_EXP + 1];
} poly;

void clearPoly(poly* A) {
	int i;
	for (i = 0; i < MAX_EXP + 1; i++) {
		A->check[i] = 0;
	}
}

poly createPoly(void) {
	poly res;
	int i;
	for (i = 0; i < MAX_EXP + 1; i++) {
		res.check[i] = 0;
	}

	return res;
}

void printPoly_impl(poly A, char* buffer) {
	int isFirst = 1;
	int noTermFlag = 1;
	int i;
	for (i = MAX_EXP; i >= 0; i--) {
		char buffTemp[BUFFSIZE] = "";
		if (A.check[i] == 1) {
			noTermFlag = 0;
			if (isFirst == 1 || A.coeffs[i] < 0) {
				sprintf(buffTemp, "%dx^%d", A.coeffs[i], i);
				strcat(buffer, buffTemp);
				isFirst = 0;
			}
			else if (A.coeffs[i] > 0) {
				sprintf(buffTemp, "+%dx^%d", A.coeffs[i], i);
				strcat(buffer, buffTemp);
			}
		}
	}

	if (noTermFlag == 1) {
		sprintf(buffer, "0");
	}
}

void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) {
	if (A->check[exp] == 1) {
		A->coeffs[exp] += coeff;
	}
	else if (A->check[exp] == 0) {
		A->check[exp] = 1;
		A->coeffs[exp] = coeff;
	}

	if (A->coeffs[exp] == 0) {
		A->check[exp] = 0;
	}
}

poly multiPoly(poly A, poly B) {
	poly res = createPoly();
	int i, j;
	for (i = 0; i < MAX_EXP + 1; i++) {
		if (A.check[i] != 1) continue;
		for (j = 0; j < MAX_EXP + 1; j++) {
			if (B.check[j] != 1) continue;

			addTerm(&res, i + j, A.coeffs[i] * B.coeffs[j]);
		}
	}

	return res;
}

int main() {

	return 0;
}
