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
    struct stud* p; // Wska�nik na poprzedni element
    struct stud* n; // Wska�nik na nast�pny element
} STUDENT;

STUDENT* H = NULL; // G�owa listy
STUDENT* T = NULL; // Ogon listy

FILE* fd = NULL;

// Funkcja wczytuj�ca dane z pliku do listy
void list2(FILE* plik) {
    unsigned len;
    STUDENT* B = NULL;
    char bufor[MAX_BUFOR];

    while (fgets(bufor, MAX_BUFOR, fd)) {
        B = (STUDENT*)malloc(sizeof(STUDENT));
        if (H == NULL) {
            H = T = B; // Je�li lista jest pusta, inicjalizujemy g�ow� i ogon
            B->p = NULL;
        }
        else {
            T->n = B; // Poprzedni ogon wskazuje na nowy element
            B->p = T; // Ustawiamy wska�nik na poprzedni element
            T = B; // Nowy element staje si� ogonem
        }
        B->n = NULL;

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
    }
}

// Funkcja wy�wietlaj�ca list�
void dispList2() {
    STUDENT* w = H;
    if (H == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    while (w != NULL) {
        printf("%p <- %p -> %p\n", w->p, w, w->n);
        printf("%12s| %12s| %4d| %25s| %7.2lf\n",
            w->imie, w->nazwisko, w->rok, w->adres, w->stypendium);
        w = w->n;
    }
}

// Dodanie elementu na pocz�tek listy
void addHeadList2() {
    STUDENT* new_node = (STUDENT*)malloc(sizeof(STUDENT));
    if (new_node == NULL) {
        printf("B��d: nie uda�o si� zaalokowa� pami�ci.\n");
        return;
    }

    char buffer[100];
    printf("Podaj imi�: ");
    scanf("%s", buffer);
    new_node->imie = strdup(buffer);

    printf("Podaj nazwisko: ");
    scanf("%s", buffer);
    new_node->nazwisko = strdup(buffer);

    printf("Podaj rok urodzenia: ");
    scanf("%d", &(new_node->rok));

    printf("Podaj adres: ");
    scanf("%s", buffer);
    new_node->adres = strdup(buffer);

    printf("Podaj kwot� stypendium: ");
    scanf("%lf", &(new_node->stypendium));

    new_node->p = NULL;
    new_node->n = H;

    if (H != NULL) {
        H->p = new_node;
    }
    else {
        T = new_node; // Je�li lista by�a pusta, ustawiamy ogon
    }

    H = new_node; // Nowy element staje si� g�ow�
    printf("Dodano element na pocz�tek listy.\n");
}

// Dodanie elementu na koniec listy
void addTailList2() {
    STUDENT* new_node = (STUDENT*)malloc(sizeof(STUDENT));
    if (new_node == NULL) {
        printf("B��d: nie uda�o si� zaalokowa� pami�ci.\n");
        return;
    }

    char buffer[100];
    printf("Podaj imi�: ");
    scanf("%s", buffer);
    new_node->imie = strdup(buffer);

    printf("Podaj nazwisko: ");
    scanf("%s", buffer);
    new_node->nazwisko = strdup(buffer);

    printf("Podaj rok urodzenia: ");
    scanf("%d", &(new_node->rok));

    printf("Podaj adres: ");
    scanf("%s", buffer);
    new_node->adres = strdup(buffer);

    printf("Podaj kwot� stypendium: ");
    scanf("%lf", &(new_node->stypendium));

    new_node->n = NULL;
    new_node->p = T;

    if (T != NULL) {
        T->n = new_node;
    }
    else {
        H = new_node; // Je�li lista by�a pusta, ustawiamy g�ow�
    }

    T = new_node; // Nowy element staje si� ogonem
    printf("Dodano element na koniec listy.\n");
}

// Usuni�cie elementu z pocz�tku listy
void remHeadList2() {
    if (H == NULL) {
        printf("Lista jest pusta, brak element�w do usuni�cia.\n");
        return;
    }

    STUDENT* temp = H;
    H = H->n;

    if (H != NULL) {
        H->p = NULL;
    }
    else {
        T = NULL; // Je�li lista sta�a si� pusta
    }

    free(temp->imie);
    free(temp->nazwisko);
    free(temp->adres);
    free(temp);

    printf("Usuni�to element z pocz�tku listy.\n");
}

// Usuni�cie elementu z ko�ca listy
void remTailList2() {
    if (T == NULL) {
        printf("Lista jest pusta, brak element�w do usuni�cia.\n");
        return;
    }

    STUDENT* temp = T;
    T = T->p;

    if (T != NULL) {
        T->n = NULL;
    }
    else {
        H = NULL; // Je�li lista sta�a si� pusta
    }

    free(temp->imie);
    free(temp->nazwisko);
    free(temp->adres);
    free(temp);

    printf("Usuni�to element z ko�ca listy.\n");
}

// Liczba element�w w li�cie
int lenList2() {
    int count = 0;
    STUDENT* current = H;
    while (current != NULL) {
        count++;
        current = current->n;
    }
    return count;
}

// Znalezienie studenta z najwi�kszym stypendium
STUDENT* max_s2() {
    if (H == NULL) {
        printf("Lista jest pusta.\n");
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

int main() {
    fd = fopen("dane.txt", "r");
    if (fd == NULL) {
        printf("Nie mog� otworzy� pliku dane.txt do odczytu!\n");
        return 1;
    }

    list2(fd);
    fclose(fd);

    dispList2();
    puts("---------------------------------------------------------------");

    printf("Dodaj studenta na pocz�tek:\n");
    addHeadList2();
    printf("Dodaj studenta na koniec:\n");
    addTailList2();
    dispList2();
    puts("---------------------------------------------------------------");

    STUDENT* max_student = max_s2();
    if (max_student != NULL) {
        printf("Student z najwi�kszym stypendium: %s %s, %.2lf\n",
            max_student->imie, max_student->nazwisko, max_student->stypendium);
    }

    printf("Liczba element�w w li�cie: %d\n", lenList2());

    remHeadList2();
    remTailList2();
    dispList2();

    return 0;
}
