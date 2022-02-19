#ifndef GermanInfantry_h
#define GermanInfantry_h
#include "Infantry.h"
class GermanInfantry : public Infantry {

public:
 GermanInfantry();
 virtual void move();
 virtual void fight();
 virtual string getName();
private:
 string name;

};
#endif
