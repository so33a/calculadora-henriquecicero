#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

typedef struct node* link;
struct node {
	int item;
	link next;	
};

typedef struct pilha {
	link topo;
} *Pilha;

Pilha novaPilha (void);
void destroiPilha (Pilha p);
void push (Pilha p, int valor);
int pop (Pilha p);

int main (void) {

	return EXIT_SUCCESS;
}

Pilha novaPilha (void) {
	Pilha p = malloc (sizeof(*p));

	if (p == NULL) {
		printf ("Ha algo errado!\n");
		exit (-1);
	}
	p->topo = 0;
	return p;
}

void destroiPilha (Pilha p) {
	free (p);
}

void push (Pilha p, int valor) {
	link t = p->topo;

	if (p->topo == 0) {
		t->item = valor;
	} else { 
		t->next->item = valor;
	}
}

int pop (Pilha p) {
	link t = p->topo;
	link y;
	int x;

	if (p->topo == 0) {
		printf ("Lista vazia!\n");
		return EXIT_SUCCESS;
	} else {
		y = t;
		x = t->item;
		t = t->next;

		free (y);
	}
	
	return x;
}
