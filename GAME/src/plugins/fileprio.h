#ifndef FILEPRIO_H
#define FILEPRIO_H

// #define NOMBRE_TILE_LARGEUR 15
// #define NOMBRE_TILE_HAUTEUR 15
#include "carte.h"

typedef struct _position{
    int x;
    int y;
} position;

typedef struct _noeud{
    int f;
    int g;
    position *position;
    struct _noeud *parent;
} noeud;

typedef struct _fileprio{
    noeud *v;
    struct _fileprio *next;
} fileprio;

typedef struct _chemin{
    position *v;
    struct _chemin *next;
} chemin;

position *create_position(int x, int y);

void print_position(position *pos);

noeud *create_noeud(position *pos,int g,int f,noeud *parent);

void print_noeud(noeud *n);

fileprio *create_file(noeud *n,fileprio *file);

fileprio *next(fileprio *f);

noeud *value(fileprio *f);

void print_file(fileprio *f);

void add(noeud *elt,fileprio** file_adresse); //modif de la liste initiale

int equal(position *pos1,position *pos2);

void print_map(int **carte);

int autorise(position *pos,int **carte);

int fct_h(noeud *n,position *dst);

int best(noeud *n,fileprio *f); //renvoie 0 si il y a déjà un noeud de même position qui a un meilleur f, 1 sinon

void supprime(noeud *n, fileprio **file_adresse); //modif de la liste initiale

void print_chemin(chemin *c);

chemin *create_chemin(position *p,chemin *f);

void free_chemin(chemin *c);

void free_file(fileprio *f);

void free_noeud(noeud *n);

int present(int i, int j, chemin *c); //vérifie si la position (i,j) est dans le chemin

position *trouver_destination(int **map);

#endif
