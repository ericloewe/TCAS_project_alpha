//TCAS_comms.cpp

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include "TCAS_comms.h"


//memBufException stuff


memBufException::memBufException(const string& message)
{
    errMsg = message;
}

const char* memBufException::what() const throw()
{
    return errMsg.c_str();
}




//
// Constructors and destructor
//
    
/* Constructor with message and size
    
    Creates memBuffer object with buffer of size bytes, to which
    the first size bytes of msg will be copied.
*/
memBuffer::memBuffer(char *msg, int size)
{
    init(size);
    
    if (!copy(msg, size))
    {
        //Bad init
        //If this code executes, something is very wrong
        throw memBufException("Unable to copy size bytes into memBuffer!");
    }
}

/*  Constructor with size
    
    Creates memBuffer object with buffer of size bytes, which will be empty
*/
memBuffer::memBuffer(int size)
{
    init(size); //Heavy lifting has already been taken care of
}

/*  Default constructor
    
    This one is useless, really
*/
memBuffer::memBuffer()
{
    //Do nothing
}

/*  Destructor
    
    Not much to see here
*/
memBuffer::~memBuffer()
{
    //Buffer is the only thing that needs treatment
    if (buffer != nullptr)
    {
        delete[] buffer;
    }
}

/*  Initialize memBuffer with desired size
    
    intiSize - Size of the buffer to allocate
    
    Defaults to DEFAULT_MSG_INIT_SIZE for invalid sizes
    
    Throws memBufException if allocation fails
    Throws TODO: SOMETHING if memBuffer is already initialized
    
*/
void memBuffer::init(int initSize)
{
    if (buffer != nullptr) //Don't init if it's already been done
    {
        throw memBufException("Tried to initialize initialized memBuffer!");
    }
    
    if (initSize < 1) //Use default size
    {
        initSize = DEFAULT_MSG_INIT_SIZE;
    }
    
    //buffer = (char*)calloc(initSize, 1);
    buffer = new char[initSize];
    
    if (buffer == nullptr)
    {
        throw memBufException("Calloc returned NULL!");
    }
    
    maxSize = initSize;
    currSize = 0;
    
    return;
}

/* Expands initialized memBuffer to a new size

    newSize  - Size of the newly-allocated buffer
    
    Despite its name, expand will happilly truncate memBuffers to 
    smaller sizes.
    
    Throws memBufException if allocation fails
    Throws TODO: SOMETHING if memBuffer is already initialized
*/
void memBuffer::expand(int newSize)
{
    //Check if memBuffer has been initialized
    //If not, throw an exception
    
    if (buffer == nullptr)
    {
        throw memBufException("memBuffer not initialized!");
    }
    
    //Allocate a new memory region
    
    //char *newBuf = (char*)calloc(newSize, 1);
    char *newBuf = new char[newSize];
    
    if (newBuf == nullptr)
    {
        throw memBufException("Calloc returned NULL!");
    }
    
    //Copy contents over to newBuf
    //Start by using the smallest of newSize and currSize    
    int sizeToCopy;
    if (newSize > currSize)
    {
        sizeToCopy = currSize;
    }
    else
    {
        sizeToCopy = newSize;
        currSize = newSize; //We truncated the message
    }
    memcpy(newBuf, buffer, sizeToCopy);
    
    //Cleanup time
    free(buffer);
    
    buffer = newBuf;
}

/* Copy an existing message into our memBuffer
    
    All new bytes are placed starting at memBuffer[currSize]
    
    msg     - Pointer to existing memory to copy
    msgLen  - Size of memory to copy
    
    If msgLen + currSize > maxSize, copy does nothing
    
    Return value indicates whether the addition to the message fits and was
    thus presumably successful
*/
bool memBuffer::copy(char *msg, int msgLen)
{
    if (buffer == nullptr)
    {
        throw memBufException("memBuffer not initialized!");
    }
    
    if (msgLen + currSize > maxSize) //Do nothing, return false
    {
        return false;
    }
    
    char *start = buffer + currSize;
    
    memcpy(start, msg, msgLen);
    
    currSize += msgLen;
    
    return true;
}


//Append message to existing. Allocates space if needed
bool memBuffer::append(char *msg, int size)
{
    if (buffer == nullptr)
    {
        throw memBufException("memBuffer not initialized!");
    }
    
    if (currSize + size > maxSize)
    {
        //Expand memBuffer
        expand(currSize + size);
    }
    
    if (!copy(msg, size))
    {
        //TODO Throw exception
        
        return false;
    }
    
    return true;
}

//Truncate message to sizeToTruncate bytes
bool memBuffer::truncate(int sizeToTruncate)
{
    if (buffer == nullptr)
    {
        throw memBufException("memBuffer not initialized!");
    }
    
    //There's really no good reason to reduce the size of the memBuffer, 
    //so let's keep things simple
    
    if (maxSize >= sizeToTruncate)
    {
        if (sizeToTruncate < currSize)
        {
            currSize = sizeToTruncate;
            return true;
        }
    }
}

//Get the actual message as a buffer of chars 
void memBuffer::getContents(int& sizeFilled, const char* & outputBuffer)
{
    if (buffer == nullptr)
    {
        throw memBufException("memBuffer not initialized!");
    }
    
    sizeFilled = currSize;
    outputBuffer = buffer;
}


/*
 *  Actual networking stuff
 *
 *
 *
 */
 
/*
 *  Init constructor
 */ 
broadcast_socket::broadcast_socket(int port)
{
    //Create an IPv4 UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sock_fd < 1)
    {
        //TODO - Throw exception
        std::cout << "Socket creation failed and should've thrown an exception" << std::endl;
        exit(-1);
    }
    
    
    
    char broadcastIP[] = "255.255.255.255";
    int broadscastPort = port;
    
    int broadcastPerm = 1;
    
    //Set broadcast permission to true
    if (setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, 
                   (void *) &broadcastPerm, sizeof(broadcastPerm)) < 0)
    {
        //TODO - Throw exception
        std::cout << "setsockopt failed miserably" << std::endl;
        exit(-1);
    }
    
    //Set loopback to false, may be useful in the future
    /*
        char loopch=0;

        if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP,
                       (char *)&loopch, sizeof(loopch)) < 0) {
          perror("setting IP_MULTICAST_LOOP:");
          close(sd);
          exit(1);
        }
    
    */
      
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
    broadcastAddr.sin_port = htons(broadscastPort);
    
    sendAddr = (sockaddr*) &broadcastAddr;
    int sendAddrSize = sizeof(broadcastAddr);
    
    string testString = "This is a test string";
    
    if (sendto(sock_fd, testString.c_str(), testString.length(), 0, 
                sendAddr, sendAddrSize) != testString.length())
    {
        fprintf(stderr, "sendto error");
        exit(1);
    }
    
    

}  

/*
 *  updateTCASStatus - Update the message's own state fields
 */
void TCAS_msg::updateOwnStatus(AC_state state)
{
    ac_id = state.getID();
    
    xPos = state.getX_pos();
    yPos = state.getY_pos();
    zPos = state.getZ_pos();
    
    xSpd = state.getX_spd();
    ySpd = state.getY_spd();
    zSpd = state.getZ_spd();
}

/*
 *  updateTCASStatus - Update the message's TCAS fields
 */
void TCAS_msg::updateTCASStatus(TCAS_state state)
{
    strncpy(status, state.status, 16);
    strncpy(resolution, state.resolution, 16);
    intruderHex = state.intruder_hex;
    resValue = state.res_value;
}

/*  
 *  Constructor: Use existing AC_state to initialize the message.
 *
 *      TCAS status data is not initialized
 *
 *      CRC32 is calculated only upon transmission
 */
TCAS_msg::TCAS_msg(AC_state state)
{
    //Set the correct header
    strncpy(header, TCAS_MSG_HEADER, TCAS_MSG_STRLEN);
    
    this.updateOwnStatus(state);
    
    //We don't have TCAS status data
    
    //CRC32 is calculated just before transmission
}

/*  
 *  Constructor: Use existing AC_state and TCAS_state to initialize 
 *                  the message.
 *
 *      CRC32 is calculated only upon transmission
 */
TCAS_msg::TCAS_msg(AC_state state, TCAS_state situation)
{
    //Set the correct header
    strncpy(header, TCAS_MSG_HEADER, TCAS_MSG_STRLEN);
    
    this.updateOwnStatus(state);
    this.updateTCASStatus(situation);
    
    //CRC32 is calculated just before transmission
}
    
void broadcast_socket::transmitUpdatedStatus(AC_state ownState, TCAS_state tcasSituation)
{
    TCAS_msg msg(ownState, tcasSituation);
    
    //Calculate CRC32
    
    //send the data
    int bytes = sendto(sock_fd, (void *) &msg, sizeof(TCAS_msg), 0, 
                sendAddr, sendAddrSize);
                
    if (bytes != sizeof(TCAS_msg))
    {
        //TODO: Throw exception
        
    }
    
    return true;
}   
    
    
    
    
    
    
    
    
