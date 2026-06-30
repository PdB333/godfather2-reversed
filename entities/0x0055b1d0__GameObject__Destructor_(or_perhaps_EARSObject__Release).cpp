// FUNC_NAME: GameObject::Destructor (or perhaps EARSObject::Release)
// Function address: 0x0055b1d0
// This is a destructor/cleanup function for a reference-counted game object.
// It sets vtable pointers, releases internal references, decrements refcount,
// and if refcount reaches zero, finalizes the object via a global command buffer.

struct GameObject {
    void** vtable; // +0x00
    // ... many fields, only offsets are documented below
    int refCount; // +0x164 (offset 0x59 from this)
    // +0x218 at offset 0x86: flag for array cleanup
    // +0x480 at offset 0x120: flag for enabling array cleanup
    // +0x3a0 at offset 0xe8: timer structure (shorts at +1 and +6, callback pointer)
    // +0x1d1..0x1e0 (every 5 words): pointer array of 4 refcounted objects
    // +0x1e6..0x1d2 (descending, pairs): additional pointer cleanup region
    // +0x710..0x71c (offsets 0x1c4-0x1c7): four integer IDs for destruction queue
    // +0xf0..0x114 (4 blocks of 0xc): arrays released by FUN_00572c50
};

void __fastcall GameObject::destructor(GameObject* this)
{
    void** vtableArray;
    int* refObj;
    int* nextRef;
    int i;
    int result;
    short* timerStruct;
    int* cleanupPtr;
    uint* globalStackPtr; // from DAT_01206880 + 0x14
    int arrIndex;

    // Set up vtable and other base pointers (constructor-like action during destruction)
    this->vtable = (void**)0x00e3a080; // PTR_FUN_00e3a080
    this[0x0f] = (undefined4*)0x00e3a2e0;
    this[0x12] = (undefined4*)0x00e3a2f0;
    this[0x14] = (undefined4*)0x00e3a2f4;
    *(this + 0x15) = (undefined4*)0x00e3a2f8;
    this[0x16] = (undefined4*)0x00e3a358;
    this[0xb8] = (undefined4*)0x00e3a3bc;
    this[0xb9] = (undefined4*)0x00e3a3d0;

    // Release four reference-counted objects stored at offsets 0x1d1, 0x1d6, 0x1db, 0x1e0
    refObj = &this->refCountArray; // +0x1d1
    for (i = 0; i < 4; i++)
    {
        FUN_0055af20(); // pre-release helper (may be a check or log)
        if (*refObj != 0)
        {
            // Decrement reference count (stored at offset +4 of the object)
            int* object = (int*)*refObj;
            int* cnt = object + 1;
            *cnt = *cnt - 1;
            if (*cnt == 0)
            {
                // Call destructor from vtable
                (**(code**)(*object + 4))();
            }
            *refObj = 0;
        }
        refObj += 5; // stride of 5 words (20 bytes)
    }

    // Handle timer callback structure at +0xe8
    timerStruct = (short*)this[0xe8];
    if (timerStruct != 0 && timerStruct[1] != 0)
    {
        timerStruct[3]--; // decrement timer count (short at +6)
        if (timerStruct[3] == 0)
        {
            // Invoke callback function at start of structure with parameter 1
            (**(code**)timerStruct)(1);
        }
    }

    // If flag at +0x120 is set, clean up four arrays at +0xf0, +0xfc, +0x108, +0x114
    if (this[0x120] != 0)
    {
        cleanupPtr = &this[0xf0]; // start of array block
        for (i = 0; i < 4; i++)
        {
            if (this[0x86] != 0)
            {
                FUN_00572c50(cleanupPtr);
            }
            cleanupPtr += 0xc / 4; // each block is 0xc bytes (3 words)
        }
    }

    // If reference count at +0x164 is non-zero, push items onto global destruction command queue
    if (this[0x59] != 0)
    {
        globalStackPtr = *(uint**)(DAT_01206880 + 0x14);
        // Process four ID values at +0x1c4, +0x1c5, +0x1c6, +0x1c7
        for (int idIdx = 0; idIdx < 4; idIdx++)
        {
            int idVal = this[0x1c4 + idIdx]; // offset 0x1c4 + idIdx
            if (idVal != 0)
            {
                // Push command to queue
                globalStackPtr = *(uint**)(DAT_01206880 + 0x14);
                **(uint**)globalStackPtr = (uint)&PTR_LAB_01124668; // command marker
                *globalStackPtr = *globalStackPtr + 4;
                *(int*)*globalStackPtr = idVal;
                *globalStackPtr = *globalStackPtr + 4;
                *(uint*)*globalStackPtr = (uint)(this + 0x15); // pointer to +0x15 field
                *globalStackPtr = *globalStackPtr + 4;

                // Decrement reference count; if zero, push final cleanup command
                if (this[0x59] != 0)
                {
                    this[0x59]--;
                    if (this[0x59] == 0)
                    {
                        globalStackPtr = *(uint**)(DAT_01206880 + 0x14);
                        **(uint**)globalStackPtr = (uint)&PTR_LAB_0110ba58; // finalize marker
                        *globalStackPtr = *globalStackPtr + 4;
                        // Conditionally push pointer (non-zero if this != 0)
                        *(uint*)*globalStackPtr = (this != 0) ? (uint)(this + 0x15) : 0;
                        *globalStackPtr = *globalStackPtr + 4;
                    }
                }
            }
        }
    }

    // Additional pointer cleanup: three iterations over a region of offsets 0x1e2/0x1e1, 0x1dd/0x1dc, etc.
    nextRef = &this[0x1e6]; // start high
    for (i = 0; i < 4; i++)
    {
        int* pairStart = nextRef - 5; // offsets 0x1e1, 0x1dc, 0x1d7, 0x1d2
        if (nextRef[-4] != 0) // offset 0x1e2, then 0x1dd, etc.
        {
            *(int*)(nextRef[-4] + 8) = 0; // clear pointer at +8 of the object
            nextRef[-4] = 0;
        }
        if (*pairStart != 0)
        {
            *(int*)(*pairStart + 8) = 0;
            *pairStart = 0;
        }
        nextRef = pairStart;
    }

    // Call a helper 4 times (probably for additional cleanup)
    for (i = 0; i < 4; i++)
    {
        FUN_004bfcf0();
    }

    // Final cleanup function
    FUN_00544450();

    return;
}