#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_RECORDS 1000
#define MAX_NAME_LENGTH 50
#define MAX_NIM_LENGTH 20

// Struktur untuk menyimpan NIM dan NAMA
typedef struct {
    char nim[MAX_NIM_LENGTH];
    char nama[MAX_NAME_LENGTH];
} Data;

// Fungsi untuk memuat data dari file
int loadData(const char *filename, Data data[], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s.\n", filename);
        return 0;
    }
    *count = 0;
    while (fscanf(file, "%[^,],%[^\n]\n", data[*count].nim, data[*count].nama) == 2) {
        (*count)++;
    }
    fclose(file);
    return 1;
}

// Fungsi pencarian substring case-insensitive
char *strcasestr_custom(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;

    for (const char *h = haystack; *h; h++) {
        const char *n = needle;
        const char *p = h;
        while (*p && *n && tolower((unsigned char)*p) == tolower((unsigned char)*n)) {
            p++;
            n++;
        }
        if (!*n) return (char *)h;
    }
    return NULL;
}

// Fungsi untuk pencarian berdasarkan NIM atau NAMA
void search(Data data[], int count, const char *field, const char *value) {
    clock_t start = clock();
    int found = 0;
    for (int i = 0; i < count; i++) {
        if ((strcmp(field, "NIM") == 0 && strcasestr_custom(data[i].nim, value)) ||
            (strcmp(field, "NAMA") == 0 && strcasestr_custom(data[i].nama, value))) {
            printf("%s\t%s\n", data[i].nim, data[i].nama);
            found = 1;
        }
    }
    if (!found) {
        printf("No records found.\n");
    }
    clock_t end = clock();
    printf("Total time %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Command error. You need a data file as arguments.\n");
        return 1;
    }

    Data data[MAX_RECORDS];
    int count;
    
    if (!loadData(argv[1], data, &count)) {
        return 1;
    }

    char command[100];
    while (1) {
        printf("Your command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // menghapus newline

        if (strcmp(command, "berhenti") == 0) {
            break;
        } else if (strncmp(command, "cari ", 5) == 0) {
            char field[10], value[MAX_NAME_LENGTH];
            if (sscanf(command + 5, "%s %[^\n]", field, value) == 2) {
                if (strcmp(field, "NIM") == 0 || strcmp(field, "NAMA") == 0) {
                    search(data, count, field, value);
                } else {
                    printf("Syntax error. Should only cari NIM/NAMA value\n");
                }
            } else {
                printf("Syntax error. Should only cari NIM/NAMA value\n");
            }
        } else {
            printf("Syntax error. Should only cari NIM/NAMA value\n");
        }
    }
    return 0;
}
