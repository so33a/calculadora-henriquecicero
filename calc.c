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
} * Pilha;

Pilha novaPilha (void);
void destroiPilha (Pilha p);
void push (Pilha p, int valor);
int pop (Pilha p);
int infixoParaPosfixo (char* entrada, char* saida, int n);
int bemEncaixado (char* s);
int calcula (char* s );
int topo (Pilha p);

int main (void) {
	char infixo[255] ;
	char posfixo[255];
	printf("Sou uma calculadora de inteiros implementado com pilha!\n");
	printf("Digite quit para sair !\n");
	printf ("> ");
	while(fgets(infixo, 255, stdin) != NULL) {
			if(strcmp(infixo, "quit\n") == 0)  {
					printf ("morri !\n");
					return 0;
			}
			if(bemEncaixado(infixo)) {
					infixoParaPosfixo(infixo, posfixo, 255);
					printf("%d\n", calcula(posfixo));
			} else
					printf ("Erro nos parenteses\n");
			printf ("> ");
	}
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

int topo (Pilha p) {
    return p->topo->item;
}

int infixoParaPosfixo (char * entrada, char * saida, int n)
{
    Pilha p = novaPilha();
    int i,k ;
    int j = 0;
    char c;
    push(p, '(');
    for (i = 0; entrada[i] != '\0' &&  i < n; i++)
        {
            if((j-1 > 0) && (saida[j-1] != ' '))
                saida[j++]  = ' ';
            if(entrada[i] == '(') {
                push(p, entrada[i]);
            } else if(entrada[i] == ')'){
                while (1) {
                    c = pop(p);
                    if(c == '(') break;
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
            } else if((entrada[i] == '+') || (entrada[i] == '-')){
                while (1) {
                    c = topo(p);
                    if(c == '(') break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if((entrada[i] == '*') || (entrada[i] == '/')) {
                while (1) {
                    c = topo(p);
                    if(c == '(' || c == '+' || c == '-'  ) break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if (entrada[i] >= '0' && entrada[i] <= '9') {
                while (entrada[i] >= '0' && entrada[i] <= '9') {
                    saida[j++] = entrada[i];
                    i++;
                }
                saida[j++] = ' ';
                i--;
            }

        }
    while (1) {
        c = pop(p);
        if(c == '(') break;
        saida[j++] = c;
        saida[j++] = ' ';
    }
    saida[j] = '\0';
    destroiPilha(p);
    return 0;
}

int bemEncaixado (char* s) {
	Pilha p = novaPilha ();
	link t = p->topo;
	int i;
	int resultado = 1;

	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == '(') {
			push (p, 1);
		} else if (s[i] == ')') {
			pop (p);
		}
	}
	if (t->item > 0)
		resultado = 0;
	destroiPilha(p);
	return resultado;
}

int calcula (char* s) {
    int i = 0;
    int d = 0,k;
    int numero = 0;
    Pilha p = novaPilha();
    int resultado ;
    int a,b;
    while  (s[i] != '\0') {
        if(s[i] >= '0' && s[i] <= '9' ) {
            sscanf(&s[i], "%d", & numero);
            while(s[i] >= '0' && s[i] <= '9')
                i++;
            i--;
            push(p, numero);
        } else if (s[i] == '+') {
            b = pop(p);
            a = pop(p);
            push (p, a + b);
        } else if (s[i] == '-') {
            b = pop(p);
            a = pop(p);
            push (p, a - b);
        } else if (s[i] == '*') {
            b = pop(p);
            a = pop(p);
            push (p, a * b);
        } else if (s[i] == '/') {
            b = pop(p);
            a = pop(p);
            push (p, a/b);
        }
        i++;
    }
    resultado = topo(p);
    destroiPilha(p);
    return resultado;
}
