#ifndef IMPORT_H
#define IMPORT_H

#include "data.h"

// Function to import data from CSV file
int importFromCSV(const char* filename, List* list);

// Function to add new node to list
Node* addNode(List* list, const char* name, int price, Date date);

#endif