#include <iostream>
#include "TCAS_defs.h"
#include "Navigation.h"


//Default constructor
//Sets invalid AC_ID
AC_state::AC_state()
{
    AC_ID = 0;
}

//Standard constructor
//Sets all fields    
AC_state::AC_state(uint64_t ID, double xpos, double ypos, double zpos,
                double xspd, double yspd, double zspd)
{
    AC_ID = ID;
    
    x_pos = xpos;
    y_pos = ypos;
    z_pos = zpos;
    
    x_spd = xspd;
    y_spd = yspd;
    z_spd = zspd;
    
    time_of_issue = std::chrono::high_resolution_clock::now();
    
    //DEBUG
    auto duration = time_of_issue.time_since_epoch();
    std::cout << "High resolution timer: " << duration.count() << std::endl;
}

AC_state::AC_state(uint64_t ID, double Latitude, double Longitude, double Altitude){
    
    double Pos_llh[3] = {Latitude, Longitude, Altitude};
    double Pos_xyz[3];
    llh_to_xyz(Pos_llh, Pos_xyz);
    
    x_pos = Pos_xyz[0];
    y_pos = Pos_xyz[1];
    z_pos = Pos_xyz[2];
    
    x_spd = 0;
    y_spd = 0;
    z_spd = 0;
    
    time_of_issue = std::chrono::high_resolution_clock::now();
}
