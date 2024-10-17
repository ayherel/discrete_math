#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
typedef struct Node {
	int value;
	struct Node* next;
} Node;

void print_list(Node* head) {
	int flag = 0;
	Node* temp;
	temp = head;
	
	do
	{
	    
		printf("%d (address this: %p, address next: %p) \n", head->value, head, head->next);
		head = head->next;
		if (temp == head) flag = 1;
		
    } while ((head != NULL) && (flag != 1));
	
	printf("\n");
}

void merge_lists(Node **head1, Node **head2, Node **head3) {
	
	*head3 = NULL;

	// 
	if (*head1 == NULL) {
		*head3 = *head2;
		return;
	}
	if (*head2 == NULL) {
		*head3 = *head1;
		return;
	}

	// P!P>P7P4P0P5P< P3P>P;P>P2
	Node *current = NULL;
	Node *tail = NULL;

	// 
	while (*head1 != NULL && *head2 != NULL) {
		// P!P2P=P8P2P0P5P< P7P=P
		if ((*head1)->value < (*head2)->value) {
			// 
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
			// 
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

	// 
	while (*head1 != NULL) {
		Node *temp = *head1;
		*head1 = (*head1)->next;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}

	// P
	while (*head2 != NULL) {
		Node *temp = *head2;
		*head2 = (*head2)->next;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}

	// P!P>P7P4P0P5P<
	tail->next = *head3;
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
	srand(time(NULL)); // P8P
	int a,b;
	printf("length 1: ");
	scanf(" %d", &a);
	printf("length 2: ");
	scanf(" %d", &b);
	Node* head1 = NULL;
	generate_list(&head1, a);
	sort_list(&head1);

	Node* head2 = NULL;
	generate_list(&head2, b);
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
