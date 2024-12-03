#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
// Определение структуры дерева
struct nodeDerevo {
    char data[50];
    struct nodeDerevo *left;
    struct nodeDerevo *right;
};
typedef struct nodeDerevo nodeDerevo;

// Функция для создания нового узла
nodeDerevo* newNode(char data[]) {
    nodeDerevo* node = (nodeDerevo*)malloc(sizeof(nodeDerevo));
    strcpy(node->data, data);
    node->left = node->right = NULL;
    return node;
}

// Функция для вставки элемента в дерево (без учета лексикографического порядка)
nodeDerevo* insert(nodeDerevo* nachaloDereva, char data[]) {
    if (nachaloDereva == NULL) {
        return newNode(data);
    }

    // Мы просто вставляем элементы произвольно: если нет левого потомка — вставляем туда, иначе — в правого
    if (nachaloDereva->left == NULL) {
        nachaloDereva->left = newNode(data);
    } else if (nachaloDereva->right == NULL) {
        nachaloDereva->right = newNode(data);
    } else {
        // Если оба поддерева заняты, добавляем в левое поддерево рекурсивно
        nachaloDereva->left = insert(nachaloDereva->left, data);
    }

    return nachaloDereva;
}

// Функция для поиска самого младшего общего предка (youngest)
nodeDerevo* findyoung(nodeDerevo* nachaloDereva, char data1[], char data2[]) {
    // Если дерево пустое, возвращаем NULL
    if (nachaloDereva == NULL) {
        return NULL;
    }

    // Если один из узлов совпадает с текущим, то текущий узел - это youngest
    if (strcmp(nachaloDereva->data, data1) == 0 || strcmp(nachaloDereva->data, data2) == 0) {
        return nachaloDereva;
    }

    // Ищем youngest в левом и правом поддереве
    nodeDerevo* left = findyoung(nachaloDereva->left, data1, data2);
    nodeDerevo* right = findyoung(nachaloDereva->right, data1, data2);

    // Если один узел найден в левом поддереве, а другой в правом, то корень - youngest
    if (left && right) {
        return nachaloDereva;
    }

    // Если оба узла находятся в одном из поддеревьев, возвращаем этот поддерево
    return left ? left : right;
}

// Функция для вывода дерева с отступами
void printDerevo(nodeDerevo* nachaloDereva, int otstup) {
    if (nachaloDereva == NULL) {
        return;
    }

    // Печатаем правое поддерево
    printDerevo(nachaloDereva->right, otstup + 1);

    // Печатаем текущий узел с отступами
    for (int i = 0; i < otstup; i++) {
        printf("\t");
    }
    printf("%s\n", nachaloDereva->data);

    // Печатаем левое поддерево
    printDerevo(nachaloDereva->left, otstup + 1);
}

int main() {
    nodeDerevo* nachaloDereva = NULL;

    // Вставляем элементы в дерево произвольно
    nachaloDereva = insert(nachaloDereva, "cat");
    insert(nachaloDereva, "catL");
    insert(nachaloDereva, "catR");
    insert(nachaloDereva, "catLL");
    insert(nachaloDereva, "catLR");
    insert(nachaloDereva, "catLLL");
    insert(nachaloDereva, "catLLR");

    // Печатаем дерево
    printf("Дерево поиска:\n");
    printDerevo(nachaloDereva, 0);

    // Находим и выводим youngest для двух строк
    char data1[] = "catR";
    char data2[] = "catLL";
    nodeDerevo* Derevo = findyoung(nachaloDereva, data1, data2);

    if (Derevo != NULL) {
        printf("\nyoungest predok for '%s' и '%s' : %s\n", data1, data2, Derevo->data);
    } else {
        printf("\nyoungest predok not found '%s' и '%s'.\n", data1, data2);
    }
    getch();
    return 0;
}
