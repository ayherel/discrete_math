/*
Сформировать два односвязных списка целых чисел. Готово

Слить их в односвязный циклический список. Наполовину готово
Сделать список циклическим. Дописать

Так чтобы узлы были 
расположены по возрастанию значений. Готово
*/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

struct Node {
    int value;
    struct Node *next;
};

typedef struct Node Node;

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("value = %d\n", current->value);
        printf("value adress = %p \n", &(current->value));
        current = current->next;
    }
}

// Функция для поиска узла с минимальным значением в двух списках
Node* find_min_node(Node *head_one, Node *head_two, int minimum) {
    Node *min_node = NULL;
    int min_value = 1000; // Начальное значение для минимума

    Node *current_one = head_one;
    Node *current_two = head_two;

    while (current_one != NULL) {
        if (((current_one->value) < min_value) && ((current_one->value) > minimum)) {
            min_value = current_one->value;
            min_node = current_one;
        }
        current_one = current_one->next;
    }

    while (current_two != NULL) {
        if (((current_two->value) < min_value) && ((current_two->value) > minimum)) {
            min_value = current_two->value;
            min_node = current_two;
        }
        current_two = current_two->next;
    }

    return min_node;
}


// Функция для добавления узла в конец списка
void append_node(Node **head, int value) {
    // Создаем новый узел
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(2);
    }
    new_node->value = value;
    new_node->next = NULL;

    // Если список пуст, новый узел становится головой списка
    if (*head == NULL) {
        *head = new_node;
    } else {
        // Иначе находим последний узел и добавляем новый узел в конец
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}


int main()
{
    srand((unsigned int)time(NULL));
    int length_sum = 0;
    Node *head = NULL;
    Node *head1 = NULL;
    Node *head2 = NULL;

    Node* minimaln_node;

    int min_value = 1;
    
    // Создаем и добавляем 10 узлов
    for (int i = 1; i <= 10; i++) {
        append_node(&head, (1 + rand()%100)); // Присваиваем каждому узлу значение случайное значение от 1 до 100
        length_sum++;
    }

    for (int i = 1; i <= 20; i++) {
        append_node(&head1, (1 + rand()%100)); // Присваиваем каждому узлу значение случайное значение от 1 до 100
        length_sum++;
    }
    length_sum++;


    printf("список [1]\n");
    print_list(head); // Выводим узлы списка 1

    
    printf("\n список [2] \n");
    print_list(head1); // Выводим узлы списка 2

    printf("\n общая длина списков= %d \n", length_sum);

    getch();


    //*******************************************************************
    for( int i=1; i<=length_sum; i++)
    {
        minimaln_node = find_min_node(head, head1, min_value);

        if (minimaln_node != NULL){
            min_value = minimaln_node->value;
            printf(" [%d] minimum adres = %p \n", i, minimaln_node);
            printf(" [%d] minimum value = %d \n", i, minimaln_node->value);
            append_node(&head2, minimaln_node->value);
        }
    }


   
    printf("\n список [3] \n");
    print_list(head2); // Выводим узлы списка 3


    // Освобождаем память
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    while (head1 != NULL) {
        Node *temp = head1;
        head1 = head1->next;
        free(temp);
    }

    while (head2 != NULL) {
        Node *temp = head2;
        head2 = head2->next;
        free(temp);
    }


    getch();

    return 0;
}
// Код завершения 0 - весь код выполнился (надеюсь нормально)
// Код завершения 1 - пока не придумал
// Код завершения 2 - нехватка памяти