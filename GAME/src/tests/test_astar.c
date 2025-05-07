#include <stdio.h>
#include <stdlib.h>
#include "../plugins/fileprio.h"
#include "../plugins/astar.h"
#include "../plugins/carte.h"

int main(){
    
    int c[32][32] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    int **cc=trans(c);
    int c2[32][32] = {
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    int **cc2=trans(c2);



    //test de create_position et print_position
    printf("test de create position et print position :\n");
    position *pos=create_position(5,4);
    print_position(pos);
    free(pos);

    printf("\n");

    //test de create_noeud et print_noeud
    printf("test de create noeud et print noeud :\n");
    position *pos0=create_position(5,4);
    noeud *n0=create_noeud(pos0,0,5,NULL);
    print_noeud(n0);
    printf("\n");
    noeud *n00=create_noeud(pos0,0,5,n0);
    free_noeud(n00);
    free_noeud(n0);
    free(pos0);

    printf("\n");

    //test de create_file et print file et next et value
    printf("test de create file et print file :\n");
    position *pos21=create_position(5,4);
    position *pos1=create_position(9,11);
    noeud *n=create_noeud(pos21,1,10,NULL);
    noeud *n1=create_noeud(pos1,2,20,NULL);
    fileprio *f0=create_file(n,create_file(n1,NULL));
    print_file(f0);
    printf("test de value :\nf : ");
    print_noeud(value(f0));
    printf("\nliste vide : ");
    print_noeud(value(NULL));
    printf("\ntest de next :\n");
    print_file(next(f0));
    printf("liste vide : ");
    print_file(next(NULL));
    free_file(f0);
    free(pos21);
    free(pos1);
    
    printf("\n");

    //test de add
    printf("test de add :\n");
    position *pos22=create_position(10,14);
    noeud *n7=create_noeud(pos22,1,10,NULL);
    fileprio *f=create_file(n7,NULL);
    printf("f :\n");
    print_file(f);

    printf("ajout à f de ");
    position *pos3=create_position(30,34);
    noeud *n3=create_noeud(pos3,0,30,NULL);
    print_noeud(n3);
    printf("\n");
    add(n3,&f);
    print_file(f);

    printf("ajout à f de ");
    position *pos2=create_position(20,24);
    noeud *n2=create_noeud(pos2,3,20,NULL);
    print_noeud(n2);
    printf("\n");
    add(n2,&f);
    print_file(f);

    printf("ajout à f de ");
    position *pos50=create_position(40,44);
    noeud *n50=create_noeud(pos50,3,40,NULL);
    print_noeud(n50);
    printf("\n");
    add(n50,&f);
    print_file(f);

    printf("ajout à f de ");
    position *pos60=create_position(0,4);
    noeud *n60=create_noeud(pos60,3,5,NULL);
    print_noeud(n60);
    printf("\n");
    add(n60,&f);
    print_file(f);

    position *pos51=create_position(30,34);
    noeud *n51=create_noeud(pos51,1,30,NULL);
    fileprio *f5=create_file(n51,NULL);
    printf("f5 :\n");
    print_file(f5);

    printf("ajout à f5 de ");
    position *pos52=create_position(10,14);
    noeud *n52=create_noeud(pos52,0,10,NULL);
    print_noeud(n52);
    printf("\n");
    add(n52,&f5);
    print_file(f5);


    printf("test de add sur liste vide :\n");

    fileprio *f2=NULL;
    printf("f2 :\n");
    print_file(f2);

    printf("ajout à f2 de ");
    position *pos4=create_position(0,0);
    noeud *n4=create_noeud(pos4,0,0,NULL);
    print_noeud(n4);
    printf("\n");
    add(n4,&f2);
    print_file(f2);


    free_file(f);
    free_file(f2);
    free_file(f5);
    free(pos3);
    free(pos22);
    free(pos2);
    free(pos4);
    free(pos50);
    free(pos51);
    free(pos52);
    free(pos60);
    free_noeud(n3);
    free_noeud(n2);
    free_noeud(n50);
    free_noeud(n60);
    free_noeud(n52);
    free_noeud(n4);

    printf("\n");

    // test de equal
    printf("test de equal :\n");
    position *pos5=create_position(10,12);
    position *pos6=create_position(10,12);
    position *pos7=create_position(9,12);
    position *pos8=create_position(10,13);
    position *pos9=create_position(9,13);
    printf("(10,12) & (10,12) :  %d\n(10,12) & (9,12) : %d\n(10,12) & (10,13) : %d\n(10,12) & (9,13) : %d\n",equal(pos5,pos6),equal(pos5,pos7),equal(pos5,pos8),equal(pos5,pos9));
    free(pos5);
    free(pos6);
    free(pos7);
    free(pos8);
    free(pos9);

    printf("\n");

    //test de autorise et print_map
    printf("test de print_map :\n");
    printf("carte 1 :\n");
    print_map(cc);
    printf("test de autorise sur carte1(15,15):\n");
    position *pos10=create_position(-1,5);
    position *pos11=create_position(5,-1);
    position *pos12=create_position(16,5);
    position *pos13=create_position(1,16);
    position *pos14=create_position(0,0);
    position *pos15=create_position(14,14);
    position *pos16=create_position(1,15);
    position *pos17=create_position(3,1);
    position *pos18=create_position(2,1);
    printf("(-1,5) : 0=%d\n",autorise(pos10,cc));
    printf("(5,-1) : 0=%d\n",autorise(pos11,cc));
    printf("(16,5) : 0=%d\n",autorise(pos12,cc));
    printf("(1,16) : 0=%d\n",autorise(pos13,cc));
    printf("(0,0) : 1=%d\n",autorise(pos14,cc));
    printf("(14,14) : 1=%d\n",autorise(pos15,cc));
    printf("(1,15) : 0=%d\n",autorise(pos16,cc));
    printf("(3,1) : 0=%d\n",autorise(pos17,cc));
    printf("(2,1) : 1=%d\n",autorise(pos18,cc));
    free(pos10);
    free(pos11);
    free(pos12);
    free(pos13);
    free(pos14);
    free(pos15);
    free(pos16);
    free(pos17);
    free(pos18);

    printf("\n");

    //test de fct_h
    printf("test de fct_h :\n");
    position *pos23=create_position(0,0);
    position *pos24=create_position(14,14);
    position *pos25=create_position(2,1);
    noeud *n23=create_noeud(pos23,0,0,NULL);
    noeud *n24=create_noeud(pos24,0,0,NULL);
    noeud *n25=create_noeud(pos25,0,0,NULL);
    position *dst=create_position(14,14);
    printf("h((0,0))=%d(=28)\nh((14,14))=%d(=0)\nh((2,1))=%d(=25)\n",fct_h(n23,dst),fct_h(n24,dst),fct_h(n25,dst));
    free_noeud(n23);
    free_noeud(n24);
    free_noeud(n25);
    free(pos23);
    free(pos24);
    free(pos25);
    free(dst);

    printf("\n");

    //test de best -> renvoie 0 si il y a déjà un noeud de même position qui a un meilleur f
    printf("test de best :\nfile test :\n");
    position *pos20b=create_position(3,4);
    noeud *n20b=create_noeud(pos20b,0,15,NULL);
    fileprio *f3=create_file(n20b,NULL);
    print_file(f3);
    position *pos20a=create_position(3,4);
    position *pos20c=create_position(3,4);
    position *pos19=create_position(15,16);
    noeud *n20a=create_noeud(pos20a,0,10,NULL);
    noeud *n20c=create_noeud(pos20c,0,20,NULL);
    noeud *n19=create_noeud(pos19,0,30,NULL);
    printf("best avec pos(3,4),f=10 : 1=%d\n",best(n20a,f3));
    printf("best avec pos(3,4), f=20 : 0=%d\n",best(n20c,f3));
    printf("best avec pos(15,16), f=30 : 1=%d\n",best(n19,f3));
    printf("test de best avec liste vide : 1=%d\n",best(n20a,NULL));
    free(pos20b);
    free_file(f3);
    free(pos20a);
    free(pos20c);
    free(pos19);
    free_noeud(n20a);
    free_noeud(n20c);
    free_noeud(n19);

    printf("\n");

    //test de supprime
    printf("test de supprime :\n");

    position *pos26=create_position(5,4);
    noeud *n26=create_noeud(pos26,1,10,NULL);
    position *pos27=create_position(9,11);
    noeud *n27=create_noeud(pos27,2,20,NULL);
    position *pos28p=create_position(1,1);
    noeud *n28p=create_noeud(pos28p,1,1,NULL);
    noeud *n28pp=create_noeud(pos28p,1,1,n28p);
    position *pos28=create_position(10,12);
    noeud *n28=create_noeud(pos28,0,0,n28pp);
    fileprio *f4=create_file(n26,NULL);
    add(n27,&f4);
    add(n28,&f4);
    print_file(f4);
    
    printf("supprime (9,11) :\n");
    position *pos27b=create_position(9,11);
    noeud *n27b=create_noeud(pos27b,5,30,NULL);
    supprime(n27b,&f4);
    print_file(f4);

    printf("supprime (9,11) :\n");
    supprime(n27b,&f4);
    print_file(f4);

    printf("rajout de (9,11) :\n");
    noeud*n27bb=create_noeud(pos27b,5,30,NULL);
    add(n27bb,&f4);
    print_file(f4);
    
    printf("supprime (5,4) :\n");
    position *pos26b=create_position(5,4);
    noeud *nb=create_noeud(pos26b,1,10,NULL);
    supprime(nb,&f4);
    print_file(f4);
    
    printf("supprime (10,12) :\n");
    position *pos29=create_position(10,12);
    noeud *n29=create_noeud(pos29,1,1,NULL);
    supprime(n29,&f4);
    print_file(f4);

    printf("supprime (10,12) :\n");
    supprime(n29,&f4);
    print_file(f4);

    printf("supprime (9,11) :\n");
    position *pos30=create_position(9,11);
    noeud *n30=create_noeud(pos30,1,1,NULL);
    supprime(n30,&f4);
    print_file(f4);

    printf("test de supprime sur liste nulle :\n");
    
    fileprio *f6=NULL;
    position *pos28b=create_position(10,12);
    noeud *n28b=create_noeud(pos28b,0,0,NULL);
    supprime(n28b,&f6);
    print_file(f6);

    free(pos26);
    free(pos27);
    free(pos28);
    free(pos27b);
    free(pos26b);
    free(pos29);
    free(pos28b);
    free(pos30);
    free(pos28p);
    free_file(f4);
    free_file(f6);
    free_noeud(n28b);
    free_noeud(n27b);
    free_noeud(nb);
    free_noeud(n29);
    free_noeud(n30);
    free_noeud(n27);
    free_noeud(n28);
    free_noeud(n28p);
    free_noeud(n28pp);
    free_noeud(n27bb);

    printf("\n");

    //test de chemin
    printf("test de create chemin et print chemin :\n");
    position *pos32=create_position(5,4);
    position *pos31=create_position(9,11);
    chemin *c0=create_chemin(pos31,create_chemin(pos32,NULL));
    print_chemin(c0);
    free_chemin(c0);
    free(pos32);
    free(pos31);

    printf("\n");

    // test de A*
    printf("test de A* :\n");
    position *src=create_position(0,0);
    position *dst2=create_position(14,14);
    position *dst3=create_position(6,6);
    

    chemin *c1=astar(src,dst2,cc);
    print_chemin(c1);
    free_chemin(c1);

    chemin *c2b=astar(src,dst3,cc2);
    print_chemin(c2b);
    free_chemin(c2b);


    free(src);
    free(dst2);
    free(dst3);
    
    printf("\n");

    // test de present :
    printf("test de present :\n");
    position *pos33=create_position(5,4);
    position *pos34=create_position(9,11);
    chemin *cb=create_chemin(pos33,create_chemin(pos34,NULL));
    print_chemin(cb);
    printf("(0,0) present : 0=%d,\n(5,4) present : 1=%d,\n",present(0,0,cb),present(5,4,cb));
    free_chemin(cb);
    free(pos33);
    free(pos34);

    printf("\n");

    //test de trouver_destination
    printf("test de trouver_dest\n");
    position *dstdst=trouver_destination(cc);
    print_position(dstdst);
    free(dstdst);

    printf("\n");

    free_carte(cc);
    free_carte(cc2);

    return 0;
}

