// FUNC_NAME: NetSession::receivePackets

#include <winsock2.h> // For sockaddr_in, htonl, etc.

// Global reentrancy guard counter
static int g_activeThreadCount = 0; // _DAT_01205a30

// External functions (likely from network library)
extern int socket(); // FUN_0065c190
extern int recvfrom(sockaddr* from, char* buf, int len); // FUN_00658390
extern void closeSocket(); // FUN_0064b440
extern void* PTR_LAB_00e42f38; // Some global structure, e.g. g_netSessionGlobal

class NetSession {
    // vtable at offset 0
    // int m_socketDescriptor at offset 0x64 (0x19 * 4)
    // virtual void onDataReceived(sockaddr* from, void* context) at vtable+0xc (index 3)
public:
    void receivePackets();
    virtual void onDataReceived(sockaddr* from, void* context);
};

void NetSession::receivePackets() {
    int* thisPtr = this; // unaff_EDI, used as object pointer

    // Increment thread counter
    g_activeThreadCount++;

    // Buffer for received data
    char recvBuffer[1028]; // local_404

    // Sockaddr structure for the sender
    sockaddr_in fromAddr; // local_550 (combination of local_550, local_54e, local_54c, etc.)
    fromAddr.sin_family = 0;
    fromAddr.sin_port = 0;
    fromAddr.sin_addr.s_addr = htonl(INADDR_ANY); // local_54c = htonl(0)
    memset(fromAddr.sin_zero, 0, sizeof(fromAddr.sin_zero)); // local_540,544,548, etc.

    // Other local variables (not all used, but from decompilation)
    int recvLen = 0; // local_554
    char* activeBuffer = recvBuffer; // local_530
    int bufferSize = 0x400; // local_52c (1024)
    bool bufferAllocated = false; // local_528
    int something1 = 0x2000; // local_510
    int something2 = 0x2000; // local_50c
    void* context = &PTR_LAB_00e42f38; // local_53c
    // ... other zeroed locals

    // Create a socket
    int sock = socket(); // FUN_0065c190
    thisPtr[0x19] = sock; // store socket descriptor at offset 0x64

    // Main receive loop
    while (true) {
        // Receive data into recvBuffer
        int result = recvfrom((sockaddr*)&fromAddr, recvBuffer, &recvLen); // FUN_00658390
        // If buffer was allocated (from a previous iteration?) free it
        if (bufferAllocated) {
            bufferAllocated = false;
            free(activeBuffer); // _free
        }
        // Reset buffer pointers
        activeBuffer = recvBuffer;
        bufferSize = recvLen * 8; // why *8? Possibly a different unit
        // ... other resets

        if (result != 0) break; // On error, exit loop

        // Call virtual method to process packet
        (this->*(void (NetSession::*)(sockaddr*, void*)) (*(int**)this)[3])((sockaddr*)&fromAddr, context);
    }

    // Cleanup
    g_activeThreadCount--;
    closeSocket(); // FUN_0064b440
}