// FUNC_NAME: PoolAllocator::insertAt
// Function at 0x004f1690: Allocates an 8-byte slot in a fixed-size pool, inserting at a given index (or appending if index equals current count). Shifts existing elements to make room.
// Global state:
//   DAT_01218f28 - pool base address (pointer to 8-byte element array)
//   DAT_01218f2c - current number of used slots (count)
//   DAT_01218f30 - maximum capacity (max count)
//   unaff_ESI (implicit register parameter) - desired insertion index

int __declspec(naked) PoolAllocator::insertAt()
{
    __asm
    {
        // The original code uses ESI as the index parameter (unaff_ESI).
        // We simulate by pushing ESI and returning in EAX.
        // This is a simplified C++ representation.
    }
    int* base = DAT_01218f28;   // +0x00: pool base
    int* count = &DAT_01218f2c; // +0x04: current count
    int* maxCount = &DAT_01218f30; // +0x08: capacity

    if (*count == *maxCount)
    {
        // Pool full, attempt to expand (calls another function)
        PoolAllocator::expand(); // FUN_004f1460
    }

    int index; // unaff_ESI - passed in ESI, assumed to be the requested slot index
    // Since ESI is not a parameter in the declared signature, we treat it as implicit.
    // For clarity, we write as if index is a function argument.

    // If index equals current count, just append
    if (index == *count)
    {
        int slotOffset = (*count) * 8;
        (*count)++;
        return (int)(base + slotOffset);
    }

    // Insert at index: shift elements from the end up to index+1
    // Copy last element one position forward (to current count)
    int* puVar2 = (int*)( (char*)base + (*count) * 8 );
    puVar2[0] = puVar2[-2]; // copy first dword of previous element
    puVar2[1] = puVar2[-1]; // copy second dword of previous element

    int uVar3 = *count;
    while (--uVar3 > index)
    {
        int* pSlot = (int*)( (char*)base + uVar3 * 8 );
        pSlot[0] = pSlot[-2];
        pSlot[1] = pSlot[-1];
    }

    (*count)++;
    // Return pointer to the empty slot at index (caller is expected to fill it)
    return (int)(base + index * 8);
}