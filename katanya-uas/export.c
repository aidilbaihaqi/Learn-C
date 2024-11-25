#include <stdio.h>
#include "export.h"

int exportToCSV(const char* filename, List* list) {
    FILE* file = fopen(filename, "w");
    if (!file) return 0;

    Node* current = list->head;
    while (current) {
        fprintf(file, "%s,%d,%02d-%02d-%02d\n",
                current->name,
                current->price,
                current->productionDate.day,
                current->productionDate.month,
                current->productionDate.year);
        current = current->next;
    }

    fclose(file);
    return 1;
}