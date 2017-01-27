#pragma once

#include <chrono>


const uint64_t own_hex = 216412359;

class AC_state
{
    friend class AC_sim; //to access the positions and velocities
    friend class TCAS_sim; //to access AC_ID
    friend void printState(AC_state state);
    
private:
    uint64_t AC_ID;
    
    double x_pos;
    double y_pos;
    double z_pos;
    
    double x_spd;
    double y_spd;
    double z_spd;
    
    std::chrono::time_point<std::chrono::high_resolution_clock> time_of_issue;
    
   
    
public:
    //Default constructor, marks as invalid state
    AC_state();
    AC_state(uint64_t ID, double xpos, double ypos, double zpos,
                double xspd, double yspd, double zspd);
                
    AC_state(uint64_t ID, double Latitude, double Longitude, double Altitude); //velocity to be defined by commands
    
};
