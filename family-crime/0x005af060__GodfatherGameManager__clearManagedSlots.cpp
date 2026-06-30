// FUNC_NAME: GodfatherGameManager::clearManagedSlots
// Address: 0x005af060
// Role: Clears a fixed array of 4 managed object pointers at offset +0x820.
// For each non-null pointer, calls a destructor function via a global type-dispatch table (DAT_0103aee0)
// indexed by the first dword (type ID) masked to 0x7fff. Then resets the slot to a sentinel (DAT_0119cbbc).

void __thiscall GodfatherGameManager::clearManagedSlots(void)
{
    // +0x820: pointer to an array of 4 managed object pointers
    int *slotArray = reinterpret_cast<int *>(reinterpret_cast<uintptr_t>(this) + 0x820);
    
    // Iterate over 4 slots
    for (int i = 0; i < 4; i++)
    {
        // Current object pointer is stored as an int (but points to a uint*)
        uint *objPtr = reinterpret_cast<uint *>(slotArray[i]);
        
        if (objPtr != nullptr)
        {
            // Extract type ID from the object's first dword & 0x7fff
            uint typeId = *objPtr & 0x7fff;
            
            // Global table of destructor functions at DAT_0103aee0 (assumed array of function pointers)
            // Each entry is 4 bytes (function pointer), indexed by typeId.
            typedef void (*DestructorFunc)(uint *);
            DestructorFunc destructor = reinterpret_cast<DestructorFunc>(&DAT_0103aee0 + typeId * 4);
            
            // Call the destructor on the object
            destructor(objPtr);
        }
        
        // Reset the slot to the global sentinel value (DAT_0119cbbc, likely nullptr or a special marker)
        slotArray[i] = DAT_0119cbbc;
    }
}