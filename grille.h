#ifndef GRILLE_H
#define GRILLE_H

#include "utils.h"
#include "serpent.h"

class Grille{
    bool grille[z][z];
public:
    void init();
    bool get(point a) const;
    void set(point a,bool booleen);
};

#endif // GRILLE_H
