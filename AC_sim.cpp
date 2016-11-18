#include "AC_sim.h"

AC_sim::AC_sim(AC_state initState)
{
    state = initState;
}

void AC_sim::step(milliseconds stepDuration)
{
    state.x_pos += state.x_spd*(double)stepDuration.count()/1000.0;
    state.y_pos += state.y_spd*(double)stepDuration.count()/1000.0;
    state.z_pos += state.z_spd*(double)stepDuration.count()/1000.0;
    
    state.time_of_issue += stepDuration;
}

void AC_sim::advanceToNow()
{
    milliseconds stepDuration = duration_cast<milliseconds>(std::chrono::high_resolution_clock::now() - state.time_of_issue);
    
    step(stepDuration);
    
}

AC_state AC_sim::getCurrentState(){
    advanceToNow();
    return state;
}
