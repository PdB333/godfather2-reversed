// FUNC_NAME: EARSConnection::processCommandList
// Address: 0x004b4e70
// Role: Parses a linked list of command nodes (tag/value/next) to build arguments for a critical-section-guarded submission to some subsystem (likely networking/queue management). 
//   - Tag 2: Sets a speed/rate value (local_4)
//   - Tag 3: Adjusts param_2 (timestamp/offset) and uVar4 (size/duration) according to alignment logic
//   - Then acquires a critical section from an internal manager, calls FUN_00647070 (submitCommand), and releases the lock.

#include <windows.h> // for CRITICAL_SECTION etc.

typedef int* CommandNode; // each node: [tag, value, next]

int __thiscall EARSConnection::processCommandList(/* this */ int thisPtr, uint timestampOrSeq, CommandNode nodeList)
{
    int tag;
    LPCRITICAL_SECTION criticalSection;
    uint alignmentDiff;
    uint local_4 = 0x10;                   // default speed/rate? (e.g., packet window size)
    uint sizeOrDuration = 0;               // uVar4

    if (nodeList != nullptr)
    {
        do {
            tag = *nodeList;
            if (tag == 0) break;               // end-of-list marker
            if (tag == 2)
            {
                local_4 = nodeList[1];          // set the speed/rate value (e.g., number of packets)
            }
            else if (tag == 3)
            {
                sizeOrDuration = nodeList[1];   // e.g., packet size or time delta
                // alignment to 8-byte boundary? Compute padding needed.
                // Extract lower 3 bits + sign bit, treat as signed mod 8.
                alignmentDiff = sizeOrDuration & 0x80000007;
                if ((int)alignmentDiff < 0)
                {
                    // If negative (sign bit), adjust to positive modulo 8
                    alignmentDiff = (alignmentDiff - 1 | 0xfffffff8) + 1;
                }
                if (alignmentDiff != 0)
                {
                    timestampOrSeq += alignmentDiff;          // advance timestamp by padding
                    sizeOrDuration += (8 - alignmentDiff);    // round up size to next multiple of 8
                }
            }
            nodeList = (CommandNode)nodeList[2]; // follow next pointer
        } while (nodeList != nullptr);
    }

    // Fetch current sequence from this->+0x14
    uint currentSeq = *(uint *)(thisPtr + 0x14);
    // Get pointer to manager object from this->+0x40
    int managerPtr = *(int *)(thisPtr + 0x40);
    // Manager+0x4E8 holds a pointer to a critical section
    criticalSection = *(LPCRITICAL_SECTION *)(managerPtr + 0x4E8);

    if (criticalSection != nullptr)
    {
        // Acquire lock (with custom increment? DebugInfo manipulation is suspicious – perhaps a custom spinlock variant)
        EnterCriticalSection(criticalSection);
        // The next two lines adjust the critical section's internal debug info as a simple spinlock increment.
        // This is not standard usage; likely a custom lock model (e.g., counting semaphore).
        criticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }

    // Call internal function with:
    //   manager pointer, local_4 (rate), sizeOrDuration, and flag (timestampOrSeq <= currentSeq)
    // The flag indicates if the new timestamp is older or the same as current.
    uint result = FUN_00647070(managerPtr, local_4, sizeOrDuration, (uint)(timestampOrSeq <= currentSeq));

    if (criticalSection != nullptr)
    {
        // Unlock (reverse of the above increment)
        criticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(criticalSection);
    }

    return result;
}