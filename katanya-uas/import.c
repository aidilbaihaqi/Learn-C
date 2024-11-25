#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "import.h"

Node* addNode(List* list, const char* name, int price, Date date) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    strcpy(newNode->name, name);
    newNode->price = price;
    newNode->productionDate = date;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (!list->head) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
    return newNode;
}

int importFromCSV(const char* filename, List* list) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;

    char line[256];
    char name[100];
    int price;
    char dateStr[9];
    Date date;

    while (fgets(line, sizeof(line), file)) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;
        
        // Parse CSV line
        if (sscanf(line, "%[^,],%d,%s", name, &price, dateStr) == 3) {
            if (parseDate(dateStr, &date)) {
                addNode(list, name, price, date);
            }
        }
    }

    fclose(file);
    return 1;
}