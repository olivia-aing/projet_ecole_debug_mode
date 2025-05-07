#include "fileprio.h"
#include "stdio.h"
#include "stdlib.h"

position *create_position(int a, int b){
    position *pos=malloc(sizeof(position));
    pos->x=a;
    pos->y=b;
    return pos;
}

void print_position(position *pos){
    printf("(%d,%d)",pos->x,pos->y);
}

noeud *create_noeud(position *pos,int gn,int fn,noeud *parent){
    noeud *n=malloc(sizeof(noeud));
    n->f=fn;
    n->g=gn;
    n->position=create_position(pos->x,pos->y);
    noeud *p=parent;
    if (p==NULL){
        n->parent=NULL;
    } else {
        n->parent=create_noeud(p->position,p->g,p->f,p->parent);
    }
    return n;
}

void print_noeud(noeud *n){
    if (n==NULL){
        printf("()");
    } else {
        printf("(");
    print_position(n->position);
    printf(", g=%d, f=%d)",n->g,n->f);
    }
}

fileprio *create_file(noeud *n,fileprio *file){ //attention ne conserve pas l'ordre : utiliser add
    fileprio *f=malloc(sizeof(fileprio));
    f->next=file;
    f->v=n;
    return f;
}

fileprio *next(fileprio *f){
    if (f==NULL){
        return NULL;
    } else {
        return f->next;
    }
}

noeud *value(fileprio *f){
    if (f==NULL){
        return NULL;
    } else {
        return f->v;
    }
}

void print_file(fileprio *f){
    printf("file : [");
    noeud *v;
    fileprio *ne=f;
    while (ne!=NULL){
        v=value(ne);
        print_noeud(v);
        printf(",  ");
        ne=next(ne);
    }
    printf("]\n");
}

void add(noeud *elt,fileprio** file_adresse){
    fileprio *file=*file_adresse;
    noeud *n=create_noeud(elt->position,elt->g,elt->f,elt->parent);
    if (file==NULL){
        // printf("test1\n");
        *file_adresse=create_file(n,NULL);
    } else if (file->next==NULL){
        if (elt->f<=value(file)->f){
            // printf("test2\n");
            *file_adresse=create_file(n,file);
        } else {
            // printf("test3\n");
            file->next=create_file(n,NULL);
        }
    } else {
        fileprio *ne=file;
        if (elt->f<=value(file)->f){
            // printf("test4\n");
            *file_adresse=create_file(n,file);
        } else {
            while (ne->next!=NULL){
                if (elt->f<=value(ne->next)->f){
                    // printf("test5\n");
                    ne->next=create_file(n,ne->next);
                    return;
                } else {
                    ne=ne->next;
                }
            }
            if (elt->f>=value(ne)->f){
                // printf("test6\n");
                ne->next=create_file(n,NULL);
            }
        }
    }
}

int equal(position *pos1,position *pos2){
    //pb du NULL pas traité
    if (pos1->x==pos2->x && pos1->y==pos2->y){
        return 1;
    } else {
        return 0;
    }
}

void print_map(int **carte){
    printf("[");
    for (int i=0;i<NOMBRE_TILE_HAUTEUR;i++){
        for (int j=0;j<NOMBRE_TILE_LARGEUR;j++){
            printf("%d ",carte[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

int autorise(position *pos,int **carte){
    if (pos->x>=NOMBRE_TILE_LARGEUR || pos->x<0 || pos->y>=NOMBRE_TILE_HAUTEUR || pos->y<0){
        return 0;
    } else {
        if (carte[pos->y][pos->x]==0 || carte[pos->y][pos->x]>1 || carte[pos->y][pos->x]<-1){
            return 1;
        } else {
            return 0;
        }
    }
}

int fct_h(noeud *n,position *dst){ //Manhattan Distance
    return abs(n->position->x - dst->x) + abs(n->position->y - dst->y);
}

int best(noeud *n,fileprio *f){
    fileprio *ne=f;
    noeud *v;
    while (ne!=NULL){
        v=value(ne);
        if (equal(n->position,v->position)){
            if (n->f<v->f){
                return 1;
            } else {
                return 0;
            }
        }
        ne=next(ne);
    }
    return 1;
}

void supprime(noeud *n, fileprio **file_adresse){
    fileprio *f=*file_adresse;
    if (f==NULL){
        // printf("test1\n");
    } else if (f->next==NULL){
        if (equal(n->position,f->v->position)){
            // printf("test2\n");
            free_file(f);
            *file_adresse=NULL;
        }
    } else {
        if (equal(n->position,f->v->position)){
            // printf("test3\n");
            fileprio *c = f;
            *file_adresse=f->next;
            free_noeud(c->v);
            free(c);
        } else {
            // printf("test4\n");
            fileprio *ne=f;
            while (ne->next!=NULL){
            if (equal(n->position,ne->next->v->position)){
                fileprio *c=ne->next;
                ne->next=ne->next->next;
                free_noeud(c->v);
                free(c);
                break;
            } else {
                ne=ne->next;
            }
            }
        }
    }
}

chemin *create_chemin(position *p,chemin *f){
    chemin *c=malloc(sizeof(chemin));
    c->v=create_position(p->x,p->y);
    c->next=f;
    return c;
}

void print_chemin(chemin *c){
    chemin *ne=c;
    position *p;
    printf("chemin : [");
    while (ne!=NULL){
        p=ne->v;
        print_position(p);
        printf(", ");
        ne=ne->next;
    }
    printf("]\n");
}

void free_chemin(chemin *c){
    chemin *ne=c;
    position *p;
    chemin *current;
    while (ne!=NULL){
        p=ne->v;
        free(p);
        current=ne;
        ne=ne->next;
        free(current);
    }
}

void free_file(fileprio *f){
    if (f!=NULL){
        noeud *v;
        fileprio *ne=f;
        fileprio *current;
        while (ne!=NULL){
            v=value(ne);
            free_noeud(v);
            current=ne;
            ne=next(ne);
            free(current);
        }
    }
    
}

void free_noeud(noeud *n){
    free(n->position);
    if(n->parent!=NULL){
        free_noeud(n->parent);
    }
    free(n);
    
}

int present(int i, int j, chemin *c){
    position *pos=create_position(i,j);
    chemin *ne=c;
    position *p;
    while (ne!=NULL){
        p=ne->v;
        if (equal(pos,p)){
            free(pos);
            return 1;
        }
        ne=ne->next;
    }
    free(pos);
    return 0;
}

position *trouver_destination(int **map){
    for (int i=0;i<NOMBRE_TILE_HAUTEUR;i++){
            for (int j=0;j<NOMBRE_TILE_LARGEUR;j++){
                if (map[i][j]>1){
                    position *dst=create_position(j,i);
                    return dst;
                }
            }
        }
    return NULL;
}
