/* 
 *  Copyright notice
 *
 *
 *
 */


#include <iostream>
#include <unistd.h>
#include "TCAS_defs.h"
#include "AC_sim.h"

void printState (AC_state state);

using std::cout; using std::endl;

int main(int argn, char *argv[])
{
    std::cout << "TCAS simulator Group C\n";
    std::cout << "Initializing...\n";
    
    //TODO - Acquire starting coordinates
    std::cout << "Using default initial state: x=0;0;0 v=200;0;0\n";
    double xinit = 0;
    double yinit = 0;
    double zinit = 0;
    
    double xdotinit = 200;
    double ydotinit = 0;
    double zdotinit = 0;
    
    //TODO - Initialize own model
    AC_state ownInitState(own_hex, xinit, yinit, zinit, xdotinit, ydotinit,
                            zdotinit);
    
    AC_sim ownAircraft(ownInitState);
    
    while(1)
    {
        sleep(1);
        
        printState(ownAircraft.getCurrentState());
        
    }
    
    //TODO - Initialize networking
    
    //TODO - Initialize TCAS simulator
    
    //TODO - Initialize TCAS resolver
    
    //TODO - Graphical visualization
    
    //TODO - Cleanup
}

void printState (AC_state state){
    cout << "Aircraft ID: " << state.AC_ID << endl;
    cout << "Position: " << state.x_pos << "; " << state.y_pos << "; " << state.z_pos << endl;
    cout << "Velocity: " << state.x_spd << "; " << state.y_spd << "; " << state.z_spd << endl;
}
