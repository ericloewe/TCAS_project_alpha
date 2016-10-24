/*
 *  TCAS_sim.h
 */
 
#include "TCAS_defs.h"
 
class TCAS_sim
{

    
private:
    AC_state ownState;
    AC_state targetStates[8];
 
    //TODO: Some sort of collisions object
    
    
public:
    bool TCAS_simUpdateOwnState(AC_state);
    bool TCAS_simUpdateTargetState(AC_state);
 
    int TCAS_simDo();
    //TODO: getter for collisions object
    
    
}
 
