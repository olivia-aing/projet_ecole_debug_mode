// #include "fileprio.h"
#include "astar.h"
#include <stdio.h>
#include <stdlib.h>

chemin *astar(position *src, position *dst, int **carte){
    fileprio *open=NULL;
    fileprio *closed=NULL;
    int max=abs(src->x - dst->x) + abs(src->y - dst->y);
    noeud *n = create_noeud(src,0,max,NULL);
    add(n,&open);
    // free_noeud(n);
    position *pos=create_position(0,0);
    noeud *n2=create_noeud(pos,0,0,NULL);
    int h;
    // printf("open et closed initiales :\n");
    // print_file(open);
    // print_file(closed);
    // printf("\n");
    while (open != NULL){
        // printf("\n");
        // printf("etape 1 :\n");
        // printf("le noeud choisi est : ");
        free_noeud(n);
        n=value(open);
        // print_noeud(n);
        // printf("\nopen :\n");
        fileprio *c=open;
        open=next(open);
        free(c);
        // print_file(open);
        if (equal(n->position,dst)){
            // printf("\netape finale\n");
            add(n,&closed);
            //reconstitution du chemin
            chemin *c=NULL;
            noeud *n_for_free=n;
            while(!(equal(n->position,src))){
            c=create_chemin(n->position,c);
            // noeud *nc=n;
            n=n->parent;
            // free_noeud(nc);
            }
            c=create_chemin(n->position,c);
            // free_noeud(n);
            free_noeud(n_for_free);
            // print_file(open);
            // print_file(closed);
            free_file(open);
            free_file(closed);
            free(pos);
            free_noeud(n2);

            return c;
        } else {
            // printf("\n");
            // printf("etape 2 :\nclosed :\n");
            add(n,&closed);
            // print_file(closed);
            for (int i=-1;i<2;i=i+2){ // voisins de n sur la même ligne
                
                // printf("\netape 2a :\n");
                (n2->position)->x=((n->position)->x+i);
                (n2->position)->y=((n->position)->y);
                // print_noeud(n2);
                // printf("\n");
                if (autorise(n2->position,carte)){
                    // printf("autorise\n");
                    h=fct_h(n2,dst);
                    n2->g = (n->g)+1;
                    n2->f = h+(n2->g);
                    if (best(n2,open) && best(n2,closed)){
                        // printf("c le meilleur\n");
                        // noeud *n2_for_free=n2;
                        // n2=create_noeud(n2->position,n2->g,n2->f,n);
                        // free_noeud(n2_for_free);
                        // supprime(n2,&open);
                        // supprime(n2,&closed);
                        // add(n2,&open);
                        noeud *n2_copy=create_noeud(n2->position,n2->g,n2->f,n);
                        supprime(n2_copy,&open);
                        supprime(n2_copy,&closed);
                        add(n2_copy,&open);
                        free_noeud(n2_copy);
                        // print_file(open);
                        // print_file(closed);
                    }
                }
                // free_noeud(n2);
                // n2=create_noeud(pos,0,0,NULL);
            }
            // printf("\nfin etape 2a");
            // print_file(open);
            // print_file(closed);
            for (int i=-1;i<2;i=i+2){ //voisin de n sur la même colonne
                // printf("\netape 2b : ");
                (n2->position)->x=((n->position)->x);
                (n2->position)->y=((n->position)->y+i);
                // printf("\n");
                // print_noeud(n2);
                // printf("\n");
                if (autorise(n2->position,carte)){
                    // printf("autorise\n");
                    h=fct_h(n2,dst);
                    n2->g = (n->g)+1;
                    n2->f = h+(n2->g);
                    if (best(n2,open) && best(n2,closed)){
                        // printf("c le meilleur\n");
                        // noeud *n2_for_free=n2;
                        // n2=create_noeud(n2->position,n2->g,n2->f,n);
                        // free_noeud(n2_for_free);
                        // supprime(n2,&open);
                        // supprime(n2,&closed);
                        // add(n2,&open);
                        noeud *n2_copy=create_noeud(n2->position,n2->g,n2->f,n);
                        supprime(n2_copy,&open);
                        supprime(n2_copy,&closed);
                        add(n2_copy,&open);
                        free_noeud(n2_copy);
                        // print_file(open);
                        // print_file(closed);
                    }   
                }
                // free_noeud(n2);
                // n2=create_noeud(pos,0,0,NULL);
            }
            // printf("\nfin etape 2b");
            // print_file(open);
            // print_file(closed);
        }
    }
    free_file(open);
    free_file(closed);
    free(pos);
    free_noeud(n2);
    free_noeud(n);
    return NULL;
    // si open vide et pas trouvé dest -> pas de sol
    
    //free(open,close,n...)
}
