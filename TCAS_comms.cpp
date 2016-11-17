//TCAS_comms.cpp

#include <cstdlib>
#include <cstring>
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

    
    

    
    
    
    
    
    
    
    
    
    
    
