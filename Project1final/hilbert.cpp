//DRIVER: Malek Khaled Zaben
//NAVIGATOR: Thomas Bivins

#include <iostream>
#include "hilbert.h"

using namespace std;
//HilbertCurve Constructor: defines all objects required to create a HilbertCurve
HilbertCurve::HilbertCurve(int level, int size)
:rules(), turtle(size, size)
{
    InstructionList oddIL;
    oddIL.append(TURN_LEFT);
    oddIL.append(EVEN);
    oddIL.append(FORWARD);
    oddIL.append(TURN_RIGHT);
    oddIL.append(ODD);
    oddIL.append(FORWARD);
    oddIL.append(ODD);
    oddIL.append(TURN_RIGHT);
    oddIL.append(FORWARD);
    oddIL.append(EVEN);
    oddIL.append(TURN_LEFT);

    InstructionList evenIL;
    evenIL.append(TURN_RIGHT);
    evenIL.append(ODD);
    evenIL.append(FORWARD);
    evenIL.append(TURN_LEFT);
    evenIL.append(EVEN);
    evenIL.append(FORWARD);
    evenIL.append(EVEN);
    evenIL.append(TURN_LEFT);
    evenIL.append(FORWARD);
    evenIL.append(ODD);
    evenIL.append(TURN_RIGHT);
    
    const unordered_map<hilbert_t, const InstructionList*> subMap = {{EVEN, &evenIL}, {ODD, &oddIL}};

    rules.append(ODD);
    
    
    //apply substitution rules according to level
    for (int i = 0; i < level; i++)
    {
        rules.substitute(subMap);
    }
    
    
    //determine distance according to level and size
    double dis = size;
    for (int i = 0; i < level; i++)
    {
        dis = dis / 2;
    }
    rules.setDistance(dis);
    
    turtle.follow(rules);
    
    
}