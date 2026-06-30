// FUNC_NAME: MemoryPool::validateNode
int __thiscall MemoryPool::validateNode(uint nodePtr)
{
    uint* headerValue;
    LPCRITICAL_SECTION criticalSection;
    uint alignedSize;
    uint unknownFlag;
    uint nextPtr;
    uint prevPtr;
    int errorCount;
    int integrityCheck;
    bool isNotHead;
    
    // Get the critical section for thread safety
    criticalSection = *(LPCRITICAL_SECTION*)(this + 0x4e8);
    if (criticalSection != (LPCRITICAL_SECTION)0x0) {
        EnterCriticalSection(criticalSection);
        // Increment a debug counter (stored in a secondary critical section's DebugInfo field)
        criticalSection[1].DebugInfo =
             (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }
    
    // Extract the aligned size/next pointer from the node header (offset +4)
    alignedSize = *(uint*)(nodePtr + 4) & 0x7ffffff8;
    headerValue = (uint*)(alignedSize + nodePtr);
    
    // Start with a base error count from a helper function
    errorCount = FUN_00644d30(nodePtr);
    
    // Add checks based on flags in the header
    errorCount = errorCount + 
                 (*(byte*)((*(uint*)(nodePtr + 4) & 0x7ffffff8) + 4 + nodePtr) & 1) +  // bit0 at headerValue[4] (byte)
                 (*(uint*)(nodePtr + 4) >> 1 & 1);  // bit1 of the header word
    
    if (alignedSize < 0x10) {
        // For small sizes (< 16), check if size > 4
        isNotHead = (4 < alignedSize);
    }
    else {
        // Check if this node is the list head or has a special flag set
        if ((nodePtr == *(uint*)(this + 0x440)) ||
            ((*(byte*)((headerValue[1] & 0x7ffffff8) + 4 + (int)headerValue) & 1) != 0)) {
            integrityCheck = 0;
        }
        else {
            integrityCheck = 1;
        }
        
        // Retrieve next and previous pointers (offsets +8 and +0xc)
        nextPtr = *(uint*)(nodePtr + 8);
        prevPtr = *(uint*)(nodePtr + 0xc);
        
        // Accumulate integrity violations
        errorCount = errorCount + 
            (uint)((nodePtr & 7) != 0) +                                    // alignment check (must be 8-byte aligned)
            (uint)(*headerValue != alignedSize) +                            // header value must match aligned size
            ((byte)~*(byte*)(nodePtr + 4) & 1) +                             // byte at nodePtr+4 should not be zero?
            integrityCheck +                                                  // if not head and no special flag
            (uint)(*(uint*)(prevPtr + 8) != nodePtr) +                       // prev node's next must point back to this
            (uint)(*(uint*)(nextPtr + 0xc) != nodePtr);                      // next node's prev must point back to this
        
        // If this node is not self-pointing (i.e., it has different neighbors)
        if ((nodePtr != prevPtr) && (nodePtr != nextPtr)) {
            goto SkipAdditionalCheck;
        }
        
        // If both prev and next are the same (single node?), check if they are equal
        errorCount = errorCount + (uint)(nextPtr != prevPtr);
        
        // Check if this node is not the head
        isNotHead = (nodePtr != *(uint*)(this + 0x440));
    }
    
    // Final addition for the head check
    errorCount = errorCount + (uint)isNotHead;
    
SkipAdditionalCheck:
    if (criticalSection != (LPCRITICAL_SECTION)0x0) {
        // Decrement the debug counter before leaving critical section
        criticalSection[1].DebugInfo =
             (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(criticalSection);
    }
    
    return errorCount;
}