/*
 *  TCAS_sim.h
 */

#pragma once
 
#include "TCAS_defs.h"

 
class TCAS_sim
{

    
private:
    AC_state ownState;
    AC_state targetStates[8];
 
    //TODO: Some sort of collisions object
    
    
public:
    //Insert new simulation parameters (from control inputs)
    bool UpdateOwnState(AC_state);
    //Insert new simulation parameters (from network)
    bool UpdateTargetState(AC_state);

    
    int TCAS_simDo();
    //TODO: getter for collisions object
    
    
}
 
