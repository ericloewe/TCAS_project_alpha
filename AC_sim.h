#include "TCAS_defs.h"

class AC_sim
{
    private:
    
    AC_state state;
    
    void advanceToNow();
    
    public:
    
    AC_sim(AC_state initState);
    AC_state getCurrentState();
    
    //bool cmdInputs();
    
    void runSim(int freq);
    
    
    
    
}