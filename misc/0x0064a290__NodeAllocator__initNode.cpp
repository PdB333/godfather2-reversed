// FUNC_NAME: NodeAllocator::initNode
void __thiscall NodeAllocator::initNode(int thisPtr, int nodePtr, int value)
{
    LPCRITICAL_SECTION criticalSection = *(LPCRITICAL_SECTION *)(thisPtr + 0x1b8);
    if (criticalSection != (LPCRITICAL_SECTION)0x0) {
        EnterCriticalSection(criticalSection);
        // The following line is likely a custom spinlock or debug counter
        // It increments Type field of a structure following the critical section
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo->Type + 1);
    }
    // Initialize node structure (36 bytes total)
    *(int *)nodePtr = value;                    // +0x00: node payload
    *(int *)(nodePtr + 4) = *(int *)(thisPtr + 0x1c); // +0x04: next pointer (from object field)
    *(int *)(nodePtr + 8) = 0;                 // +0x08: reserved
    *(long long *)(nodePtr + 12) = 0;          // +0x0C: two integer fields cleared
    *(long long *)(nodePtr + 20) = 0;          // +0x14: two integer fields cleared
    *(long long *)(nodePtr + 28) = 0;          // +0x1C: two integer fields cleared
}