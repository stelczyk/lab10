#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996 6387)
#define MAX_BUFOR 80

typedef struct stud {
	char* imie;
	char* nazwisko;
	int rok;
	char* adres;
	double stypendium;
	struct stud* n;
}STUDENT;

STUDENT* H;

FILE* fd = NULL;

void list1(FILE* plik)
{
	unsigned len;
	STUDENT* B = NULL, * P = NULL;
	char bufor[MAX_BUFOR];
	H = (STUDENT*)NULL;
	while (fgets(bufor, MAX_BUFOR, fd)) {
		B = (STUDENT*)malloc(sizeof(STUDENT));
		if (H == (STUDENT*)NULL)
		{
			H = B;
		}
		else
		{
			P->n = B;
		}
		B->n = (STUDENT*)NULL;

		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		B->imie = (char*)malloc(len);
		strcpy(B->imie, bufor);

		fgets(bufor, MAX_BUFOR, fd);
		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		B->nazwisko = (char*)malloc(len);
		strcpy(B->nazwisko, bufor);

		fgets(bufor, MAX_BUFOR, fd);
		B->rok = atoi(bufor);

		fgets(bufor, MAX_BUFOR, fd);
		len = (unsigned)strlen(bufor);
		bufor[len - 1] = '\0';
		B->adres = (char*)malloc(len);
		strcpy(B->adres, bufor);

		fgets(bufor, MAX_BUFOR, fd);
		B->stypendium = atof(bufor);
		P = B;
	}
}

void dispList1()
{
	STUDENT* w;
	w = H;
	if (H == NULL)
	{
		printf("Lista pusta");
		return;
	}

	for (w = H; w != (STUDENT*)NULL; w = w->n)
	{
		printf("%p   %p\n", w, w->n);
		printf("%12s| %12s| %4d| %25s| %7.2lf\n", w->imie, w->nazwisko, w->rok, w->adres, w->stypendium);
	}
}

void addTailList1() {
	STUDENT* new_node = (STUDENT*)malloc(sizeof(STUDENT));
	if (new_node == NULL) {
		printf("Blad, nie udalo sie zaalokowac pamieci\n");
		return;
	}

	char buffer[100];
	printf("podaj imie: ");
	scanf("%s", buffer);
	new_node->imie = strdup(buffer);

	printf("podaj nazwisko: ");
	scanf("%s", buffer);
	new_node->nazwisko = strdup(buffer);

	printf("podaj rok urodzenia: ");
	scanf("%d", &(new_node->rok));

	printf("podaj adres: ");
	scanf("%s", buffer);
	new_node->adres = strdup(buffer);

	printf("podaj kwote stypendium: ");
	scanf("%lf", &(new_node->stypendium));

	new_node->n = NULL;

	if (H == NULL) {
		H = new_node;
		return;
	}

	STUDENT* temp = H;
	while (temp->n != NULL) {
		temp = temp->n;
	}
	temp->n = new_node;
}

void addHeadList1() {
	STUDENT* new_node = (STUDENT*)malloc(sizeof(STUDENT));
	if (new_node == NULL) {
		printf("Blad, nie udalo sie zaalokowac pamieci\n");
		return;
	}

	char buffer[100];
	printf("podaj imie: ");
	scanf("%s", buffer);
	new_node->imie = strdup(buffer);

	printf("podaj nazwisko: ");
	scanf("%s", buffer);
	new_node->nazwisko = strdup(buffer);

	printf("podaj rok urodzenia: ");
	scanf("%d", &(new_node->rok));

	printf("podaj adres: ");
	scanf("%s", buffer);
	new_node->adres = strdup(buffer);

	printf("podaj kwote stypendium: ");
	scanf("%lf", &(new_node->stypendium));

	new_node->n = H;
	H = new_node;
}

STUDENT* max_s() {
	if (H == NULL) {
		printf("lista jest pusta\n");
		return NULL;
	}

	STUDENT* max_student = H;
	STUDENT* current = H->n;

	while (current != NULL) {
		if (current->stypendium > max_student->stypendium) {
			max_student = current;
		}
		current = current->n;
	}
	return max_student;
}

int lenList1() {
	int count = 0;
	STUDENT* current = H;

	while (current != NULL) {
		count++;
		current = current->n;	
	}
	return count;
}

void remHeadList1() {
	if (H == NULL) {
		printf("Lista jest pusta, brak elementów do usuniêcia.\n");
		return;
	}

	STUDENT* temp = H; 
	H = H->n; 
	free(temp->imie);
	free(temp->nazwisko);
	free(temp->adres);
	free(temp); 
	printf("Usuniêto element z pocz¹tku listy.\n");
}

void remTailList1() {
	if (H == NULL) {
		printf("Lista jest pusta, brak elementów do usuniêcia.\n");
		return;
	}

	
	if (H->n == NULL) {
		free(H->imie);
		free(H->nazwisko);
		free(H->adres);
		free(H);
		H = NULL;
		printf("Usuniêto ostatni element z listy (by³a jedynym elementem).\n");
		return;
	}

	
	STUDENT* current = H;
	while (current->n->n != NULL) {
		current = current->n;
	}

	
	STUDENT* temp = current->n;
	free(temp->imie);
	free(temp->nazwisko);
	free(temp->adres);
	free(temp);

	current->n = NULL; 
	printf("Usuniêto element z koñca listy.\n");
}

int main()
{
	

	fd = fopen("dane.txt", "r");
	if (fd == NULL) {
		printf("Nie mogê otworzyæ pliku dane.txt do odczytu!\n");
		getchar();
		exit(1);
	}

	list1(fd);
	dispList1(); puts("---------------------------------------------------------------------\n");
	printf("dodaj studenta na poczatek\n");
	addHeadList1();
	printf("dodaj studenta na koniec\n");
	addTailList1();
	dispList1(); puts("---------------------------------------------------------------------\n");
	STUDENT* max_student = max_s();
	if (max_student != NULL) {
		printf("Student z najwiêkszym stypendium:\n");
		printf("Imiê: %s\n", max_student->imie);
		printf("Nazwisko: %s\n", max_student->nazwisko);
		printf("Stypendium: %.2lf\n\n", max_student->stypendium);
	}
	int lenght = lenList1();
	printf("dlugosc listy = %d\n\n", lenght);
	remHeadList1();
	dispList1(); puts("---------------------------------------------------------------------\n");
	remTailList1();
	dispList1(); putchar('\n');

	return 0;

}