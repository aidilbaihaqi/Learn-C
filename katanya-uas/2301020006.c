#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "import.h"
#include "export.h"

void initList(List* list) {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

int isValidDate(int day, int month, int year) {
    int maxDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;
    
    // Check for leap year and update February's days
    if (month == 2 && (year % 4 == 0)) {
        maxDays[1] = 29;
    }
    
    return day <= maxDays[month - 1];
}

int parseDate(const char* dateStr, Date* date) {
    int day, month, year;
    if (sscanf(dateStr, "%d-%d-%d", &day, &month, &year) != 3) {
        return 0;
    }
    if (!isValidDate(day, month, year)) {
        return 0;
    }
    date->day = day;
    date->month = month;
    date->year = year;
    return 1;
}

void formatPrice(int price, char* buffer) {
    sprintf(buffer, "%d", price);
    int len = strlen(buffer);
    int j = 0;
    char temp[20];
    
    for (int i = len - 1, count = 0; i >= 0; i--, count++) {
        if (count > 0 && count % 3 == 0) {
            temp[j++] = '.';
        }
        temp[j++] = buffer[i];
    }
    temp[j] = '\0';
    
    // Reverse the string
    for (int i = 0; i < j/2; i++) {
        char t = temp[i];
        temp[i] = temp[j-1-i];
        temp[j-1-i] = t;
    }
    
    strcpy(buffer, temp);
}

void displayMenu() {
    printf("\nMenu Masakan\n");
    printf("[\033[1;36m\033[1m1\033[0m] Input Data Baru\n");
    printf("[\033[1;36m\033[1m2\033[0m] Import Data Baru\n");
    printf("[\033[1;36m\033[1m3\033[0m] Browse Data\n");
    printf("[\033[1;36m\033[1m4\033[0m] Export ke CSV\n");
    printf("[\033[1;36m\033[1m9\033[0m] Berhenti Program\n");
    printf("Pilihan anda : ");
}

void inputNewData(List* list) {
    char choice;
    do {
        char name[100];
        int price;
        char dateStr[20];
        Date date;

        printf("\nMasukan Nama Masakan: ");
        scanf(" %[^\n]s", name);
        
        printf("Masukan Harga Jual : Rp. ");
        scanf("%d", &price);

        do {
            printf("Masukan Tanggal Produksi hari-bulan-tahun (00-00-00) : ");
            scanf("%s", dateStr);
            
            if (!parseDate(dateStr, &date)) {
                printf("\nMaaf, tanggal salah. Format yang diperbolehkan 00-00-00\n");
                printf("dimana hari-bulan-tahun\n");
                printf("Silahkan ulangi penginputan tanggal produksi.\n");
            }
        } while (!parseDate(dateStr, &date));

        addNode(list, name, price, date);

        printf("Masih ada data ? [Y / T ] : ");
        scanf(" %c", &choice);
    } while (toupper(choice) == 'Y');
}

void browseData(List* list) {
    if (!list->head) {
        printf("Tidak ada data untuk ditampilkan.\n");
        return;
    }

    Node* current = list->head;
    char choice;
    char priceStr[20];

    do {
        formatPrice(current->price, priceStr);
        printf("\nData ke %d dari %d\n", 
               (current->prev ? (list->count - (list->tail == current ? 0 : 1)) : 1), 
               list->count);
        printf("Nama masakan : %s\n", current->name);
        printf("Harga : Rp. %s\n", priceStr);
        printf("Tanggal Produksi : %02d-%02d-%02d\n", 
               current->productionDate.day,
               current->productionDate.month,
               current->productionDate.year);
        
        do {
            printf("Pilihan P / N / Q : ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            
            if (choice != 'P' && choice != 'N' && choice != 'Q') {
                printf("\nPilihan hanya boleh P untuk data sebelum, N untuk data\n");
                printf("sesudah atau Q untuk berhenti browsing data\n");
                printf("Silahkan ulangi\n");
            }
        } while (choice != 'P' && choice != 'N' && choice != 'Q');

        if (choice == 'P') {
            current = current->prev ? current->prev : list->tail;
        } else if (choice == 'N') {
            current = current->next ? current->next : list->head;
        }
    } while (choice != 'Q');
}

int main() {
    List list;
    initList(&list);
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputNewData(&list);
                break;
            case 2: {
                char filename[256];
                printf("\nMasukan path dan nama file CSV : ");
                scanf(" %[^\n]s", filename);
                if (!importFromCSV(filename, &list)) {
                    printf("\nFile tidak ditemukan atau path salah.\n");
                }
                break;
            }
            case 3:
                browseData(&list);
                break;
            case 4: {
                char filename[256];
                printf("\nMasukan Path dan nama file untuk di export data : ");
                scanf(" %[^\n]s", filename);
                if (!exportToCSV(filename, &list)) {
                    printf("\nGagal export file. Periksa nama file dan path apakah sudah betul.\n");
                }
                break;
            }
            case 9:
                printf("\nTerima kasih sudah menggunakan aplikasi keren ini.\n");
                break;
            default:
                printf("\nMaaf, pilihan salah. Hanya boleh 1, 2, 3, 4 atau 9\n");
                printf("Silahkan ulangi pilihan menu.\n");
        }
    } while (choice != 9);

    // Free memory
    Node* current = list.head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}