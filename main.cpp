class Unit//unità generica
{
};
class Tank:public Unit{//unità di carri
};
class Tiger:public Tank{ //carri
};
class T34:public Tank{
};
class  Infantry// fanteria
{
};
class  GermanInfantry:public Infantry// fanteria
{
};
class  RussianInfantry:public Infantry// fanteria
{
};
class Armyfactory{//esercito generico 
};
class GermanFactory:public Armyfactory{
};
class RussianFactory:public Armyfactory{
};

