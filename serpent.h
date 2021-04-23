#ifndef SERPENT_H
#define SERPENT_H

#include "utils.h"
#include "grille.h"

const int taille_max=z*z;

class Serpent{
    int Dir;
    point Serp[taille_max];
    int Taille;
public:
    Serpent();
    Serpent(int a,point b[taille_max],int c);
    ~Serpent();
    void setDir();
    int getDir();
    void setDir(int n);
    point getTete();
    point getAvantTete();
    point getQueue();
    void serp(point a[1000]);
    int getTaille();
    void avance(Color col);
    void avance_snake();
    void avance(Color col,NativeBitmap moto,NativeBitmap blanc);
    void init();
    void aug_taille();
};


#endif // SERPENT_H
