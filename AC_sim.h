#pragma once

#include "TCAS_defs.h"
#include <chrono>


//typedef std::chrono::duration<long long int> milliDuration;
using namespace std::chrono;

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
    
    private:
    void step(milliseconds stepDuration);
    
};
