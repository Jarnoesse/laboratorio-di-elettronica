#ifndef ArmyFactory_h
#define ArmyFactory_h
#include <vector>
using std::vector;
#include "Unit.h"
class ArmyFactory {

public:
 virtual ~ArmyFactory(){};
 virtual vector<Unit*> getArmy() const = 0;
};
#endif /* ArmyFactory_h */
