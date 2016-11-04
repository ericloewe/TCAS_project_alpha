/* 
 *  Copyright notice
 *
 *
 *
 */


#include <iostream>
#include "TCAS_defs.h"
 
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
    
    //TODO - Initialize networking
    
    //TODO - Initialize TCAS simulator
    
    //TODO - Initialize TCAS resolver
    
    //TODO - Graphical visualization
    
    //TODO - Cleanup
}