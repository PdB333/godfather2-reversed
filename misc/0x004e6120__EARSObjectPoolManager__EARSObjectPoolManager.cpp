// FUNC_NAME: EARSObjectPoolManager::EARSObjectPoolManager
// Reconstructed constructor for an EA EARS object pool manager.
// Function address: 0x004e6120
// The function initializes the object, constructs 5 sub-components,
// then conditionally inserts a resource pointer into a global linked list.

void __fastcall EARSObjectPoolManager::EARSObjectPoolManager(EARSObjectPoolManager* this)
{
    // Set base vtable (first inheritance level) at +0x00
    this->vtableBase = (void*)&PTR_FUN_00e371e8;

    // Construct 5 sub-objects (e.g., child pools, slots, or manager sub-units)
    for (int i = 0; i < 5; i++)
    {
        FUN_004ebba0(); // Sub-object initialization (likely creates a new instance or resets a slot)
    }

    // Switch vtable to derived class (secondary vtable for this object)
    // Overwrites the original vtable pointer at +0x00
    this->vtableDerived = (void*)&PTR_FUN_00e37110;

    // Check if a resource pointer at offset +0x10 is non-zero
    if (this->resourcePtr != 0)
    {
        // Access global pool insertion cursor stored at DAT_01206880 + 0x14
        int** insertCursor = (int**)(DAT_01206880 + 0x14);

        // Write a sentinel address into the slot pointed to by the cursor
        *((void***)(*insertCursor)) = (void**)&PTR_LAB_01123be8;

        // Advance the cursor by one pointer (4 bytes)
        *insertCursor = *insertCursor + 1;

        // Store the resource pointer into the next slot
        *((int*)(*insertCursor)) = this->resourcePtr;

        // Advance the cursor again
        *insertCursor = *insertCursor + 1;

        // Clear the resource pointer fields in this object (+0x10 and +0x14)
        this->resourcePtr  = 0;
        this->field_0x14   = 0;
    }
}
```