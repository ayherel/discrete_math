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

// разобрать функцию
void printDerevo(nodeDerevo* nachaloDereva, int otstup) {
    if (nachaloDereva == NULL) {
        return;
    }

    printDerevo(nachaloDereva->right, otstup + 1);

    for (int i = 0; i < otstup; i++) {
        printf("\t");
    }
    printf("%s-%d \n", nachaloDereva->data, nachaloDereva->vozrast);

    printDerevo(nachaloDereva->left, otstup + 1);
}


nodeDerevo* insert(nodeDerevo* fnachaloDereva, char fdata[], int fvozrast) {
    if (fnachaloDereva == NULL) {
        nodeDerevo* new_node = newNode(fdata);
        new_node->vozrast = fvozrast;
        return new_node;
    }

    int x = strcmp(fdata, fnachaloDereva->data);
    if (x < 0) {
        fnachaloDereva->left = insert(fnachaloDereva->left, fdata, fvozrast);
    }
    else{
        if (x == 0) {
            fnachaloDereva->right = insert(fnachaloDereva->right, fdata, fvozrast + 1);
        }

        else fnachaloDereva->right = insert(fnachaloDereva->right, fdata, fvozrast);
    }
    return fnachaloDereva;
}

int findPathToNode(nodeDerevo* ffnachaloDereva, char fdata[], Stack* stack, int fvozrast) {
    if (ffnachaloDereva == NULL) return 0;

    char buffer[60];
    sprintf(buffer, "%s_%d", ffnachaloDereva->data, ffnachaloDereva->vozrast);
    push(stack, strdup(buffer));

    if ((strcmp(ffnachaloDereva->data, fdata) == 0) && (ffnachaloDereva->vozrast == fvozrast)) return 1;

    if (findPathToNode(ffnachaloDereva->left, fdata, stack, fvozrast) || findPathToNode(ffnachaloDereva->right, fdata, stack, fvozrast)) return 1;

    /*
    int ress = pop(stack);
    printf("- %d - \n", ress);
    free(ress);
    printf("- %d - \n", ress);
    free(pop(stack)); // зачем?
    */
    pop(stack);
    printf("Node not found; \n");
    return 0;
}

int main() {
    system("cls"); // cls - что?
    nodeDerevo* nachaloDereva = NULL;

    char key;
    int flag = 0;

    while (flag != 1){
        int xx;
        system("cls");
        printf("Derevo:\n");
        printDerevo(nachaloDereva, 0);
        char simbol, slovo[50];
        memset(slovo, '\0', 50);
        printf("Input node for tree: \n");
        int ii=0;
        do {
            simbol = getchar();
            if (simbol != '\n'){
                slovo[ii] = simbol;
                ii++;
            }
        } while (simbol != '\n');
        nachaloDereva = insert(nachaloDereva, slovo, 0);
        system("cls");
        printf("Derevo:\n");
        printDerevo(nachaloDereva, 0);

        printf("If you want add node input y, else other simbol: \n");
        key = getch();
        if (key == 'y'){
            flag = 0;
        }
        else{
            flag = 1;
        }
        memset(slovo, '\0', 50);
    };

    char simbol, simbol2;
    int ii1, ii2;

    getch();
    char data1[50];
    memset(data1, '\0', 50);
    int vozrastData1 = 0;
    printf("First node for FPTN: \n");
    printf("Input repeat first node: \n");
    scanf (" %d", &vozrastData1);
    printf("Input data first node: \n");
    ii1=0;
    while ((getchar()) != '\n');
    do {
        simbol = getchar();
        if (simbol != '\n'){
            data1[ii1] = simbol;
            ii1++;
        }
    } while (simbol != '\n');

    char data2[50];
    memset(data2, '\0', 50);
    int vozrastData2 = 0;
    printf("Second node for FPTN: \n");
    printf("Input repeat second node: \n");
    scanf (" %d", &vozrastData2);
    printf("Input data second node: \n");
    ii2=0;
    //fflush(stdin);
    while ((getchar()) != '\n');
    do {
        simbol2 = getchar();
        if (simbol2 != '\n'){
            data2[ii2] = simbol2;
            ii2++;
        }
    } while (simbol2 != '\n');

    system("cls");
    printf("Derevo:\n");
    printDerevo(nachaloDereva, 0);
    printf("First node povtor: %s_%d\n", data1, vozrastData1);
    printf("Secind node povtor: %s_%d\n", data2, vozrastData2);

    // arrays for find path
    char pathArray1[30][50];
    char pathArray2[30][50];

    Stack* stack1 = createStack();
    Stack* stack2 = createStack();
    int index = 0;
    int index2 = 0;
    // find path 1
    if (findPathToNode(nachaloDereva, data1, stack1, vozrastData1)) {
        while (!stackempty(stack1)) {
            strcpy(pathArray1[index], pop(stack1));
            printf("uzli 1 %s \n", pathArray1[index]);
            index++;
        }
    }
    else printf("Node %s not found\n", data1);

    printf("\n");

    // find path 2
    if (findPathToNode(nachaloDereva, data2, stack2, vozrastData2)) {
        while (!stackempty(stack2)) {
            strcpy(pathArray2[index2], pop(stack2));
            printf("uzli 2 %s \n", pathArray2[index2]);
            index2++;
        }
    }
    else printf("Node %s not found\n", data2);

    int flagg;
    for (int i=1; i < index; i++){
        for (int j=1; j <index2; j++){
            flagg = strcmp(pathArray1[i], pathArray2[j]);
            if (flagg == 0){
                printf("Found the youngest ancestor: %s\n", pathArray1[i]);
                getch();
                return 0;
            }
        }
    };

    getch();
    return 0;
}

