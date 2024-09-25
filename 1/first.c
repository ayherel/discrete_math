/*
Сформировать два односвязных списка целых чисел. 

Слить их в односвязный циклический список. 
Сделать список циклическим. Дописать

Так чтобы узлы были 
расположены по возрастанию значений. 
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


// (F1) - Функция для вывода элементов списка
void print_list(Node *head) {
    int flag = 0;
    Node *current = head;
    while (current != NULL) {
        printf("value = %d\n", current->value);
        printf("value adress = %p \n", &(current->value));
        current = current->next;
    if (flag == 1)
    //print_element_from_adres(&(current->value));
    flag++;
    }
}


    

// (для F2) - Вспомогательная функция для проверки, является ли узел уже добавленным в объединенный список
int is_added(Node *node, Node **added_nodes) {
    Node *current = *added_nodes;
    while (current != NULL) {
        if (current == node) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
    


// (для F2) - Вспомогательная функция для добавления узла в список добавленных узлов
void add_node_to_added(Node *node, Node **added_nodes) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = node->value;
    new_node->next = *added_nodes;
    *added_nodes = new_node;
}





// (F2) - Функция для поиска узла с минимальным значением в двух списках
Node* find_min_node(Node *head_one, Node *head_two, int minimum, Node *added_nodes) {
    Node *min_node = NULL;
    int min_value = 1000; // Начальное значение для минимума

    Node *current_one = head_one;
    Node *current_two = head_two;

    while (current_one != NULL) {
        if (((current_one->value) < min_value) && ((current_one->value) > minimum) && (!is_added(current_one, added_nodes))) {
            min_value = current_one->value;
            min_node = current_one;
        }
        current_one = current_one->next;
    }

    while (current_two != NULL) {
        if (((current_two->value) < min_value) && ((current_two->value) > minimum) && (!is_added(current_two, added_nodes))) {
            min_value = current_two->value;
            min_node = current_two;
        }
        current_two = current_two->next;
    }

    if (min_node != NULL) {
        add_node_to_added(min_node, added_nodes);
    }

    return min_node;
}



// (F3) - Функция для добавления узла в конец списка
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

/*
// (F4)- Функция для добавления узла в начало списка
void append_node_begin(Node **head, int value){
    Node *new_node =  (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(2);
    }
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}


// (F5)- Функция для добавления узла в произвольное место списка
void append_node_random(Node *head, int value){
    if (head == NULL){
        printf("Ошибка с узлом, предыдущий не можеть быть нулл");
        return 1;
    }

    Node *new_node =  (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(2);
    }
    new_node->value = value;
    new_node->next = head->next;
    head->next= new_node;
}

// (F6)- Функция для извлечения узла из начало списка
void extract_node_begin(Node **head){
    if (*head == NULL) {
       printf("Такой узел отсутствует");
    }
    Node *extract_node = *head;
    *head = extract_node->next;
    extract_node->next  = NULL;
    return extract_node;
}

// (F7)- Функция для извлечения узла из конца списка
void extract_node(Node **head){
    if (head == NULL) {
       printf("Такой узел отсутствует");
    }

    Node *current = *head;
    Node *prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    if (prev != NULL) {
        prev->next = NULL;
    } else {
        *head = NULL; // Список состоял из одного узла
    }
    return current;
}

// (F8)- Функция для извлечения узла из произвольной части списка
Node* extract_node_random(Node **head, Node *target_node) {
    if (*head == NULL || target_node == NULL) {
        return NULL;
    }
    Node *current = *head;
    Node *prev = NULL;
    while (current != target_node && current != NULL) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return NULL; // Узел не найден
    }
    if (prev != NULL) {
        prev->next = current->next;
    } else {
        *head = current->next; // Узел был первым в списке
    }
    current->next = NULL;
    return current;
}


// (F9)- Функция для извлечения узла из произвольной части списка
Node* extract_node_from_adress(Node *head, int index) {
    Node *current = head;
    int count = 0;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    if (count == index) {
        return current;
    } else {
        return NULL; // Индекс вне диапазона
    }
}
*/

int main()
{
    srand((unsigned int)time(NULL));
    int length_sum = 0;
    Node *head = NULL;
    Node *head1 = NULL;
    Node *head2 = NULL;
    Node *last_node = NULL;


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
        minimaln_node = find_min_node(head, head1, min_value, &head2);

        if (minimaln_node != NULL){
            min_value = minimaln_node->value;
            printf(" [%d] minimum adres = %p \n", i, minimaln_node);
            printf(" [%d] minimum value = %d \n", i, minimaln_node->value);
            append_node(&head2, minimaln_node->value);
            if (last_node == NULL){
                last_node = head2;
            }
        }
    }

    // Подключаем последний узел к первому узлу, чтобы сделать список циклическим
    last_node->next = head2;

    ///////////////////////
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
// Код завершения 1 - ошибка с узлами
// Код завершения 2 - нехватка памяти
