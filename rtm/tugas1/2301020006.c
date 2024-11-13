#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// delimiter data pada setiap file menggunakan koma (,)

typedef struct {
    char NIM[20];  // pakai tipe data string karena tidak di kalkulasi
    char NAMA[100];
} Data;

int readData(const char *filename, Data **data) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file %s\n", filename);
        return -1;
    }

    int count = 0;
    char buffer[150];

    // Menghitung valid lines
    while (fgets(buffer, sizeof(buffer), file)) {
        // ngecheck apakah baris bukan hanya newline atau baris kosong
        if (strlen(buffer) > 1) {
            count++;
        }
    }
    rewind(file);

    *data = (Data *)malloc(count * sizeof(Data));
    int index = 0;

    // read data, mengabaikan newline atau baris kosong
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strlen(buffer) > 1) {
            sscanf(buffer, "%[^,],%[^\n]", (*data)[index].NIM, (*data)[index].NAMA);
            index++;
        }
    }

    fclose(file);
    return count;
}

void swap(Data *a, Data *b) {
    Data temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(Data *data, int low, int high, int ascending, int byNIM) {
    if (low < high) {
        const char *pivot = byNIM ? data[high].NIM : data[high].NAMA;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            int comparison = byNIM ? strcmp(data[j].NIM, pivot) : strcmp(data[j].NAMA, pivot);
            if ((ascending && comparison <= 0) || (!ascending && comparison >= 0)) {
                i++;
                swap(&data[i], &data[j]);
            }
        }
        swap(&data[i + 1], &data[high]);

        quickSort(data, low, i, ascending, byNIM);
        quickSort(data, i + 2, high, ascending, byNIM);
    }
}

void selectionSort(Data *data, int size, int ascending, int byNIM) {
    for (int i = 0; i < size - 1; i++) {
        int minMaxIndex = i;
        for (int j = i + 1; j < size; j++) {
            int comparison = byNIM ? strcmp(data[j].NIM, data[minMaxIndex].NIM) : strcmp(data[j].NAMA, data[minMaxIndex].NAMA);
            if ((ascending && comparison < 0) || (!ascending && comparison > 0)) {
                minMaxIndex = j;
            }
        }
        swap(&data[minMaxIndex], &data[i]);
    }
}

void merge(Data *data, int l, int m, int r, int ascending, int byNIM) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Data *L = (Data *)malloc(n1 * sizeof(Data));
    Data *R = (Data *)malloc(n2 * sizeof(Data));

    for (int i = 0; i < n1; i++)
        L[i] = data[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        int comparison = byNIM ? strcmp(L[i].NIM, R[j].NIM) : strcmp(L[i].NAMA, R[j].NAMA);
        if ((ascending && comparison <= 0) || (!ascending && comparison >= 0)) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Data *data, int l, int r, int ascending, int byNIM) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(data, l, m, ascending, byNIM);
        mergeSort(data, m + 1, r, ascending, byNIM);
        merge(data, l, m, r, ascending, byNIM);
    }
}

void insertionSort(Data *data, int size, int ascending, int byNIM) {
    for (int i = 1; i < size; i++) {
        Data key = data[i];
        int j = i - 1;
        while (j >= 0) {
            int comparison = byNIM ? strcmp(data[j].NIM, key.NIM) : strcmp(data[j].NAMA, key.NAMA);
            if ((ascending && comparison > 0) || (!ascending && comparison < 0)) {
                data[j + 1] = data[j];
                j--;
            } else {
                break;
            }
        }
        data[j + 1] = key;
    }
}

void printData(Data *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s %s\n", data[i].NIM, data[i].NAMA);
    }
}

void sortAndMeasure(Data *data, int size, int algorithm, int ascending, int byNIM) {
    clock_t start = clock();
    if (algorithm == 1) {
        quickSort(data, 0, size - 1, ascending, byNIM);
    } else if (algorithm == 2) {
        selectionSort(data, size, ascending, byNIM);
    } else if (algorithm == 3) {
        mergeSort(data, 0, size - 1, ascending, byNIM);
    } else if (algorithm == 4) {
        insertionSort(data, size, ascending, byNIM);
    }

    clock_t end = clock();
    printData(data, size);
    printf("Total time: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Command error. You need data file as arguments\n");
        return 1;
    }

    Data *data;
    int size = readData(argv[1], &data);
    if (size < 0) return 1;

    int choice, order, sortBy;
    while (1) {
        printf("\nMain Menu\n");
        printf("1. Quick Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Merge Sort\n");
        printf("4. Insertion Sort\n");
        printf("5. Quit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 5) break;
        if (choice < 1 || choice > 5) {
            printf("Wrong Input. Should only number from number 1 to number 5.\n");
            continue;
        }

        printf("\nOption\n");
        printf("1. Ascending order on NIM\n");
        printf("2. Descending order on NIM\n");
        printf("3. Ascending order on NAMA\n");
        printf("4. Descending order on NAMA\n");
        printf("Your choice: ");
        scanf("%d", &order);

        if (order < 1 || order > 4) {
            printf("Wrong input. Should only number from number 1 to number 4.\n");
            continue;
        }

        sortBy = (order <= 2);
        int ascending = (order == 1 || order == 3);

        sortAndMeasure(data, size, choice, ascending, sortBy);
    }

    free(data);
    return 0;
}
