#ifndef DATA_H
#define DATA_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct Node {
    char name[100];
    int price;
    Date productionDate;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int count;
} List;

// Function to initialize list
void initList(List* list);

// Function to validate date
int isValidDate(int day, int month, int year);

// Function to parse date string
int parseDate(const char* dateStr, Date* date);

// Function to format price with dots
void formatPrice(int price, char* buffer);

#endif