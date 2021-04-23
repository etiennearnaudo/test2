// Imagine++ project
// Project:  Tp8
// Author:   keriven
// Date:     2007/10/23

// Programme TRON

#include "utils.h"
#include "serpent.h"
#include "grille.h"

//======================================
// Serpent

void maj_grille(Grille &grille,Serpent s){
    grille.set(s.getTete(),true);
}

bool collision(const Grille &grille,Serpent s){
    point Tete=s.getTete();
    if (Tete.x<0 or Tete.x>z-1) return true;
    if (Tete.y<0 or Tete.y>z-1) return true;
    return grille.get(Tete);
}

void toucheClavier(Serpent &S1,Serpent &S2){
    int e;
    while(true){
        e=Clavier();
        if (e==S1.getDir() or e==S2.getDir()) break;
        if (e==16777234 and S2.getDir()!=0){
            S2.setDir(2);
            break;
        }
        if (e==16777235 and S2.getDir()!=1){
            S2.setDir(3);
            break;
        }
        if (e==16777236 and S2.getDir()!=2){
            S2.setDir(0);
            break;
        }
        if (e==16777237 and S2.getDir()!=3){
            S2.setDir(1);
            break;
        }
        if (e==113 and S1.getDir()!=0){
            S1.setDir(2);
            break;
        }
        if (e==115 and S1.getDir()!=3){
            S1.setDir(1);
            break;
        }
        if (e==100 and S1.getDir()!=2){
            S1.setDir(0);
            break;
        }
        if (e==122 and S1.getDir()!=1){
            S1.setDir(3);
            break;
        }
        if (e== 0) break;
    }
}

void afficherScore(int s1,int s2){
    fillRect(w,h,w*5,h*2,WHITE);
    fillRect(w*(z-5),h,w*5,h*2,WHITE);
    string J1=std::to_string(s1);
    string J2=std::to_string(s2);
    drawString(w,h*2,"J1 :",RED,8);
    drawString(w*4,h*2,J1,RED,8);
    drawString(w*(z-5),h*2,"J2 :",RED,8);
    drawString(w*(z-2),h*2,J2,RED,8);
}

Serpent serpentInitialise(){
    point b[taille_max];
    int centre=int(z/3);
    point a={Random(centre,2*centre),Random(centre,2*centre)};
    b[0]=a;
    fillRect(w*b[0].x,h*b[0].y,w,h,RED);
    Serpent s(Random(0,3),b,1);
    return s;
}
//======================================
// Jeu TRON

void jeu_1p(){
    fillRect(0,0,w*z,h*z,WHITE);
    Grille grille;
    grille.init();
    Serpent serpent=serpentInitialise();
    bool encours=true;
    while(encours){
        maj_grille(grille,serpent);
        serpent.setDir();
        serpent.avance(GREEN);
        serpent.aug_taille();
        milliSleep(50);
        if (collision(grille,serpent)) encours=false;
    }
}

void jeu_2p(){
    int W,H;
    byte *rgb;
    loadColorImage(srcPath("moto_blue.bmp"),rgb,W,H);
    NativeBitmap motoBleue(W,H);
    motoBleue.setColorImage(0,0,rgb,W,H);
    loadColorImage(srcPath("moto_red.bmp"),rgb,W,H);
    NativeBitmap motoRouge(W,H);
    motoRouge.setColorImage(0,0,rgb,W,H);
    loadColorImage(srcPath("explosion.bmp"),rgb,W,H);
    NativeBitmap explosion(W,H);
    explosion.setColorImage(0,0,rgb,W,H);
    NativeBitmap blanc(W,H);

    fillRect(0,0,w*z,h*z,WHITE);
    Grille grille;
    Serpent s1;
    Serpent s2;
    bool encours;
    int score1=0,score2=0;
    while(true){
        grille.init();
        s1.init();
        s2.init();
        encours=true;
        afficherScore(score1,score2);
        while(encours){
            maj_grille(grille,s1);
            maj_grille(grille,s2);
            toucheClavier(s1,s2);
            s1.avance(BLUE,motoBleue,blanc);
            s2.avance(RED,motoRouge,blanc);
            s1.aug_taille();
            s2.aug_taille();
            milliSleep(50);
            if (collision(grille,s1)) {
                encours=false;
                point a=s1.getTete();
                putNativeBitmap(a.x*w,a.y*h,explosion);
                score2+=1;
            }
            if (collision(grille,s2)) {
                encours=false;
                point a=s2.getTete();
                putNativeBitmap(a.x*w,a.y*h,explosion);
                score1+=1;
            }
        }
        afficherScore(score1,score2);
        drawString(w*int(z/3),h*int(z/2),"CLIQUEZ POUR REJOUER",RED,14);
        click();
        fillRect(0,0,w*z,h*z,WHITE);
    }
}

void snake(){
    int W,H;
    byte *rgb;
    loadColorImage(srcPath("pomme.bmp"),rgb,W,H);
    NativeBitmap pomme(W,H);
    pomme.setColorImage(0,0,rgb,W,H);
    NativeBitmap blanc(W,H);

    fillRect(0,0,w*z,h*z,WHITE);
    Grille grille;
    Grille grille_pomme;
    grille.init();
    grille_pomme.init();
    Serpent serpent;
    serpent.init();
    bool encours=true;
    int j=0,a,b;
    int aucune_pomme=true;
    point queue,tete;
    while(encours){
        grille.set(serpent.getTete(),true);
        serpent.setDir();
        queue = serpent.getQueue();
        serpent.avance_snake();
        grille.set(queue,false);
        if (j%10==0 and aucune_pomme) {
            a=Random(0,z-1);
            b=Random(0,z-1);
            if (not(grille.get({a,b}))){
                grille_pomme.set({a,b},true);
                putNativeBitmap(w*a,h*b, pomme);
                aucune_pomme=false;
            }

        }
        tete = serpent.getTete();
        if (grille_pomme.get(tete)) {
            serpent.aug_taille();
            grille_pomme.set(tete,false);
            aucune_pomme=true;
            putNativeBitmap(w*tete.x,h*tete.y,blanc);
        }
        milliSleep(50);
        if (collision(grille,serpent)) encours=false;
        j+=1;
    }
}

void jeu_2p_bis(){
    fillRect(0,0,w*z,h*z,WHITE);
    Grille grille;
    Serpent s1;
    Serpent s2;
    bool encours;
    int score1=0,score2=0;
    string J1,J2;
    while(true){
        grille.init();
        s1.init();
        s2.init();
        encours=true;
        afficherScore(score1,score2);
        while(encours){
            maj_grille(grille,s1);
            maj_grille(grille,s2);
            toucheClavier(s1,s2);
            s1.avance(BLUE);
            s2.avance(GREEN);
            s1.aug_taille();
            s2.aug_taille();
            milliSleep(50);
            if (collision(grille,s1)) {
                encours=false;
                score2+=1;
            }
            if (collision(grille,s2)) {
                encours=false;
                score1+=1;
           }
        }
        afficherScore(score1,score2);
        drawString(w*int(z/3),h*int(z/2),"CLIQUEZ POUR REJOUER",RED,14);
        click();
        fillRect(0,0,w*z,h*z,WHITE);
    }
}


int main()
{   initRandom();
	openWindow(w*z,h*z);

    jeu_1p();
    drawString(w*int(z/3),h*int(z/2),"CLIQUEZ POUR SNAKE",RED,14);
    click();
    snake();
    drawString(w*int(z/3),h*int(z/2),"CLIQUEZ POUR TRON",RED,14);
    drawString(w*int(z/3+3/2),h*(int(z/2)+4),"TOUCHES J2 : Z,Q,S,D",RED,11);
    drawString(w*int(z/3+9/2),h*(int(z/2)+2),"J1 : ROUGE",RED,11);
    drawString(w*int(z/3+9/2),h*(int(z/2)+3),"J2 : BLEU",RED,11);
    click();
    jeu_2p();
//    jeu_2p_bis();

	endGraphics();
	return 0;
}
