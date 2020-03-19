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
	Node* end;
} SkipList;

int getHeight(int max_h) {
	int h = 1;
	float p = 0.8;
	while (h < max_h && rand() / (RAND_MAX + 1.) < p) h++;
	return h;
}


Node* newNode(int val, int max_height) {
	Node* n = malloc(sizeof(Node));
	n->val = val;
	n->height = getHeight(max_height);
	n->next = calloc(n->height, sizeof(Node*));
	return n;
}

void deleteNode(Node* n) {
	free(n);
}

SkipList* newSkipList(int max_height) {
	SkipList* list = malloc(sizeof(SkipList));
	list->max_height = max_height;
	list->start = malloc(sizeof(Node*));
	list->end = malloc(sizeof(Node*));
	list->start->height = max_height;
	list->end->height = max_height;
	list->start->next = malloc(max_height * sizeof(Node*));
	list->end->next = malloc(max_height * sizeof(Node*));
	// allocate list->start and list->end
	// initialize height and next for each one

	for (int i = 0; i<max_height; i++) {
		list->start->next[i] = list->end;
		list->end->next[i] = NULL;
	}

	return list;
}

void deleteSkipList(SkipList* list) {
	// call deleteNode() on every node in skiplist
	// call free() on list
	Node* tmp = list->start;
	Node* deleted_Node;
	while (tmp) {
		deleted_Node = tmp;
		tmp = tmp->next[0];
		free(deleted_Node);
	}
	free(list);
}

void insert(SkipList* list, Node* node) {
	Node* tmp = list->start;
	int i = list->max_height - 1;
	while (i >= 0) {
		while (tmp->next[i]->next[i] != NULL && tmp->next[i]->val < node->val) tmp = tmp->next[i];
		if (i < node->height) {
			node->next[i] = tmp->next[i];
			tmp->next[i] = node;
		}
		// while value of tmp->next[i] is less than value of given node, go ahead
		// if i isn't too high - insert (plug) given node on level 'i'
		i--;
	}
}

Node* find(SkipList* list, int val) {
	Node* tmp = list->start;
	int i = list->max_height - 1;
	while (i >= 0) {
		while (tmp->next[i]->next[i] && tmp->next[i]->val < val) tmp = tmp->next[i];
		// while value of tmp->next[i] is less than value of given node, go ahead
		i--;
	}
	if (tmp->next[0]->val == val) return tmp->next[0];
	return NULL;
	// return desired node or NULL if such value doesn't exist in the skiplist
}

void removeFromList(SkipList* list, Node* node) {
	Node* tmp = list->start;
	int i = node->height - 1;
	while (i >= 0) {
		while (tmp->next[i]->next[i] && tmp->next[i]->val < node->val) tmp = tmp->next[i];
		// while value of tmp->next[i] is less than value of given node, go ahead
		tmp->next[i] = tmp->next[i]->next[i];
		// remove (unplug) given node on level 'i'
		i--;
	}
}

int main(int argc, char** argv) {
    /*
     * test data:
     * Z - number of test cases
     * h, I, R, F - max height of single node (h), number of values to insert (I), remove(R) and find (F)
     * I values to insert
     * R values to remove (should exist in the previous set)
     * F values to find
     * Output:
     * F lines, "y" or "n" in each one - depending on whether given value is present in the skiplist or not
    */
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    for (int i=0; i<Z; i++) {
        int h, I, R, F;
        scanf("%d", &h);
        scanf("%d", &I);
        scanf("%d", &R);
        scanf("%d", &F);

        SkipList* list = newSkipList(h);
        int x;
        // insert
        for(int j=0; j<I; j++) {
            scanf("%d", &x);
            insert(list, newNode(x, h));
        }
        // remove
        for(int j=0; j<R; j++) {
            scanf("%d", &x);
            Node* n = find(list, x);
            removeFromList(list, n);
            deleteNode(n);
        }
        // find
        for(int j=0; j<F; j++) {
            scanf("%d", &x);
            printf("%s\n", find(list, x) == NULL ? "n" : "y");
        }

        // cleanup
        deleteSkipList(list);
    }
}