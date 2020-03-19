#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node {
    int val;
    int height;
    struct Node** next;
} Node;

typedef struct SkipList {
    int max_height;
    Node* start;
    //Node* end;
} SkipList;

int getHeight(int max_h) {
    int h = 1;
    float p = 0.8;
    while (h < max_h && rand() / (RAND_MAX + 1.) < p) h++;
    return h;
}

Node* newNode(int val, int max_height) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->val = val;
	n->height = getHeight(max_height);
	n->next = (Node**)calloc(n->height, sizeof(Node)*max_height);
	return n;
}

void deleteNode(Node* n) {
	free(n);
}

SkipList* newSkipList(int max_height) {
	SkipList* list = malloc(sizeof(SkipList));
	list->max_height = max_height;
	list->start = newNode(0, max_height);

	for (int i = 0; i<max_height; i++) {
		list->start->next[i] = NULL;
	}

	return list;
}

void deleteSkipList(SkipList* list) {
	Node *p = list->start;
	Node *curr = p->next[0];
	while (p != NULL) {
		free(p);
		p = curr;
		if (p != NULL) curr = curr->next[0];
	}
	free(list);
}

void insert(SkipList* list, Node* node) {
	Node* tmp = list->start;
	int i = list->max_height - 1;
	while (i >= 0) {
		while (tmp->next[i] != NULL && tmp->next[i]->val < node->val) {
			tmp = tmp->next[i];
		}

		node->next[i] = tmp->next[i];
		tmp->next[i] = node;
		i--;
	}
}

int main(int argc, char** argv) {
    /*
     * test data:
     * Z - number of test cases
     * h, I - max height of single node (h), number of values to insert (I)
     * I values to insert
     * Output:
     * I lines, subsequent values stored in list
    */
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    for (int i=0; i<Z; i++) {
        int h, I;
        scanf("%d", &h);
        scanf("%d", &I);

        SkipList* list = newSkipList(h);
        int x;
        // insert
        for(int j=0; j<I; j++) {
            scanf("%d", &x);
            insert(list, newNode(x, h));
        }
        // print all values
        Node* iter = list->start, tmp;
        while(iter->next[i] != NULL) {
            printf("%d\n", iter->next[0]->val);
            iter = iter->next[0];
        }
        
		//cleanup
		deleteSkipList(list);
    }
}