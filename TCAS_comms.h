//  TCAS_comms.h

#define DEFAULT_MSG_INIT_SIZE 256

class memBuffer
{
    private:
    
    char *buffer = nullptr;
    int maxSize = 0;
    int currSize = 0;
    
    void init(int initSize);
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
    
    //Append message to existing. Allocates space if needed
    bool append(char *msg, int size);
    //Truncate message by sizeToTruncate bytes
    bool truncate(int sizeToTruncate);
    
    
}

class broadcast_socket
{
    private:
    
    int sock_fd;
    
    
    public:
    
    broadcast_socket(int port);
    send()
    
}