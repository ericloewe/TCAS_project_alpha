#pragma once

#include <chrono>


const uint64_t own_hex = 216412359;

class AC_state
{
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
                
    uint64_t getID();
    double getX_pos();
    double getY_pos();
    double getZ_pos();
    double getX_spd();
    double getY_spd();
    double getZ_spd();
    
};