// FUN_NAME: EntityManager::processActiveEntities
void EntityManager::processActiveEntities()
{
    unsigned int count = *(unsigned int *)(this + 0x360);  // +0x360: number of active entity slots
    int *slotPtr = (int *)(this + 8);                      // +8: start of active entity slot array (each slot 108 bytes)
    unsigned int i = 0;

    if (count != 0)
    {
        do
        {
            // Check if the slot is valid: has a non-null pointer at offset 0, 
            // a non-null component at offset +16, and an active flag at offset +0x64
            if (slotPtr[0x17] != 0   &&   // +0x64 (0x17*4): active flag or state
                *slotPtr != 0        &&   // +0: pointer to entity or core object
                slotPtr[4] != 0)          // +16 (4*4): pointer to component/behavior
            {
                // Process this slot; note that the function is called with 'this' pointer
                // (slotPtr-2 resolves to 'this' as the array starts at this+8)
                FUN_006aac00(this);
            }

            i++;
            slotPtr += 0x1b;  // advance to next slot (0x1b integers = 108 bytes)
        } while (i < count);
    }
}