// FUNC_NAME: NetSession::findPacketInWindowOrStatus
// Address: 0x00645230
// This function appears to check if a given parent object (param_1) is associated with any node in an embedded linked list.
// It uses a critical section at offset 0x4e8 for thread safety, calls FUN_00644d30 (likely getSequenceStatus) and returns a combination of findings.
// The list nodes are intrusive: each node contains an offset (first int) that gives the parent object address when subtracted from the node address.

int __thiscall NetSession::findPacketInWindowOrStatus(void* thisPtr, void* parentObject)
{
    LPCRITICAL_SECTION criticalSection;       // derived from this->csListLock (offset 0x4e8)
    uint flags;                               // from parentObject+4
    int resultFromCallee;                     // from FUN_00644d30(parentObject)
    ListEntry* nodeIter;                      // iterator over linked list

    // Acquire lock if present
    criticalSection = *(LPCRITICAL_SECTION*)((int)thisPtr + 0x4e8);
    if (criticalSection != NULL)
    {
        EnterCriticalSection(criticalSection);
        // Debug hack: increment DebugInfo pointer by 1 to disable debug output while inside critical section?
        criticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }

    // Call helper function (likely returns some status based on parentObject)
    resultFromCallee = FUN_00644d30((int)parentObject);

    // Read flags at offset +4 of parentObject
    flags = *(uint*)((int)parentObject + 4);

    // Search linked list rooted at this+0x49c (list head) and first element pointer at this+0x4a8
    // Node structure: [offset (int)] [ ... ] [next (int* at offset 0xC)]
    // The loop condition: node address minus node->offset == parentObject
    for (nodeIter = *(ListEntry**)((int)thisPtr + 0x4a8);
         (nodeIter != (ListEntry*)((int)thisPtr + 0x49c) &&
          ((int)nodeIter - nodeIter->offset) != (int)parentObject);
         nodeIter = nodeIter->next)
    {
        // iterate
    }

    // Release lock if present (reverse debug hack)
    if (criticalSection != NULL)
    {
        criticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(criticalSection);
    }

    // Return: 1 if found in list + resultFromCallee + inverse of bit 1 of flags
    return ((nodeIter == (ListEntry*)((int)thisPtr + 0x49c)) ? 0 : 1) +
           resultFromCallee +
           (((byte)~(byte)(flags >> 1) & 1));
}

// Helper structure for list entry (assumed)
typedef struct ListEntry {
    int offset;           // +0x00: offset from parent object to this node (if parent = node - offset)
    // ... other fields ...
    ListEntry* next;      // +0x0C: next node pointer
} ListEntry;