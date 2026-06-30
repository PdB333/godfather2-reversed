// FUNC_NAME: NetObject::allocateReplicationBuffer
void __thiscall NetObject::allocateReplicationBuffer(int thisObj, int sourceObj)
{
    int allocPtr;
    int *newBuffer;

    // Free existing buffer if present
    if (*(int *)(thisObj + 0x98) != 0) {
        FUN_009c8eb0(*(int *)(thisObj + 0x98));   // Likely operator delete or free
        *(int *)(thisObj + 0x98) = 0;
    }

    // Allocate new buffer of size 0x24 (36 bytes)
    newBuffer = (int *)FUN_009c8e50(0x24);   // Likely operator new or malloc
    if (newBuffer == (int *)0x0) {           // Allocation failed – keep null
        newBuffer = (int *)0x0;
    } else {
        // Initialize first 7 dwords to 0
        newBuffer[0] = 0;
        newBuffer[1] = 0;
        newBuffer[2] = 0;
        newBuffer[3] = 0;
        newBuffer[4] = 0;
        newBuffer[5] = 0;
        // Set last two dwords to sentinel 0xFFFFFFFF
        newBuffer[6] = 0xFFFFFFFF;           // offset 0x1c (28)
        newBuffer[7] = 0xFFFFFFFF;           // offset 0x20 (32)
    }

    // Store buffer pointer at this+0x98
    *(int **)(thisObj + 0x98) = newBuffer;

    // Copy network update data from source object
    // sourceObj+100 and sourceObj+200 are likely update flags or masks
    newBuffer[6] = *(int *)(sourceObj + 100);         // offset 0x1c
    *(int *)((*(int *)(thisObj + 0x98)) + 0x20) = *(int *)(sourceObj + 200); // offset 0x20

    // If source object has a ghost info pointer (offset +0xd4), copy more state
    int ghostInfo = *(int *)(sourceObj + 0xd4);
    if (ghostInfo != 0) {
        // Copy fields from the ghost info object
        *(int *)(*(int *)(thisObj + 0x98) + 0x00) = *(int *)(ghostInfo + 0x26c);
        *(int *)(*(int *)(thisObj + 0x98) + 0x04) = *(int *)(ghostInfo + 0x274);
        *(int *)(*(int *)(thisObj + 0x98) + 0x08) = *(int *)(ghostInfo + 0x1dc);
        *(int *)(*(int *)(thisObj + 0x98) + 0x10) = *(int *)(ghostInfo + 0x1d8);
        *(int *)(*(int *)(thisObj + 0x98) + 0x0c) = *(int *)(ghostInfo + 0x29c);
    }

    return;
}