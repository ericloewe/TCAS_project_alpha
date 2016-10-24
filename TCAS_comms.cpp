//TCAS_comms.cpp

#include <cstdlib>
#include <cstring>
#include "TCAS_comms.h"


    /* Initialize memBuffer with desired size
        
        intiSize - Size of the buffer to allocate
        
        Defaults to DEFAULT_MSG_INIT_SIZE for invalid sizes
        
        Throws std::bad_alloc if allocation fails
        Throws TODO: SOMETHING if memBuffer is already initialized
        
    */
    void init(int initSize)
    {
        if (buffer != nullptr) //Don't init if it's already been done
        {
            //TODO: Throw exception
        }
        
        if (initSize < 1) //Use default size
        {
            buffer = (char*)calloc(DEFAULT_MSG_INIT_SIZE, 1);
            
            if (buffer == nullptr)
            {
                throw std::bad_alloc("Calloc returned NULL!");
            }
            
            maxSize = DEFAULT_MSG_INIT_SIZE;
            currSize = 0;
            
            return;
        }
        else
        {
            buffer = (char*)calloc(initSize, 1);
            
            if (buffer == nullptr)
            {
                throw std::bad_alloc("Calloc returned NULL!");
            }
            
            maxSize = initSize;
            currSize = 0;
            
            return;
        }
    }
    
    /* Expands initialized memBuffer to a new size
    
        newSize  - Size of the newly-allocated buffer
        
        Despite its name, expand will happilly truncate memBuffers to 
        smaller sizes.
        
        Throws std::bad_alloc if allocation fails
        Throws TODO: SOMETHING if memBuffer is already initialized
    */
    void expand(int newSize)
    {
        //Check if memBuffer has been initialized
        //If not, throw an exception
        
        if (buffer == nullptr)
        {
            //TODO: Throw exception
        }
        
        //Allocate a new memory region
        
        char *newBuf = (char*)calloc(newSize, 1);
        
        if (newBuf == nullptr)
        {
            throw std::bad_alloc("Calloc returned NULL!");
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
    bool copy(char *msg, int msgLen)
    {
        if (msgLen + currSize > maxSize) //Do nothing, return false
        {
            return false;
        }
        
        char *start = buffer + currSize;
        
        memcpy(start, msg, msgLen);
        
        currSize += msgLen;
        
        return true;
    }
    
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
            //TODO: Throw exception
        }
    }
    //Constructor with size
    memBuffer::memBuffer(int size);
    //Default constructor, doesn't allocate space
    memBuffer::memBuffer();
    //Destructor
    memBuffer::~memBuffer();
    
    //Append message to existing. Allocates space if needed
    append(char *msg, int size);
    //Truncate message by sizeToTruncate bytes
    truncate(int sizeToTruncate);