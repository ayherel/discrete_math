#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

////////////////////////////////////////////////STACK////////////////////////////////////////////////
typedef struct Node {                                                                              //
    int value;                                                                                     //
    struct Node* next;                                                                             //
} Node;                                                                                            //
typedef struct Stack {                                                                             //
    Node* top;                                                                                     //
} Stack;                                                                                           //
// initial stack                                                                                   //
Stack* createStack() {                                                                             //
    Stack* stack = (Stack*)malloc(sizeof(Stack));                                                  //
    stack->top = NULL;                                                                             //
    return stack;                                                                                  //
}                                                                                                  //
// proverka stack                                                                                  //
int stackempty(Stack* stack) {                                                                     //
    return stack->top == NULL;                                                                     //
}                                                                                                  //
// func dlya sozdaniya novogo uzla                                                                 //
Node* createNode(int value) {                                                                      //
    Node* newNode = (Node*)malloc(sizeof(Node));                                                   //
    newNode->value = value;                                                                        //
    newNode->next = NULL;                                                                          //
    return newNode;                                                                                //
}                                                                                                  //
// dobavlenie elementa v stack                                                                     //
void push(Stack* stack, int value) {                                                               //
    Node* newNode = createNode(value);                                                             //
    newNode->next = stack->top;                                                                    //
    stack->top = newNode;                                                                          //
}                                                                                                  //
// udalenie elementa iz stack                                                                      //
int pop(Stack* stack) {                                                                            //
    if (stackempty(stack)) {                                                                       //
        printf("stack is empty\n");                                                                //
		getch();                                                                                   //
        exit(1);                                                                                   //
    }                                                                                              //
    Node* temp = stack->top;                                                                       //
    int value = temp->value;                                                                       //
    stack->top = stack->top->next;                                                                 //
    free(temp);                                                                                    //
    return value;                                                                                  //
}                                                                                                  //
// get verh stack                                                                                  //
int peek(Stack* stack) {                                                                           //
    if (stackempty(stack)) {                                                                       //
        printf("stack is empty\n");                                                                //
		getch();                                                                                   //
        exit(1);                                                                                   //
    }                                                                                              //
    return stack->top->value;                                                                      //
}                                                                                                  //
////////////////////////////////////////////////STACK////////////////////////////////////////////////

struct nodeDerevo {
    char data[50];
    int vozrast;
    struct nodeDerevo *left;
    struct nodeDerevo *right;
};
typedef struct nodeDerevo nodeDerevo;

nodeDerevo* newNode(char data[]) {
    nodeDerevo* node = (nodeDerevo*)malloc(sizeof(nodeDerevo));
    strcpy(node->data, data);
    node->vozrast = 0;
    node->left = node->right = NULL;
    return node;
}

nodeDerevo* insert(nodeDerevo* fnachaloDereva, char fdata[], int fvozrast) {
    if (fnachaloDereva == NULL) {
        nodeDerevo* new_node = newNode(fdata);
        new_node->vozrast = fvozrast; // Устанавливаем возраст
        return new_node;
    }

    int x = strcmp(fdata, fnachaloDereva->data);
    if (x < 0) {
        // Если данные меньше, вставляем в левое поддерево
        fnachaloDereva->left = insert(fnachaloDereva->left, fdata, fvozrast);
    } else if (x == 0) {
        // Если данные равны, добавляем дубликат в правое поддерево с увеличением возраста
        fnachaloDereva->right = insert(fnachaloDereva->right, fdata, fvozrast + 1);
    } else {
        // Если данные больше, вставляем в правое поддерево
        fnachaloDereva->right = insert(fnachaloDereva->right, fdata, fvozrast);
    }
    return fnachaloDereva;
}

void printDerevo(nodeDerevo* nachaloDereva, int otstup) {
    if (nachaloDereva == NULL) {
        return;
    }

    printDerevo(nachaloDereva->right, otstup + 1);

    for (int i = 0; i < otstup; i++) {
        printf("\t");
    }
    printf("%s_%d \n", nachaloDereva->data, nachaloDereva->vozrast);

    printDerevo(nachaloDereva->left, otstup + 1);
}


int findPathToNode(nodeDerevo* root, char target[], Stack* stack) {
    if (root == NULL) {
        return 0; // Узел не найден
    }

    // Добавляем текущий узел в стек
    char buffer[60];
    sprintf(buffer, "%s_%d", root->data, root->vozrast);
    push(stack, strdup(buffer)); // Копируем строку в стек

    // Если текущий узел — искомый
    if (strcmp(root->data, target) == 0) {
        return 1; // Путь найден
    }

    // Рекурсивный поиск в левом и правом поддеревьях
    if (findPathToNode(root->left, target, stack) || findPathToNode(root->right, target, stack)) {
        return 1; // Путь найден в одном из поддеревьев
    }

    // Если путь не найден, удаляем текущий узел из стека
    free(pop(stack));
    return 0; // Путь не найден
}




int main() {
    nodeDerevo* nachaloDereva = NULL;

    // Вставляем узлы в дерево
    nachaloDereva = insert(nachaloDereva, "bca", 0);
    insert(nachaloDereva, "abc", 0);
    insert(nachaloDereva, "cbb", 0);
    insert(nachaloDereva, "cba", 0);
    insert(nachaloDereva, "acb", 0);
    insert(nachaloDereva, "bca", 0);
    insert(nachaloDereva, "cbc", 0);
    insert(nachaloDereva, "bcb", 0);
    insert(nachaloDereva, "bc1", 0);
    insert(nachaloDereva, "bca1", 0);
    insert(nachaloDereva, "bca3", 0);
    insert(nachaloDereva, "bca4", 0);
    printf("Derevo:\n");
    printDerevo(nachaloDereva, 0);

    // Массив для хранения пути
    char pathArray[30][60];
    char target[] = "bca1";

    // Создаем стек
    Stack* stack = createStack();

    // Ищем путь
    if (findPathToNode(nachaloDereva, target, stack)) {
        // Перемещаем путь из стека в массив
        int index = 0;
        while (!stackempty(stack)) {
            strcpy(pathArray[index], pop(stack));
            index++;
        }

        // Выводим путь
        printf("Path to %s:\n", target);
        for (int i = 0; i < index; i++) {
            printf("%s\n", pathArray[i]);
        }
    } else {
        printf("Node %s not found in the tree.\n", target);
    }



    getch();
    return 0;
}
