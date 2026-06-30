// FUNC_NAME: PacketSlotBuffer::initialize
void __thiscall PacketSlotBuffer::initialize(int *this, uint slotCount, int someParam)
{
    longlong lVar1;
    int allocatedStruct;
    undefined4 firstArrayPtr;
    uint i;

    this[3] = someParam;    // +0x0C
    this[1] = 0;            // +0x04
    this[2] = slotCount;    // +0x08
    this[4] = 0;            // +0x10

    // Allocate a structure of size 0x38 (56 bytes) – likely a sub-object for tracking slots
    allocatedStruct = FUN_009c8e50(0x38);
    if (allocatedStruct == 0) {
        allocatedStruct = 0;
    }
    else {
        FUN_00498f80();     // initialize the sub-object (e.g., vtable setup)
        // Allocate array of (slotCount+1) ints for the first table
        lVar1 = (ulonglong)(slotCount + 1) * 4;
        firstArrayPtr = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
        *(undefined4 *)(allocatedStruct + 0x30) = firstArrayPtr; // +0x30 in sub-object
    }
    *this = allocatedStruct;                    // +0x00 – pointer to sub-object

    // Zero-initialize the first array (first table of slot tracking)
    i = 0;
    do {
        *(undefined4 *)(*(int *)(*this + 0x30) + i * 4) = 0;
        i = i + 1;
    } while (i <= slotCount);

    // Allocate a second array of same size (slotCount+1 ints)
    lVar1 = (ulonglong)(slotCount + 1) * 4;
    this[5] = FUN_009c8e80(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1); // +0x14 – second table
    return;
}