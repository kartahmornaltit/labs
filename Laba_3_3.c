#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <string.h>

#define MAXSTRSIZE 50
#define MAXNAMESIZE 30
#define histogramSize 10



typedef struct paymentList {
	int year;
	int month;
	int sum;
	struct paymentList *next;
} paymentList;

typedef struct namesList {
	struct namesList *prev;
	char name[MAXNAMESIZE];
	int paymentCount;
	int paymentSum;
	paymentList* payments;
	struct namesList *next;
}namesList;

typedef struct inputList {
	char name[MAXNAMESIZE];
	int year;
	int month;
	int day;
	int payment;
}inputList;

typedef struct dBlock {
	int value;
	int count;
	int low;
	int high;
}dBlock;

namesList *first = NULL;

void inputFunc(FILE *inputFile, inputList *value)
{
	unsigned int col;
	char* pos;
	char scan[MAXSTRSIZE];

	if (NULL == fgets(scan, sizeof(scan), inputFile)) return;
	pos = strchr(scan, ';');
	col = pos - scan;
	memcpy(value->name, scan, col);
	value->name[col] = '\0';

	value->day = atoi(scan + col + 1);

	pos = strchr(scan + col, '.');
	col = pos - scan + 1;

	value->month = atoi(scan + col);

	pos = strchr(scan + col, '.');
	col = pos - scan + 1;

	value->year = atoi(scan + col);

	pos = strchr(scan + col, ';');
	col = pos - scan + 1;

	value->payment = atoi(scan + col);
}

namesList *createName(inputList *value) {
	namesList* newName;

	newName = (namesList*)malloc(sizeof(namesList));
	memcpy(newName->name, value->name, MAXNAMESIZE);
	newName->prev = NULL;
	newName->next = NULL;
	newName->paymentCount = 1;
	newName->paymentSum = value->payment;
	newName->payments = createPayment(value);
	return newName;
}

paymentList *createPayment(inputList *value) {
	paymentList* newPayment;

	newPayment = (paymentList*)malloc(sizeof(paymentList));
	newPayment->year = value->year;
	newPayment->month = value->month;
	newPayment->sum = value->payment;
	newPayment->next = NULL;
	return newPayment;
}



void addNewName(namesList *name, inputList *value, int *pointer) {
	namesList *NewName = NULL;

	NewName = (namesList*)malloc(sizeof(namesList));
	if ((name->next == NULL) && (*pointer == 3)) {
		name->next = NewName;
		NewName->prev = name;
		NewName->next = NULL;
	}
	else if (*pointer == 1) {
		NewName->prev = NULL;
		NewName->next = first;
		first->prev = NewName;
		first = NewName;
	}
	else {
		NewName->next = name;
		NewName->prev = name->prev;

		(name->prev)->next = NewName;
		name->prev = NewName;
	}
	memcpy(NewName->name, value->name, MAXNAMESIZE);
	NewName->paymentCount = 1;
	(NewName->paymentSum) = value->payment;
	NewName->payments = createPayment(value);
}


void addNemPayment(namesList *name, paymentList *payment, inputList *values) {
	paymentList *NewPayment = NULL;

	NewPayment = (paymentList*)malloc(sizeof(paymentList));

	payment->next = NewPayment;
	NewPayment->next = NULL;
	NewPayment->sum = values->payment;
	NewPayment->month = values->month;
	NewPayment->year = values->year;

	name->paymentCount++;
	name->paymentSum += values->payment;
}


namesList *namesCheck(namesList * const startPoint, char name[MAXNAMESIZE], int *pointer) {
	char scan[MAXNAMESIZE];
	namesList *pkey = startPoint;

	unsigned int scanLength;
	unsigned int nameLength;
	unsigned int length;

	nameLength = (strchr(name, '\0') - name);
	*pointer = 2;


	do {
		memcpy(scan, pkey->name, MAXNAMESIZE);
		scanLength = (strchr(scan, '\0') - scan);
		if (scanLength == nameLength)
			if (!strncmp(scan, name, nameLength)) {
				*pointer = 0;
				return pkey;
			}
		length = (scanLength > nameLength ? nameLength : scanLength);
		if ((0 < strncmp(name, scan, length)) && (pkey->next == NULL)) {
			*pointer = 3;
			return pkey;
		}
		if ((0 > strncmp(name, scan, length)) && (pkey->prev == NULL)) {
			*pointer = 1;
			return pkey;
		}
		if (0 > strncmp(name, scan, length)) return pkey;
		if (pkey->next != NULL) pkey = pkey->next;
	} while (1);
}


paymentList *paymentsCheck(paymentList * const startPoint, inputList *date, int *pointer) {
	paymentList *pkey = startPoint;

	*pointer = 0;
	do {
		if ((pkey->month == date->month) && (pkey->year == date->year)) {
			*pointer = 1;
			return pkey;
		}
		if (pkey->next != NULL) pkey = pkey->next;
	} while (pkey->next != NULL);
	return pkey;
}


void insertPayment(namesList *inPoint, paymentList *keyElement, inputList *values) {
	inPoint->paymentSum += values->payment;
	keyElement->sum += values->payment;
}

void relocateDate(inputList *values, namesList *startPoint) {
	namesList *nPoint;
	paymentList *pPoint;
	int pointer = 0;

	nPoint = namesCheck(startPoint, values->name, &pointer);
	if (!pointer) {
		pPoint = paymentsCheck(nPoint->payments, values, &pointer);
		if (pointer) insertPayment(nPoint, pPoint, values);
		else addNemPayment(nPoint, pPoint, values);
	}
	else
		addNewName(nPoint, values, &pointer);
}

void bubbleSort(int *values, int valuesCount) {
	int i, j, swap = 0;
	for (i = 0; i < valuesCount - 1; i++)
		for (j = 0; j < valuesCount - i - 1; j++)
			if (values[j] > values[j + 1]) {
				swap = values[j];
				values[j] = values[j + 1];
				values[j + 1] = swap;
			}
}

dBlock *decimalDistribution(int *mediumValues, int valuesCount) {
	int dPoint, tdPoint, i = 0, j = -1;
	dBlock *decimalValues;

	dPoint = mediumValues[valuesCount - 1];
	while (dPoint > 100) {
		i++;
		dPoint = dPoint / 10;
	}
	if (dPoint / 10 < 5) dPoint = dPoint / 10 * 10 + 5;
	else if (dPoint / 10 > 5) dPoint = (dPoint / 10 + 1) * 10;
	dPoint = dPoint*((int)pow(10, i)) / 10;

	tdPoint = 0;
	decimalValues = (dBlock*)malloc(sizeof(dBlock) * 10);

	for (i = 0; i < valuesCount; i++) {
		if (mediumValues[i] > tdPoint) {
			j++;
			decimalValues[j].low = tdPoint;
			tdPoint += dPoint;
			decimalValues[j].high = tdPoint;

			decimalValues[j].value = 0;
			decimalValues[j].count = 0;
			i--;
			continue;
		}
		decimalValues[j].value += mediumValues[i];
		decimalValues[j].count++;

	}
	return decimalValues;
}

void printHist(dBlock *decimalBlocks, int numberOfElements) {
	int i, j, histPercent;

	histPercent = numberOfElements / histogramSize;
	i = 1;
	do {
		if (histPercent >= i) histPercent += (i * 10 - histPercent % 10);
		i *= 10;
	} while ((i * 10) < histPercent);
	printf("histogram with <=%d elements in one line\n", histPercent);

	for (i = 0; i < 10; i++) {
		if (decimalBlocks[i].count) {
			for (j = 0; j <= (decimalBlocks[i].count / histPercent); j++) {
				printf("%c", '|');
			}
			printf("   in %d-%d\n", decimalBlocks[i].low, decimalBlocks[i].high);
		}
	}
}

int DecileCoefficient(int *mediumValues, int numberOfElements)
{
	int i, j, moneyOfTheGods = 0, moneyOfThePaupers = 0, DecileCoeff;

	j = numberOfElements - 1;
	for (i = 0; i < numberOfElements / 10; i++) {
		moneyOfTheGods += mediumValues[j];
		moneyOfThePaupers += mediumValues[i];
		j--;
	}
	moneyOfTheGods /= (numberOfElements / 10);
	moneyOfThePaupers /= (numberOfElements / 10);
	DecileCoeff = moneyOfTheGods / moneyOfThePaupers;
	return DecileCoeff;
}

double giniCoefficient(int *mediumValues, int numberOfElements, int accumulate) {
	int i, j, groupSize, Thirds[3] = { 0,0,0 };
	double giniCoeff = 1, firstSum = 0, secondSum = 0;
	double CThirds[3];

	groupSize = numberOfElements / 3;

	for (i = 0; i < numberOfElements; i++) {
		if (i <= groupSize) Thirds[0] += mediumValues[i];
		else if ((i > groupSize) && (i <= groupSize * 2)) Thirds[1] += mediumValues[i];
		else Thirds[2] += mediumValues[i];
	}
	for (i = 0; i < 3; i++) {
		CThirds[i] = (double)Thirds[i] / (double)accumulate;
	}
	for (i = 0; i < 3; i++) {
		firstSum += 0.333*(CumProportion(CThirds, (i + 1)));
		secondSum += 0.333*CThirds[i];
	}

	giniCoeff = 1 - 2 * firstSum + secondSum;
	return giniCoeff;
}

double CumProportion(double *values, int col) {
	int i;
	double CumPro = 0;

	for (i = 0; i < col; i++)
		CumPro += values[i];
	return CumPro;
}


int main() {
	FILE *inputFile;

	int *mediumValues = NULL;
	dBlock *decimalBlocks = NULL;
	inputList values;
	char *scan;
	int i, numberOfElements, debug = 0, accumulate = 0;
	namesList *testValues;

	inputFile = fopen("salary.csv", "rt");

	scan = (char*)malloc(sizeof(char)*MAXSTRSIZE);
	fgets(scan, sizeof(scan)*MAXSTRSIZE, inputFile);
	free(scan);

	inputFunc(inputFile, &values);

	first = createName(&values);


	while (!feof(inputFile)) {
		inputFunc(inputFile, &values);
		relocateDate(&values, first);
	}

	testValues = first;
	i = 0;

	while (1) {
		mediumValues = (int*)realloc(mediumValues, sizeof(int)*i + 1);
		mediumValues[i] = testValues->paymentSum / testValues->paymentCount;
		accumulate += mediumValues[i];
		if (i > 0)
		{
			if (mediumValues[i - 1] != debug) mediumValues[i - 1] = debug;
		}
		debug = mediumValues[i];

		i++;
		if (testValues->next == NULL) break;
		testValues = testValues->next;
	}
	numberOfElements = i;
	bubbleSort(mediumValues, numberOfElements);

	decimalBlocks = decimalDistribution(mediumValues, numberOfElements);
	printHist(decimalBlocks, numberOfElements);


	printf("Gini: %.3lf\n", giniCoefficient(mediumValues, numberOfElements, accumulate));
	printf("Decile: %d\n", DecileCoefficient(mediumValues, numberOfElements));
	printf("Median: %d\n", mediumValues[numberOfElements / 2]);
	fclose(inputFile);
	return 0;
}
