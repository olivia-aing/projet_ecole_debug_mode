#include <assert.h>
#include "../plugins/fileprio.h"
#include "../plugins/astar.h"
#include "../plugins/carte.h"

void test_position(void){
    position *pos=create_position(5,4);
    assert(pos->x==5);
    assert(pos->y==4);
    free(pos);
}

void test_noeud(void){
    position *pos=create_position(5,4);
    noeud *n=create_noeud(pos,0,5,NULL);
    assert(n->position->x==5);
    assert(n->position->y==4);
    assert(n->f==5);
    assert(n->g==0);
    noeud *n2=create_noeud(pos,10,11,n);
    assert(n2->parent->position->x==5);
    assert(n2->position!=n->position);
    free(pos);
    free_noeud(n);
    free_noeud(n2);
}

void test_file(void){
    position *pos=create_position(5,4);
    noeud *n=create_noeud(pos,0,5,NULL);
    position *pos2=create_position(7,8);
    noeud *n2=create_noeud(pos2,0,0,NULL);
    fileprio *f=create_file(n,create_file(n2,NULL));

    assert(f->v->position->x==5);
    assert(f->next->v->position->x==7);

    free(pos);
    free(pos2);
    free_file(f);
}

void test_add(void){
    // test de add plusieurs valeurs
    position *pos=create_position(10,14);
    noeud *n=create_noeud(pos,1,10,NULL);
    fileprio *f=create_file(n,NULL);
    position *pos2=create_position(30,34);
    noeud *n2=create_noeud(pos2,0,30,NULL);
    add(n2,&f);
    position *pos3=create_position(20,24);
    noeud *n3=create_noeud(pos3,3,20,NULL);
    add(n3,&f);
    position *pos4=create_position(40,44);
    noeud *n4=create_noeud(pos4,3,40,NULL);
    add(n4,&f);
    position *pos5=create_position(0,4);
    noeud *n5=create_noeud(pos5,3,5,NULL);
    add(n5,&f);

    position *pos6=create_position(30,34);
    noeud *n6=create_noeud(pos6,1,30,NULL);
    fileprio *f2=create_file(n6,NULL);
    position *pos7=create_position(10,14);
    noeud *n7=create_noeud(pos7,0,10,NULL);
    add(n7,&f2);

    noeud *current=f->v;
    noeud *next=f->next->v;
    fileprio *temp=f;
    while(temp->next!=NULL){
        assert(current->f <= next->f);
        temp=temp->next;
    }

    int len=0;
    fileprio *curr=f;
    while(curr!=NULL){
        len++;
        curr=curr->next;
    }

    assert(len==5);

    assert(f2->v->f==n7->f);


    // test de add sur liste vide
    fileprio *f3=NULL;

    position *pos8=create_position(0,0);
    noeud *n8=create_noeud(pos8,0,0,NULL);
    add(n8,&f3);

    assert(f3->v->f==n8->f);
    assert(f3->v!=n8);

    free(pos);
    free(pos2);
    free(pos3);
    free(pos4);
    free(pos5);
    free(pos6);
    free(pos7);
    free(pos8);
    free_noeud(n2);
    free_noeud(n3);
    free_noeud(n4);
    free_noeud(n5);
    free_noeud(n7);
    free_noeud(n8);
    free_file(f);
    free_file(f2);
    free_file(f3);

}

void test_equal(void){
    position *pos=create_position(10,12);
    position *pos2=create_position(10,12);
    position *pos3=create_position(9,12);
    position *pos4=create_position(10,13);
    position *pos5=create_position(9,13);

    assert(equal(pos,pos2)==1);
    assert(equal(pos,pos3)==0);
    assert(equal(pos,pos4)==0);
    assert(equal(pos,pos5)==0);

    free(pos);
    free(pos2);
    free(pos3);
    free(pos4);
    free(pos5);

}

void test_autorise(int **cc){
    position *pos=create_position(-1,5);
    position *pos2=create_position(5,-1);
    position *pos3=create_position(NOMBRE_TILE_LARGEUR,5);
    position *pos4=create_position(1,NOMBRE_TILE_HAUTEUR);
    position *pos5=create_position(0,0);
    position *pos6=create_position(NOMBRE_TILE_LARGEUR-1,NOMBRE_TILE_HAUTEUR-1);
    position *pos7=create_position(1,NOMBRE_TILE_HAUTEUR+1);
    position *pos8=create_position(3,1);
    position *pos9=create_position(2,1);

    assert(autorise(pos,cc)==0);
    assert(autorise(pos2,cc)==0);
    assert(autorise(pos3,cc)==0);
    assert(autorise(pos4,cc)==0);
    assert(autorise(pos5,cc)==1);
    assert(autorise(pos6,cc)==1);
    assert(autorise(pos7,cc)==0);
    assert(autorise(pos8,cc)==0);
    assert(autorise(pos9,cc)==1);
    
    free(pos);
    free(pos2);
    free(pos3);
    free(pos4);
    free(pos5);
    free(pos6);
    free(pos7);
    free(pos8);
    free(pos9);

}

void test_fct_h(void){
    position *pos=create_position(0,0);
    position *pos2=create_position(14,14);
    position *pos3=create_position(2,1);
    noeud *n=create_noeud(pos,0,0,NULL);
    noeud *n2=create_noeud(pos2,0,0,NULL);
    noeud *n3=create_noeud(pos3,0,0,NULL);
    position *dst=create_position(14,14);

    assert(fct_h(n,dst)==28);
    assert(fct_h(n2,dst)==0);
    assert(fct_h(n3,dst)==25);

    free(dst);
    free(pos);
    free(pos2);
    free(pos3);
    free_noeud(n);
    free_noeud(n2);
    free_noeud(n3);
}

void test_best(void){
    position *pos=create_position(3,4);
    noeud *n=create_noeud(pos,0,15,NULL);
    fileprio *f=create_file(n,NULL);
    position *pos2=create_position(3,4);
    position *pos3=create_position(3,4);
    position *pos4=create_position(15,16);
    noeud *n2=create_noeud(pos2,0,10,NULL);
    noeud *n3=create_noeud(pos3,0,20,NULL);
    noeud *n4=create_noeud(pos4,0,30,NULL);

    assert(best(n2,f)==1);
    assert(best(n3,f)==0);
    assert(best(n4,f)==1);
    assert(best(n2,NULL)==1);

    free(pos);
    free_file(f);
    free(pos2);
    free(pos3);
    free(pos4);
    free_noeud(n2);
    free_noeud(n3);
    free_noeud(n4);

}

void test_supprime(void){

    position *pos=create_position(5,4);
    noeud *n=create_noeud(pos,1,10,NULL);
    position *pos2=create_position(9,11);
    noeud *n2=create_noeud(pos2,2,20,NULL);
    position *pos3=create_position(1,1);
    noeud *n3=create_noeud(pos3,1,1,NULL);
    noeud *n4=create_noeud(pos3,1,1,n3);
    position *pos5=create_position(10,12);
    noeud *n5=create_noeud(pos5,0,0,n4);
    fileprio *f=create_file(n,NULL);
    add(n2,&f);
    add(n5,&f);
    position *pos6=create_position(9,11);
    noeud *n6=create_noeud(pos6,5,30,NULL);
    supprime(n6,&f);
    supprime(n6,&f);
    noeud*n7=create_noeud(pos6,5,30,NULL);
    add(n7,&f);
    position *pos8=create_position(5,4);
    noeud *n8=create_noeud(pos8,1,10,NULL);
    supprime(n8,&f);
    position *pos9=create_position(10,12);
    noeud *n9=create_noeud(pos9,1,1,NULL);
    supprime(n9,&f);
    supprime(n9,&f);
    position *pos10=create_position(9,11);
    noeud *n10=create_noeud(pos10,1,1,NULL);
    supprime(n10,&f);
    
    int len=0;
    fileprio *current=f;
    while(current!=NULL){
        len++;
        current=current->next;
    }
    assert(len==0);
    
    //test de supprime sur liste nulle
    fileprio *f2=NULL;
    position *pos11=create_position(10,12);
    noeud *n11=create_noeud(pos11,0,0,NULL);
    supprime(n11,&f2);
    
    assert(f2==NULL);

    free(pos);
    free(pos2);
    free(pos5);
    free(pos6);
    free(pos8);
    free(pos9);
    free(pos11);
    free(pos10);
    free(pos3);
    free_file(f);
    free_file(f2);
    free_noeud(n11);
    free_noeud(n6);
    free_noeud(n8);
    free_noeud(n9);
    free_noeud(n10);
    free_noeud(n2);
    free_noeud(n5);
    free_noeud(n3);
    free_noeud(n4);
    free_noeud(n7);
}

void test_chemin(void){
    position *pos=create_position(5,4);
    position *pos2=create_position(9,11);
    chemin *c=create_chemin(pos,create_chemin(pos2,NULL));

    assert(c->next->v->x==9);
    assert(c->v!=pos);

    free(pos);
    free(pos2);
    free_chemin(c);
}

void test_astar(int **cc,int **cc2){
    position *src=create_position(0,0);
    position *dst=create_position(NOMBRE_TILE_LARGEUR-1,NOMBRE_TILE_HAUTEUR-1);
    position *dst2=create_position(6,6);
    
    // chemin possible
    chemin *c1=astar(src,dst,cc);

    assert(c1->v->x==src->x);
    assert(c1->v->y==src->y);

    chemin *current=c1;
    position *fin;
    while(current!=NULL){
        assert(autorise(current->v,cc)==1);
        fin=current->v;
        current=current->next;
    }    

    assert(fin->x==dst->x);
    assert(fin->y==dst->y);

    // pas de chemin possible
    chemin *c2=astar(src,dst2,cc2);

    assert(c2==NULL);


    free(src);
    free(dst);
    free(dst2);
    free_chemin(c1);
    free_chemin(c2);
}  

void test_present(void){
    position *pos=create_position(5,4);
    position *pos2=create_position(9,11);
    chemin *c=create_chemin(pos,create_chemin(pos2,NULL));

    assert(present(0,0,c)==0);
    assert(present(5,4,c)==1);

    free(pos);
    free(pos2);
    free_chemin(c);
}

void test_trouver_destination(int **cc,int **cc2){
    position *dst=trouver_destination(cc);

    assert(dst->x==0);
    assert(dst->y==4);

    // pas de destination
    position *dst2=trouver_destination(cc2);

    assert(dst2==NULL);

    free(dst);
    free(dst2);
}

int main(void){

    int c[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    int **cc=trans(c);

    int c2[NOMBRE_TILE_HAUTEUR][NOMBRE_TILE_LARGEUR] = {
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {-2,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    int **cc2=trans(c2);

    test_position();
    test_noeud();
    test_add();
    test_file();
    test_equal();
    test_autorise(cc);
    test_fct_h();
    test_best();
    test_supprime();
    test_chemin();
    test_astar(cc,cc2);
    test_present();
    test_trouver_destination(cc,cc2);

    free_carte(cc);
    free_carte(cc2);

    printf("\n\tTous les tests sont validés ! \n\n");

    return 0;
}
