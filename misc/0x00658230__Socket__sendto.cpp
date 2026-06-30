// FUNC_NAME: Socket::sendto

#include <winsock2.h> // For WSAEWOULDBLOCK

// Forward declarations of internal functions
void __cdecl FUN_0065f6b0(const char *profileName); // Add profile entry
void __cdecl FUN_0065fab0();                          // Start profiling?
int  __cdecl FUN_00657f80(int *pResult);             // Thread-safe wrapper? Possibly obtains socket ID
int  __cdecl FUN_00657f00(void *buf, int len, int socketId, void *to); // Actual sendto syscall

// Global profiling/data globals
extern int gNetworkMode;        // DAT_01205a68 - network mode (1=send,2=recv?)
extern char gEnableProfiling;   // DAT_0120589a
extern int gProfileCallCount;   // DAT_01205a80
extern int gProfileBreakCount;  // DAT_01205a7c - break after this many calls
extern void *gProfileNameList;  // DAT_01205a84 - pointer to profile name linked list
extern int gSomeOtherFlag;      // DAT_01127d3c
extern int gSomeOtherCounter;   // DAT_01127d38
extern int gMaxSomeValue;       // DAT_01205a6c

// Profiling list header (linked list of profile entries)
struct ProfileEntry {
    char name[64];     // +0x00
    int callCount;     // +0x40
    int unknown;       // +0x44
    ProfileEntry *next; // +0x48
};

// Static profile entries used for this function
static ProfileEntry gSendtoProfileSend = { "Socket::sendto", -1, 0, nullptr }; // DAT_01225d6c
static ProfileEntry gSendtoProfileRecv = { "Socket::sendto", -1, 0, nullptr }; // DAT_01225d78

// Structure for the socket object (minimal)
struct Socket {
    int socketHandle; // +0x04
    // ... other fields
};

// Function: 0x00658230 - Socket::sendto
// Wraps the actual sendto syscall with profiling and error handling.
// Returns: 0 on success, 1 on handle mismatch, 2 on WSAEWOULDBLOCK, 3 on other errors.
int Socket::sendto(Socket *thisSocket, void *buf, int len, void *to) {
    int status;
    int socketId;
    ProfileEntry *profileEntry;
    
    // Profiling section
    if (gNetworkMode == 2) { // Receive mode?
        if (gEnableProfiling != 0) {
            if ((gSendtoProfileRecv.callCount & 1) == 0) { // First time?
                gSendtoProfileRecv.callCount |= 1;
                // Initialize profiler entry
                gSendtoProfileRecv.name = "Socket::sendto"; // Already set
                // Link into global list
                gSendtoProfileRecv.next = (ProfileEntry *)gProfileNameList;
                gProfileNameList = &gSendtoProfileRecv;
            }
            FUN_0065f6b0(&gSendtoProfileRecv.name);
            gProfileCallCount++;
            if ((gProfileBreakCount != 0) && (gProfileBreakCount <= gProfileCallCount)) {
                // Trigger breakpoint (swi 3)
                __asm { int 3 } // Debug break
                return 0; // Unlikely, but the decompiler shows a return after swi
            }
            if ((gSomeOtherFlag == 0) && (gSomeOtherCounter < gMaxSomeValue)) {
                return 0; // Early exit due to some limiting condition
            }
            // Continue to actual send
        }
    }
    else if (gNetworkMode == 1) { // Send mode
        if (gEnableProfiling != 0) {
            if ((gSendtoProfileSend.callCount & 2) == 0) { // First time?
                gSendtoProfileSend.callCount |= 2;
                gSendtoProfileSend.name = "Socket::sendto";
                gSendtoProfileSend.next = (ProfileEntry *)gProfileNameList;
                gProfileNameList = &gSendtoProfileSend;
            }
            FUN_0065f6b0(&gSendtoProfileSend.name);
            FUN_0065fab0(); // Possibly start timing
        }
    }
    
    // Validate socket handle consistency
    // The original code reads *in_EAX which is presumably the socket handle from some register/global.
    // We'll assume it's the return of a prior call or the first argument.
    // Let's assume the socket handle is passed directly (e.g., thisSocket->socketHandle).
    if ((unsigned int)thisSocket->socketHandle != *(unsigned int *)(thisSocket + 4)) {
        return 1; // Handle mismatch
    }
    
    // Thread-safe wrapper to get a socket ID for the syscall
    socketId = 0;
    FUN_00657f80(&socketId);
    
    // Perform actual sendto
    status = FUN_00657f00(buf, len, socketId, to);
    
    if (status >= 0) {
        return 0; // Success
    } else {
        // Handle errors
        // If not WSAEWOULDBLOCK, return 2; else return 3? Actually the code:
        // return (iVar2 != 0x2733) + 2;
        // So if iVar2 == WSAEWOULDBLOCK (0x2733), returns 2; otherwise returns 3.
        return (status != WSAEWOULDBLOCK) + 2;
    }
}