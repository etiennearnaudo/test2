#include "utils.h"

//======================================
// Structure point

point operator+(point a,point b){
    return {a.x+b.x,a.y+b.y};
}

point operator-(point a,point b){
    return {a.x-b.x,a.y-b.y};
}


//======================================
// Gestion du clavier

int Clavier() {
	Event e;
    do {
        getEvent(0,e);
		if (e.type==EVT_KEY_ON)
            return e.key;
    } while (e.type!=EVT_NONE);
	return 0;
}

//=======================================
// Autre

void InitRandom()
{
    srand((unsigned int)time(0));
}

int Random(int a, int b)
{
    return int(a + (rand()%(b-a+1)));
}

