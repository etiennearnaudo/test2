#include "grille.h"

void Grille::init(){
    for (int i=0;i<z;i++) for (int j=0;j<z;j++) grille[i][j]=false;
}

bool Grille::get(point a) const{
    return grille[a.x][a.y];
}

void Grille::set(point a,bool booleen){
    grille[a.x][a.y]=booleen;
}
