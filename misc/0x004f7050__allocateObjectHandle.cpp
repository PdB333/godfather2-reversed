// FUNC_NAME: allocateObjectHandle
void allocateObjectHandle(int *outHandle)
{
    LPCRITICAL_SECTION criticalSection;
    int baseAddr;
    int newBlock;
    int addr;
    int index;
    int something;

    baseAddr = DAT_0120541c;  // global base pointer for object manager
    criticalSection = *(LPCRITICAL_SECTION *)(baseAddr + 0x1b8);  // critical section member at +0x1b8

    if (criticalSection != (LPCRITICAL_SECTION)0x0) {
        EnterCriticalSection(criticalSection);
    }

    newBlock = allocateMemory(baseAddr, 0x18);  // allocate 0x18-byte block (likely a node)
    if (newBlock == 0) {
        // allocation failed, fallback: get alternative address from offset 0x17c
        if (criticalSection != (LPCRITICAL_SECTION)0x0) {
            LeaveCriticalSection(criticalSection);
        }
        addr = *(int *)(baseAddr + 0x17c);
    }
    else {
        initializeBlock();  // likely initializes the block
        addr = *(int *)(newBlock + 8);  // get some pointer from inside the block
        if (criticalSection != (LPCRITICAL_SECTION)0x0) {
            LeaveCriticalSection(criticalSection);
        }
    }

    if (addr != 0) {
        index = addr - DAT_01205410;  // compute index relative to a base array
        something = *(int *)(**(int **)(__readfsdword(0x2c)) + 8) + index;  // Thread-local storage? Access current thread's data
        if (something != 0) {
            *(int *)(something + 0x10) = 0;  // clear two fields
            *(int *)(something + 0x14) = 0;
        }
    }

    outHandle[0] = index;  // return the computed index
    outHandle[1] = 1;      // set a flag indicating valid handle
    return;
}