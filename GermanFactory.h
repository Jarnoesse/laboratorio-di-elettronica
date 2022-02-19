#ifndef GermanFactory_h
#define GermanFactory_h
#include <vector>
using std::vector;
#include "Unit.h"
#include "ArmyFactory.h"
class GermanFactory : public ArmyFactory{

public:
 GermanFactory();
 ~GermanFactory();
 int sizeUnit() const;
 vector<Unit*>::const_iterator beginUnit() const;
 vector<Unit*>::const_iterator endUnit() const;
 vector<Unit*> getArmy() const;
private:
 vector<Unit*> unit;

};
#endif /* GermanFactory_h */
