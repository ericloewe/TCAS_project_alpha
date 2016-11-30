//  TCAS_comms.h

#include <exception>
#include <new>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "TCAS_defs.h"

#pragma once

#define DEFAULT_MSG_INIT_SIZE 256

using std::string;

class memBufException: public std::exception
{
    
    protected:
    
    std::string errMsg;
        
    public:
    memBufException(const string& message);
    
    virtual const char* what() const throw();
    

};

class memBuffer
{
    protected:
    
    char *buffer = nullptr;
    int maxSize = 0;
    int currSize = 0;
    
    
    void expand(int newSize);
    bool copy(char *msg, int msgLen);
    
    public:
    
    //Constructor with message and size
    memBuffer(char *msg, int size);
    //Constructor with size
    memBuffer(int size);
    //Default constructor, doesn't allocate space
    memBuffer();
    //Destructor
    ~memBuffer();
    
    void init(int initSize);
    //Append message to existing. Allocates space if needed
    bool append(char *msg, int size);
    //Truncate message to sizeToTruncate bytes
    bool truncate(int sizeToTruncate);
    //Get the actual message as a buffer of chars 
    void getContents(int& sizeFilled, const char* & outputBuffer);
    
};

class TCAS_msg
{
    public:
    
    char        header[16];
    uint64_t    ac_id;
    
    double      xPos;
    double      yPos;
    double      zPos;
    
    double      xSpd;
    double      ySpd;
    double      zSpd;
    
    char        status[16];
    uint64_t    intruderHex;
    char        resolution[16];
    double      resValue;
    
    uint32_t    CRC;
    
    //AC_state constructor
    TCAS_msg(AC_state state);
};

class broadcast_socket
{
    private:
    
    int sock_fd;
    struct sockaddr_in broadcastAddr;
    struct sockaddr* sendAddr;
    
    
    public:
    
    broadcast_socket(int port);
    bool transmitUpdatedStatus(AC_state ownState);
    int getUpdatedTargetsStatus(std::vector<AC_state>& targetsList);
    
    
    
};