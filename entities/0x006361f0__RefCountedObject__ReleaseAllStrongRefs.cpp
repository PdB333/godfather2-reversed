// FUNC_NAME: RefCountedObject::ReleaseAllStrongRefs
int __fastcall RefCountedObject::ReleaseAllStrongRefs(RefCountedObject* thisPtr)
{
    // +0x1C: m_strongRefCount
    int initialStrongRefCount = *(int*)((int)thisPtr + 0x1C);

    // Global reference decrement (-1 means release global pool)
    FUN_00635d00(0xFFFFFFFF); // releaseGlobalRef(-1)

    // +0x14: m_pRefBlock (pointer to reference control block)
    // +0x08 in that block: flags (bit0 = "has weak references" flag)
    uint8_t* refBlock = *(uint8_t**)((int)thisPtr + 0x14);
    if ((refBlock[8] & 1) == 0) // no weak references
    {
        // +0x14 in refBlock: m_slotRefCount (number of slot references)
        int* slotRefCount = (int*)(refBlock + 0x14);
        while (*slotRefCount != 0)
        {
            (*slotRefCount)--;
            FUN_00635d00(0xFFFFFFFF); // releaseSlotRef(-1)
        }
        // Decrement once more to indicate all slots released
        (*slotRefCount)--;
    }

    // The return is obscure; original code likely returned the new ref count.
    // The decompiler's in_EAX suggests the result of the last decrement
    // is combined with m_strongRefCount. We'll approximate as the updated m_strongRefCount.
    return *(int*)((int)thisPtr + 0x1C); // m_strongRefCount
}