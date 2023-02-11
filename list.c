#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct nodo {
    int value;
    struct nodo* next;
} nodo;

nodo* aggiungi_in_testa(int n, nodo* head){
    if(head != NULL){
        nodo* nodosucc = head;
        head = malloc(sizeof(nodo));
        head->value = n;
        head->next = nodosucc;
    } else {
        head = malloc(sizeof(nodo));
        head->value = n;
        head->next = NULL;
    }  
    return head;
}

void stampa_lista(nodo * testa){
	if(testa != NULL){
		printf("TESTA -> ");
		while(testa != NULL){
			printf("%d -> ",testa->value);
			testa = testa -> next;
		}
	    printf("NULL \n");
	}
	else {
		printf("LISTA VUOTA \n");
	}
}

nodo* concat_in_middle(int pos, nodo* head, nodo* patch){
    if( head == NULL){
        return NULL;
    } else if(patch == NULL){
        return head;
    } else {
        nodo* p = head;
        nodo* k = patch;
        nodo* y = head;
        while(pos != 0){
            pos--;
            p = p->next;
        }
        
        while(k->next != NULL){
            k = k->next;
        }
        k->next = p->next;
        p->next = patch;
        return head;
    }
}

/* elimina l'ultimo nodo */
nodo* elimina_last(nodo* head){
    if(head == NULL){
        return NULL;
    } else {
        nodo* prec = head;
        nodo* curr = head->next;
        while(curr->next != NULL){
            prec = curr;
            curr = curr->next;
        }
        prec->next = NULL;
        free(curr);
        return head;
    }
}

/* elimina il nodo in posizione pos*/
nodo* elimina_in_posizione(int pos, nodo* head){
    if(head == NULL){
        return NULL;
    } else {
        nodo* curr=head;
        nodo* succ = NULL;
        nodo* prec = NULL;
        while(pos > 1){
            prec = curr;
            pos--;
            curr = curr->next;
        }

        succ = curr->next;
        prec->next = succ;
        free(curr);
        
        return head;
    }
}

/* elimina tutti i nodi uguali a val */
nodo* delete_all(nodo* head, int val){
    if(head == NULL){
        return NULL;
    } else {
        nodo* curr = head->next;
        nodo* prec = head;
        nodo* succ = NULL;
        while(prec != NULL){
            if(curr->value == val){
                succ = curr->next;
                prec->next = succ;
            } else {
                prec = curr;
                curr = curr->next;
            }
        }
        return head;
    }
}

/* elimina i nodi pari */
nodo* delete_even(nodo* head){
    if(head == NULL){
        return NULL;
    } else {
        nodo* prec = head;
        nodo* curr = NULL;
        nodo* succ = NULL;
        int i=1;
        while(prec != NULL){
            if(i % 2 == 0){
                curr = prec->next;
                succ = prec->next->next;
                prec->next = succ;
                free(curr);
                i++;
            }
            prec=prec->next;
            i++;
        }
        return head;
    }
}

/* aggiunge un valore to_add dopo ogni nodo max_add */
nodo* add_odd(nodo* head, int to_add, int max_add){
    if(head == NULL){
        return NULL;
    } else {
        nodo* curr = head;
        nodo* prec = NULL;
        int i=1;
        while(curr != NULL){
            if(i % 2 == 1){
                nodo* add = (nodo*) malloc(sizeof(nodo));
                add->value = to_add;
                add->next = curr->next;
                curr->next = add;
                curr = curr->next;
            } 
            curr = curr->next;
            i++;
        }
        return head;
    }
}

/* inserisce il valore to_add dopo l'ultimo nodo con value uguale a to_compare */
nodo* insert_tail_if(nodo* head, int to_add, int to_compare){
    if(head == NULL){
        return NULL;
    } else {
        nodo* curr = head;
        int ok=0;
        while(curr->next != NULL){
            if(curr->value == to_compare){
                ok = 1;
            }
            curr = curr->next;
        }
        if(ok == 1 || curr->value == to_compare){
            nodo* new = (nodo *)malloc(sizeof(nodo));
            new->value = to_add;
            new->next = NULL;
            curr->next = new;
            return head;
        } else {
            return head;
        }
    }
}

/* elimina l'ultimo nodo della lista se contiene l'elemento to_delete*/
nodo* delete_last(nodo* head, int to_delete){
    if(head ==  NULL){
        return head;
    } else {
        nodo* curr = head;
        int cnt=0;
        while(curr != NULL){
            cnt++;
            curr=curr->next;
        }
        curr = head;
        if(cnt < to_delete){
            return head;
        } else {
            int save_node = cnt - to_delete;
            while(curr != NULL && save_node-1 > 0){
                save_node--;
                curr = curr->next;
            }
            curr->next = NULL;
            free(curr->next);
            return head;
        }
    }
}

/* elimina il nodo in posizione centrale della lista */
nodo* delete_central_element(nodo* head){
    if(head == NULL){
        return NULL;
    } else {
        nodo* curr = head;
        int cnt=0;
        while(curr != NULL){
            cnt++;
            curr = curr->next;
        }
        curr = head;
        if(cnt > 3){
            if(cnt % 2 == 0){
                nodo* prec = NULL;
                int x = cnt/2 -1;
                while(x > 0){
                    x--;
                    prec = curr;
                    curr = curr->next;
                }

                prec->next = curr->next->next;
                free(curr);
                free(curr->next);

                return head;

            } else {
                nodo* prec = NULL;
                int x = cnt/2;

                while(x > 0){
                    x--;
                    prec = curr;
                    curr = curr->next;
                }

                prec->next = curr->next;
                free(curr);
                return head;

            }
        } else {
            return head;
        }
    }
}

/* elimina tutti i nodi dispari della lista */
nodo* clean_odd(nodo* head){
    if(head == NULL){
        return  NULL;
    } else {
        while(head->value % 2 != 0){
            if(head->value % 2 != 0){
                nodo* new_head = head->next;
                free(head);
                head = new_head; 
            }
        }
        nodo* curr = head->next;
        nodo* prec = head;
        while(curr != NULL){
            if(curr->value % 2 != 0){
                prec->next = curr->next;
                free(curr);
                curr = prec->next;
            } else {
                prec = curr;
                curr = curr->next;
            }
        }
        return head;
    }
}

/* Data una lista e i valori di posizione di inizio e fine crea la sottolista */
nodo* cut(nodo* head, int begin, int end){
    if(head == NULL){
        return NULL;
    } else {
        int cnt = end - begin;
        while(begin > 0){
            nodo* new_head = head->next;
            free(head);
            head = new_head;
            begin--;
        }
        nodo* curr = head;
        nodo* prec = NULL;
        while(cnt > 0){
            prec = curr;
            curr = curr->next;
            cnt--;
        }
        printf("%d", curr->value);
        curr->next = NULL;
        prec->next = curr->next; 
        free(curr);
        return head;
    }
}

/* inverte la lista */
nodo* invert(nodo* head){
    if(head == NULL){
        return NULL;
    } else {
        nodo* succ = NULL;
        nodo* curr = head;
        nodo* prec = NULL;
        while(curr != NULL){
            succ = curr->next;
            curr->next = prec;
            prec = curr;
            curr = succ;
        }
        return prec;
    }
}


int main() {
    nodo* lista = NULL;

    for(int i=LENGTH; i > 0; i--){
        lista = aggiungi_in_testa(i, lista);
    }

    printf("Lista originale: ");
    stampa_lista(lista);

    printf("Concatenazione al terzo elemento: ");
    nodo* patch = NULL;
    patch = aggiungi_in_testa(11, patch);
    patch = aggiungi_in_testa(12, patch);
    lista = concat_in_middle(3, lista, patch);
    stampa_lista(lista);

    printf("Rimozione dei numeri dispari: ");
    lista = clean_odd(lista);
    stampa_lista(lista);

    printf("Rimozione dell'ultimo nodo: ");
    lista = elimina_last(lista);
    stampa_lista(lista);

    printf("Rimozione del nodo in posizione 4: ");
    lista = elimina_in_posizione(4, lista);
    stampa_lista(lista);

    printf("Aggiunta del valore 100 dopo ogni nodo dispari (massimo 3 volte): ");
    lista = add_odd(lista, 100, 3);
    stampa_lista(lista);

    printf("Inserimento del valore 99 dopo l'ultimo nodo contenente 8: ");
    lista = insert_tail_if(lista, 99, 8);
    stampa_lista(lista);

    printf("Eliminazione dell'ultimo nodo contenente 6: ");
    lista = delete_last(lista, 6);
    stampa_lista(lista);

    return 0;
}
    