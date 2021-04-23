#pragma once

#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

const int w=20;
const int h=20;
const int z=49;


//======================================
// Structure point

struct point
{
	int x;
	int y;
};


const int droite = 0;
const int bas = 1;
const int gauche = 2;
const int haut = 3;
const point dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};

point operator+(point a,point b);

point operator-(point a,point b);

//======================================
// Gestion du clavier

int Clavier();

void InitRandom();

int Random(int a, int b);
