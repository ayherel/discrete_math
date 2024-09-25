#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>

// Определение структуры узла
typedef struct Node {
    int data;
    struct Node *Next;
} Node;

// Определение структуры списка
typedef struct {
    Node *Head;
    Node *Tail;
    int count_Node;
} OneList;

// Определение итератора
typedef struct {
    Node *ptr;  // указатель на узел, на который указывает итератор
    OneList *list;  // указатель на список, к которому привязан итератор
} Iterator;

// Инициализация итератора
void init_iterator(Iterator *iter, OneList *list) {
    iter->ptr = list->Head;  // направляем итератор на первый узел списка
    iter->list = list;
}

// Установка итератора на первый элемент списка
Iterator begin(OneList *list) {
    Iterator iter;
    iter.list = list;
    iter.ptr = list->Head;
    return iter;
}

// Установка итератора на элемент списка, следующий за последним
Iterator end(OneList *list) {
    Iterator iter;
    iter.list = list;
    iter.ptr = NULL;
    return iter;
}

// Перевод итератора на следующий элемент списка от текущего
Iterator next(Iterator iter) {
    Iterator new_iter;
    new_iter.list = iter.list;
    new_iter.ptr = (iter.ptr != NULL) ? iter.ptr->Next : NULL;
    return new_iter;
}

// Перевод итератора на предыдущий элемент списка от текущего
Iterator prev(Iterator iter) {
    Iterator new_iter;
    new_iter.list = iter.list;
    new_iter.ptr = NULL;
    
    Node *current = iter.list->Head;
    while (current != NULL && current->Next != iter.ptr) {
        current = current->Next;
    }
    new_iter.ptr = current;
    return new_iter;
}

// Проверка, достигнут ли конец списка
bool is_done(Iterator iter) {
    return (iter.ptr == NULL);
}

// Возврат значения элемента списка, на который указывает итератор
int value(Iterator iter) {
    if (is_done(iter)) return 0;
    return iter.ptr->data;
}

// Функция добавления нового узла после текущего узла
bool add_Node_2(Iterator *iter, int data) {
    if (iter->ptr == iter->list->Tail) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) return false;
        newNode->data = data;
        newNode->Next = NULL;
        iter->list->Tail->Next = newNode;
        iter->list->Tail = newNode;
        iter->list->count_Node++;
        return true;
    }

    Node *temp = iter->list->Head;
    while (temp != NULL && temp->Next != iter->ptr) {
        temp = temp->Next;
    }

    if (temp == NULL) return false;

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return false;
    newNode->data = data;
    newNode->Next = iter->ptr->Next;
    temp->Next = newNode;
    iter->list->count_Node++;
    return true;
}

// Функция добавления узла в конец списка
void push_Tail(OneList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->data = data;
    newNode->Next = NULL;
    if (list->Tail == NULL) {
        list->Head = newNode;
        list->Tail = newNode;
    } else {
        list->Tail->Next = newNode;
        list->Tail = newNode;
    }
    list->count_Node++;
}

// Инициализация списка
OneList *init() {
    OneList *list = (OneList *)malloc(sizeof(OneList));
    if (list == NULL) return NULL;
    list->Head = NULL;
    list->Tail = NULL;
    list->count_Node = 0;
    return list;
}

// Вывод элементов списка с головы
void output(OneList *list) {
    Iterator iter;
    init_iterator(&iter, list);
    while (!is_done(iter)) {
        printf("%d\n", value(iter));
        iter = next(iter);
    }
}

// Основная функция
int main() {
    setlocale (LC_ALL, "Rus");

    // Объявляем список и инициализируем его
    OneList *list = init();
    if (list == NULL) {
        fprintf(stderr, "Ошибка инициализации списка\n");
        return 1;
    }

    // Заполняем список элементами с хвоста
    for (int i = 1; i <= 5; i++) {
        push_Tail(list, i);
    }

    // Выводим элементы списка
    printf("Элементы списка\n");
    output(list);

    // Объявляем итератор
    Iterator iter;

    // Инициализируем итератор
    init_iterator(&iter, list);

    // Устанавливаем итератор на начало списка
    iter = begin(list);
    printf("Первый элемент: %d\n", value(iter));

    // Устанавливаем итератор на следующий элемент после текущего
    iter = next(iter);
    printf("Следующий за текущим: %d\n", value(iter));

    // Устанавливаем итератор на предыдущий элемент от текущего
    iter = prev(iter);
    printf("Предыдущий перед текущим: %d\n", value(iter));

    // Добавляем элемент после текущего
    add_Node_2(&iter, 100);

    // Устанавливаем итератор на следующий элемент после текущего
    iter = next(iter);
    printf("Добавленный элемент после текущего: %d\n", value(iter));

    // Устанавливаем итератор на следующий после последнего
    iter = end(list);
    printf("Следующий после последнего: %d\n", value(iter));
    getchar();
    return 0;
}
