#include <iostream>
#include "TCAS_defs.h"


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
