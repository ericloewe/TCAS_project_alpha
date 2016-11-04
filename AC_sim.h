#pragma once

#include "TCAS_defs.h"

class AC_sim
{
    private:
    
    AC_state state;
    
    void advanceToNow();
    
    public:
    
    //Constructor with initial state
    AC_sim(AC_state initState);
    
    //Get the current aircraft simulation state
    //Used to update the TCAS simulation and to acquire
    //data to send over the network
    AC_state getCurrentState();
    
    //bool cmdInputs();
    
    void runSim(int freq);
    
    
    
    
}