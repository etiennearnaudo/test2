#include "serpent.h"
#include "utils.h"

Serpent::Serpent(){}

Serpent::Serpent(int a,point b[taille_max],int c){
    Dir=a;
    for (int i=0;i<taille_max;i++) Serp[i]=b[i];
    Taille=c;
}

Serpent::~Serpent(){}

void Serpent::setDir(){
    int e;
    while(true){
        e=Clavier() - 16777234;
        if (e==Dir) break;
        if (e==2) {
            Dir=0;
            break;
        }
        if (e==3) {
            Dir=1;
            break;
        }
        if (e==0) {
            Dir=2;
            break;
        }
        if (e==1) {
            Dir=3;
            break;
        }
        if (e== - 16777234) break;
    }
}

int Serpent::getDir(){
    return Dir;
}

void Serpent::setDir(int n){
    Dir = n ;
}

point Serpent::getTete(){
    return Serp[0];
}

point Serpent::getQueue(){
    return Serp[Taille-1];
}

void Serpent::serp(point a[taille_max]) {
    for (int i=0;i<Taille;i++) a[i]=Serp[i];
}

void Serpent::avance(Color col){
    for (int i=0;i<Taille;i++) Serp[Taille-i]=Serp[Taille-i-1];
    Serp[0]=Serp[1]+dir[Dir];
    fillRect(w*Serp[0].x,h*Serp[0].y,w,h,RED);
    fillRect(w*Serp[1].x,h*Serp[1].y,w,h,col);
}

void Serpent::avance(Color col,NativeBitmap moto,NativeBitmap blanc){

    for (int i=0;i<Taille;i++) Serp[Taille-i]=Serp[Taille-i-1];
    Serp[0]=Serp[1]+dir[Dir];
    putNativeBitmap(w*Serp[0].x,h*Serp[0].y, moto);
    putNativeBitmap(w*Serp[1].x,h*Serp[1].y, blanc);
    fillRect(w*Serp[1].x,h*Serp[1].y,w,h,col);
}

void Serpent::avance_snake(){
    for (int i=0;i<Taille;i++) Serp[Taille-i]=Serp[Taille-i-1];
    Serp[0]=Serp[1]+dir[Dir];
    fillRect(w*Serp[0].x,h*Serp[0].y,w,h,RED);
    fillRect(w*Serp[1].x,h*Serp[1].y,w,h,BLACK);
    fillRect(w*Serp[1].x+1,h*Serp[1].y+1,w-2,h-2,GREEN);
    fillRect(w*Serp[Taille].x,h*Serp[Taille].y,w,h,WHITE);
}

void Serpent::init(){
    int centre=int(z/3);
    point a={Random(centre,2*centre),Random(centre,2*centre)};
    Serp[0]=a;
    Taille=1;
    fillRect(w*Serp[0].x,h*Serp[0].y,w,h,RED);
    Dir=Random(0,3);
}

int Serpent::getTaille(){
    return Taille;
}

void Serpent::aug_taille(){
    Taille+=1;
}


















