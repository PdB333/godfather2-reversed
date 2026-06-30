// FUNC_NAME: ResourceManager::releaseAll
// Function at 0x004c9a70: Cleanup method that releases two owned sub-objects and performs final shutdown.
// Structure offsets (from this):
//   +0x04: vtable pointer for base class providing sub-object1 management
//   +0x14: vtable pointer for base class providing sub-object2 management
//   +0x18: pointer to second managed sub-object (checked if non-zero before release)
//   +0x1c: pointer to first managed sub-object (always released)
//   +0x20: set to zero after first release (maybe part of first sub-object's state)

void ResourceManager::releaseAll(void)
{
    // Stack buffer used by the custom deallocation routine (size 12)
    byte deallocBuffer[12];

    // --- Release first sub-object (subObject1) ---
    // Call custom deallocator with:
    //   buffer, this, vtable-of-subObject1, this-again, subObject1-pointer
    customDeallocator(deallocBuffer, this, *(void**)*reinterpret_cast<void**>(this + 0x1c), this,
                      *reinterpret_cast<void**>(this + 0x1c));

    // Call virtual method (index 1) from base class vtable at +0x04
    // Passes subObject1 and a size/identifier 0x18
    (*(void (**)(void*, int))(*reinterpret_cast<int**>(this + 4) + 1))( *(void**)(this + 0x1c), 0x18 );

    // Clear subObject1 pointer and adjacent field
    *reinterpret_cast<int*>(this + 0x1c) = 0;
    *reinterpret_cast<int*>(this + 0x20) = 0;

    // --- Release second sub-object (subObject2) if present ---
    if (*reinterpret_cast<int*>(this + 0x18) != 0)
    {
        // Call virtual method (index 1) from base class vtable at +0x14
        // Passes subObject2 and argument 0
        (*(void (**)(void*, int))(*reinterpret_cast<int**>(this + 0x14) + 1))( *(void*)(this + 0x18), 0 );

        *reinterpret_cast<int*>(this + 0x18) = 0;
    }

    // Call virtual method (index 3, offset 0xc) from the same base class vtable at +0x14
    (*(void (**)())(*reinterpret_cast<int**>(this + 0x14) + 3))();

    // Perform global cleanup
    globalShutdown();
    return;
}