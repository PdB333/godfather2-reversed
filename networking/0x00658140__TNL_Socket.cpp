// Xbox PDB: TNL::Socket
// FUNC_NAME: SocketManager::onSocketDestroy

// Function at 0x00658140: Called during Socket destruction for debug tracking and reference counting.
// Implements a state machine for different destruction paths (state 2 or 1) and handles
// debug logging of socket destruction events. Also maintains a counter and may trigger
// breakpoints under certain conditions.

// Global state variables:
// g_socketDestructionState (DAT_01205a68) - Current destruction mode (2 or 1)
// g_socketDestructionFlag (DAT_0120589a) - Flag enabling debug tracking
// g_socketDebugFlags (DAT_01225da0) - Bitmask to avoid duplicate registration
// g_socketDebugString1 (DAT_01225d94) - "Socket::~Socket" debug string entry
// g_socketDebugString2 (DAT_01225d88) - Second copy for state 1
// g_socketDebugHead (DAT_01205a84) - Linked list head of debug entries
// g_socketDestructionCounter (DAT_01205a80) - Number of destructions processed
// g_socketMaxDestructions (DAT_01205a7c) - Maximum allowed destructions (breakpoint threshold)
// g_otherFlag1 (DAT_01127d3c) - Another flag for conditional breakpoint
// g_otherThreshold (DAT_01127d38) - Threshold compared with g_anotherVar (DAT_01205a6c)
// g_socketRefCount (DAT_01205a30) - Global Socket reference count, decremented at end

struct DebugEntry {
    const char* name;
    int lineNumber;
    int unknown;
    DebugEntry* next;
};

// External globals (declared elsewhere)
extern int g_socketDestructionState;
extern char g_socketDestructionFlag;
extern int g_socketDebugFlags;
extern DebugEntry g_socketDebugEntry1; // at DAT_01225d94
extern DebugEntry g_socketDebugEntry2; // at DAT_01225d88
extern DebugEntry* g_socketDebugHead;
extern int g_socketDestructionCounter;
extern int g_socketMaxDestructions;
extern char g_otherFlag1;
extern int g_otherThreshold;
extern int g_anotherVar; // at DAT_01205a6c
extern int g_socketRefCount;

// Helper functions (callees)
void registerDebugEntry(DebugEntry* entry); // FUN_0065f6b0
void finalizeDestruction(); // FUN_0065fab0

void SocketManager::onSocketDestroy()
{
    // Check destruction mode and flag
    if (g_socketDestructionState == 2)
    {
        if (g_socketDestructionFlag != 0)
        {
            // If debug entry 1 not yet registered, add it
            if ((g_socketDebugFlags & 1) == 0)
            {
                g_socketDebugFlags |= 1;
                g_socketDebugEntry1.name = "Socket::~Socket";
                g_socketDebugEntry1.lineNumber = -1;
                g_socketDebugEntry1.unknown = (int)g_socketDebugHead;
                g_socketDebugHead = &g_socketDebugEntry1;
            }
            registerDebugEntry(&g_socketDebugEntry1);
            g_socketDestructionCounter++;
            
            // Check if maximum destructions reached (trigger breakpoint)
            if ((g_socketMaxDestructions != 0) && (g_socketMaxDestructions <= g_socketDestructionCounter))
            {
                __debugbreak(); // swi(3)
                return;
            }
            
            // Another conditional breakpoint
            if ((g_otherFlag1 == 0) && (g_otherThreshold < g_anotherVar))
            {
                return;
            }
            __debugbreak(); // swi(3)
            return;
        }
    }
    else if ((g_socketDestructionState == 1) && (g_socketDestructionFlag != 0))
    {
        // Similar for state 1, using debug entry 2
        if ((g_socketDebugFlags & 2) == 0)
        {
            g_socketDebugFlags |= 2;
            g_socketDebugEntry2.name = "Socket::~Socket";
            g_socketDebugEntry2.lineNumber = -1;
            g_socketDebugEntry2.unknown = (int)g_socketDebugHead;
            g_socketDebugHead = &g_socketDebugEntry2;
        }
        registerDebugEntry(&g_socketDebugEntry2);
        finalizeDestruction();
    }
    
    // Decrement global reference count
    g_socketRefCount--;
    return;
}