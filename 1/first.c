#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
typedef struct Node {
    int value;
    struct Node* next;
} Node;

void print_list(Node* head) {
    while (head != NULL) {
        printf("%d (address: %p) \n", head->value, (void*)head);
        head = head->next;
    }
    printf("\n");
}

void merge_lists(Node **head1, Node **head2, Node **head3) {
    // Инициализируем голову третьего списка
    *head3 = NULL;

    // Если какой-либо из входных списков пуст, возвращаемся
    if (*head1 == NULL) {
        *head3 = *head2;
        return;
    }
    if (*head2 == NULL) {
        *head3 = *head1;
        return;
    }

    // Создаем голову третьего списка
    Node *current = NULL;
    Node *tail = NULL;

    // Объединяем узлы двух списков
    while (*head1 != NULL && *head2 != NULL) {
        // Сравниваем значения узлов
        if ((*head1)->value < (*head2)->value) {
            // Добавляем узел из первого списка в третий список
            Node *temp = *head1;
            *head1 = (*head1)->next;
            temp->next = NULL;
            if (*head3 == NULL) {
                *head3 = temp;
                tail = temp;
            } else {
                tail->next = temp;
                tail = temp;
            }
        } else {
            // Добавляем узел из второго списка в третий список
            Node *temp = *head2;
            *head2 = (*head2)->next;
            temp->next = NULL;
            if (*head3 == NULL) {
                *head3 = temp;
                tail = temp;
            } else {
                tail->next = temp;
                tail = temp;
            }
        }
    }

    // Добавляем оставшиеся узлы из первого списка
    while (*head1 != NULL) {
        Node *temp = *head1;
        *head1 = (*head1)->next;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }

    // Добавляем оставшиеся узлы из второго списка
    while (*head2 != NULL) {
        Node *temp = *head2;
        *head2 = (*head2)->next;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }

    // Создаем цикл, связывая последний узел с первым
    //tail->next = *head3;
}



void sort_list(Node **head) {
    Node *current = *head;
    Node *next = NULL;
    int temp;

    while (current != NULL) {
        next = current->next;
        while (next != NULL) {
            if (current->value > next->value) {
                temp = current->value;
                current->value = next->value;
                next->value = temp;
            }
            next = next->next;
        }
        current = current->next;
    }
}

void generate_list(Node** head, int size) {
    *head = (Node*)malloc(sizeof(Node));
    (*head)->value = rand() % 100 + 1;
    (*head)->next = NULL;

    Node* current = *head;
    for (int i = 1; i < size; i++) {
        current->next = (Node*)malloc(sizeof(Node));
        current->next->value = rand() % 100 + 1;
        current->next->next = NULL;
        current = current->next;
    }
}

int main() {
    srand(time(NULL)); // инициализируем генератор случайных чисел

    Node* head1 = NULL;
    generate_list(&head1, 5);
    sort_list(&head1);

    Node* head2 = NULL;
    generate_list(&head2, 10);
    sort_list(&head2);

    Node* head3 = NULL;

    printf("List 1: ");
    print_list(head1);
    printf("List 2: ");
    print_list(head2);

    merge_lists(&head1, &head2, &head3);

    printf("Merged List: ");
    print_list(head3);
    getch();
    return 0;
}
