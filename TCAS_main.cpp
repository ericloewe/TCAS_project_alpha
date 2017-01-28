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
#include "Radar.h"

void printState (AC_state state);

using std::cout; using std::endl;

int main(int argn, char *argv[])
{
    std::cout << "TCAS simulator Group C\n";
    std::cout << "Initializing...\n";
    
    Radar_initialize();
    
    //TODO - Acquire starting coordinates
    std::cout << "Using default initial state: x=0;0;0 v=200;0;0\n";
    double xinit = 0;
    double yinit = 0;
    double zinit = 0;
    
    double xdotinit = 200;
    double ydotinit = 0;
    double zdotinit = 0;
    
    AC_state ownInitState(own_hex, 0, 0, 1000); //1000m above S.Tomé e Príncipe
    AC_sim ownAircraft(ownInitState);
    ownAircraft.set_controls(270, 0, pi/2);
    
    while(1)
    {
        sleep(1);
        
        printState(ownAircraft.getCurrentState());
        //Radar_update(ownAircraft, 
        
    }
    
    //TODO - Initialize networking
    
    //TODO - Initialize TCAS simulator
    
    //TODO - Initialize TCAS resolver
    
    //TODO - Graphical visualization
    
    //TODO - Cleanup
}

void printState (AC_state state){
    cout << "Aircraft ID: " << state.AC_ID << endl;
    
    double P_xyz[3] = {state.x_pos, state.y_pos, state.z_pos};
    double P_llh[3];
    
    xyz_to_llh(P_xyz, P_llh);
    
    cout << "Position: ";
    for(int i=0; i<2; i++)
        cout << P_llh[i]*180/pi << "º ";
    cout << P_llh[2] << "m " << endl;
    
    double V_xyz[3] = {state.x_spd, state.y_spd, state.z_spd};;
    double V_enu[3];
    xyz_to_enu(V_xyz, P_llh[0], P_llh[1], V_enu);
    
    cout << "Velocity: ";
    for(int i=0; i<3; i++)
        cout << V_enu[i] << " ";
    cout << "(m/s)" << endl;
    
    /*cout << "Position: " << state.x_pos << "; " << state.y_pos << "; " << state.z_pos << endl;
    cout << "Velocity: " << state.x_spd << "; " << state.y_spd << "; " << state.z_spd << endl;*/
    
}
