/*Develop a C program for a Doubly Linked List representing a sequence of web pages visited by a user. The program should insert a new page, 
move forward and backward, delete a specified page, and display the pages from first-to-last and last-to-first while handling beginning and 
end conditions correctly.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
struct Node {
    char page[MAX];
    struct Node *prev;
    struct Node *next;
};
struct Node *head = NULL;
struct Node *tail = NULL;
struct Node *current = NULL;
struct Node* createNode(char page[]) {
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(newNode->page, page);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void insertPage() {
    char page[MAX];
    struct Node *newNode;
    printf("Enter web page name: ");
    scanf("%99s", page);
    newNode = createNode(page);
    if (newNode == NULL)
        return;
    if (head == NULL) {
        head = tail = current = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        current = newNode;
    }
    printf("Page inserted successfully.\n");
}
void moveForward() {
    if (current == NULL) {
        printf("No pages in history.\n");
    }
    else if (current->next == NULL) {
        printf("Already at the last page.\n");
    }
    else {
        current = current->next;
        printf("Moved forward to: %s\n", current->page);
    }
}
void moveBackward() {
    if (current == NULL) {
        printf("No pages in history.\n");
    }
    else if (current->prev == NULL) {
        printf("Already at the first page.\n");
    }
    else {
        current = current->prev;
        printf("Moved backward to: %s\n", current->page);
    }
}
void displayForward() {
    struct Node *temp = head;
    if (head == NULL) {
        printf("History is empty.\n");
        return;
    }
    printf("First to Last:\n");
    while (temp != NULL) {
        printf("%s", temp->page);
        if (temp->next != NULL)
            printf(" <-> ");
        temp = temp->next;
    }
    printf("\n");
}
void displayBackward() {
    struct Node *temp = tail;
    if (tail == NULL) {
        printf("History is empty.\n");
        return;
    }
    printf("Last to First:\n");
    while (temp != NULL) {
        printf("%s", temp->page);
        if (temp->prev != NULL)
            printf(" <-> ");
        temp = temp->prev;
    }
    printf("\n");
}
void deletePage() {
    char page[MAX];
    struct Node *temp;
    printf("Enter page to delete: ");
    scanf("%99s", page);
    temp = head;
    while (temp != NULL &&
           strcmp(temp->page, page) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Page not found. Cannot delete.\n");
        return;
    }
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;
    if (temp == current) {
        if (temp->next != NULL)
            current = temp->next;
        else
            current = temp->prev;
    }
    free(temp);
    printf("Page deleted successfully.\n");
}
int main() {
    int choice;
    while (1) {
        printf("\n--- WEB PAGE HISTORY ---\n");
        printf("1. Insert New Page\n");
        printf("2. Move Forward\n");
        printf("3. Move Backward\n");
        printf("4. Delete Page\n");
        printf("5. Display First to Last\n");
        printf("6. Display Last to First\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insertPage();
                break;
            case 2:
                moveForward();
                break;
            case 3:
                moveBackward();
                break;
            case 4:
                deletePage();
                break;
            case 5:
                displayForward();
                break;
            case 6:
                displayBackward();
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
