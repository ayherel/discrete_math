#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
// Структура для представления узла в связном списке
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Функция для инициализации списка
void init_list(Node** head) {
    *head = NULL;
}

// Функция для перебора элементов списка и печати их значений
void traverse_list(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

// Функция для вставки узла в начало списка
void insert_at_beginning(Node** head, int value) {
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

// Функция для вставки узла в конец списка
void insert_at_end(Node** head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Функция для вставки узла в произвольную часть списка
void insert_at_position(Node** head, int value, int position) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;

    if (position == 0) {
        new_node->next = *head;
        *head = new_node;
    } else {
        Node* current = *head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Функция для удаления узла из начала списка
void delete_at_beginning(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Функция для удаления узла из конца списка
void delete_at_end(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* current = *head;
    Node* previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    if (previous == NULL) {
        *head = NULL;
    } else {
        previous->next = NULL;
    }
    free(current);
}

// Функция для удаления узла из произвольной части списка
void delete_at_position(Node** head, int position) {
    if (*head == NULL) {
        return;
    }
    if (position == 0) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    } else {
        Node* current = *head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

// Функция для доступа к узлу по индексу
int access_node(Node* head, int index) {
    Node* current = head;
    for (int i = 0; i < index; i++) {
        if (current == NULL) {
            return -1; // Индекс вне границ
        }
        current = current->next;
    }
    return current->value;
}

// Функция для удаления списка
void delete_list(Node** head) {
    Node* current = *head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Функция для проверки на пустоту списка
int is_empty(Node* head) {
    return head == NULL;
}

int main() {
    Node* head;
    init_list(&head);

    // Инициализация списка с 10 узлами, значения от 1 до 100
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        insert_at_end(&head, rand() % 100 + 1);
    }

    // Перебор элементов списка
    printf("перебор \n");
    traverse_list(head);

    // Вставка узла в начало списка
    printf("вставка в начало \n");
    insert_at_beginning(&head, 0);
    traverse_list(head);

    // Вставка узла в конец списка
    printf("вставка в конец \n");
    insert_at_end(&head, 0);
    traverse_list(head);

    // Вставка узла в произвольную часть списка
    printf("вставка в произвольную \n");
    insert_at_position(&head, 0, 5);
    traverse_list(head);

    // Удаление узла из начала списка
    printf("удаление из начала \n");
    delete_at_beginning(&head);
    traverse_list(head);

    // Удаление узла из конца списка
    printf("удаление из конца \n");
    delete_at_end(&head);
    traverse_list(head);

    // Удаление узла из произвольной части списка
    printf("удаление из произвольной части \n");
    delete_at_position(&head, 3);
    traverse_list(head);

    // Доступ к узлу по индексу
    printf("доступ по индексу \n");
    int value = access_node(head, 2);
    printf("Value at index 2: %d\n", value);

    // Удаление списка
    printf("удаление списка\n");
    delete_list(&head);

    // Проверка на пустоту списка
    printf("проверка на пустоту \n");
    if (is_empty(head)) {
        printf("List is empty\n");
    } else {
        printf("List is not empty\n");
    }
        getch();
    return 0;
}
