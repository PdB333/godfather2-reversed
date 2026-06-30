// FUNC_NAME: NodeAllocator::allocatePacketNode
// Address: 0x00615870
// This function manages a pool of 0x1000 packet nodes. It checks the state of the
// source slot (param_1), and if it's in state 3 (pending send), it removes the flag
// from the free bitmap, allocates a new node from a free list, initializes it,
// and returns it. The source and dest slots (param_1 and unaff_EDI) are indices
// into the global node table. Uses critical sections for thread safety.

#include <windows.h>

// Size of each node entry in the pool (0x38 bytes)
#define NODE_ENTRY_SIZE 0x38
#define MAX_NODES 0x1000

// Global arrays (from .data)
extern char g_nodeTable[MAX_NODES][NODE_ENTRY_SIZE]; // +0x011a0f28
extern unsigned int g_freeBitmapLow[MAX_NODES / 32];  // +0x011d8f28 (bitmap of free slots per 32-slot group)
extern unsigned int g_freeBitmapHigh[MAX_NODES / 32]; // +0x011d8f2c
extern unsigned int g_nextFreeSlotGroup;              // +0x011d9128
extern CRITICAL_SECTION g_nodeCritSection;            // +0x011d917c
extern int g_perfCounterActive;                       // +0x01222570
extern LARGE_INTEGER g_perfTimestamp;                 // +0x01205930

// Forward declarations
void* allocateNodeFromFreeList();                     // FUN_006157d0
void nodeListAdd(void* node, int param);              // FUN_00ab4db0
void profilingStart();                                 // FUN_00ab4e70
void profilingUpdate(int flag);                        // FUN_00ab51e0
void profilingFlush();                                 // FUN_00ab67c0

// __thiscall? Undetermined calling convention. We'll use standard C.
undefined4* allocatePacketNode(uint sourceSlot, undefined4 data, uint destSlot)
{
    char state;
    CRITICAL_SECTION* critSec;
    undefined4* newNode;
    uint groupIndex;
    LARGE_INTEGER perfCount;
    char* sourceEntry;
    char* destEntry;

    // Get pointer to source entry
    if (sourceSlot < MAX_NODES) {
        sourceEntry = &g_nodeTable[sourceSlot][0];
    } else {
        sourceEntry = NULL;
    }

    state = *sourceEntry; // first byte is state
    if ((state == 0x02) || (state == 0x03)) {
        // Get pointer to dest entry (from register)
        if (destSlot < MAX_NODES) {
            destEntry = &g_nodeTable[destSlot][0];
        } else {
            destEntry = NULL;
        }

        if (state == 0x03) {
            // Remove source slot from free bitmap
            groupIndex = sourceSlot >> 5; // group of 32 slots
            EnterCriticalSection(&g_nodeCritSection);
            // Clear the bit for sourceSlot
            unsigned __int64 bit = __allshl(1, sourceSlot & 0x1F);
            g_freeBitmapLow[groupIndex] &= ~(unsigned int)bit;
            g_freeBitmapHigh[groupIndex] &= ~(unsigned int)(bit >> 32);
            // Advance the next free group if this group became empty
            if ((groupIndex == g_nextFreeSlotGroup) &&
                (g_freeBitmapLow[groupIndex] == 0) &&
                (g_freeBitmapHigh[groupIndex] == 0)) {
                g_nextFreeSlotGroup++;
            }
            // Mark source entry as freed (state 5)
            *sourceEntry = 0x05;
            LeaveCriticalSection(&g_nodeCritSection);
            // Now remove dest slot from free bitmap
            groupIndex = destSlot >> 5;
            EnterCriticalSection(&g_nodeCritSection);
            bit = __allshl(1, destSlot & 0x1F);
            g_freeBitmapLow[groupIndex] &= ~(unsigned int)bit;
            g_freeBitmapHigh[groupIndex] &= ~(unsigned int)(bit >> 32);
            if ((groupIndex == g_nextFreeSlotGroup) &&
                (g_freeBitmapLow[groupIndex] == 0) &&
                (g_freeBitmapHigh[groupIndex] == 0)) {
                g_nextFreeSlotGroup++;
            }
            // Mark dest entry as freed (state 5)
            if (destEntry != NULL) {
                *destEntry = 0x05;
            }
            LeaveCriticalSection(&g_nodeCritSection);
        }

        // Allocate a new node from the free list
        newNode = (undefined4*)allocateNodeFromFreeList();
        if (newNode == NULL) {
            return NULL;
        }
        // Initialize the node
        nodeListAdd(&someNodeList, /* unknown param */);
        newNode[4] = sourceSlot;   // +0x10: source index
        newNode[3] = destSlot;     // +0x0C: dest index
        newNode[5] = data;         // +0x14: attached data
        newNode[1] = 0;            // +0x04: flags? 0
        *newNode = 2;              // +0x00: node type = 2 (packet?)

        // Profiling / performance counter update
        if (g_perfCounterActive == 0) {
            QueryPerformanceCounter(&perfCount);
            g_perfTimestamp.LowPart = perfCount.LowPart;
            g_perfTimestamp.HighPart = perfCount.HighPart;
        }
        g_perfCounterActive++;
        profilingStart();
        profilingUpdate(1);
        profilingFlush();

        return newNode;
    }
    return NULL;
}