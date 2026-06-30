// FUNC_NAME: ResourceHandle::initialize
// Address: 0x00556ab0
// Role: Initializes a resource handle with smart pointer management and unique ID assignment.
// Parameters:
//   thisPtr (ESI) - Pointer to the ResourceHandle object (this)
//   isNew (param_1) - Non-zero if constructor is creating a new object, zero if reusing existing
//   extraData (param_2) - Additional data passed to the sub-object initialization
//   hasSubObject (param_3) - Non-zero if a sub-object (like a material or texture) is present
//   typeIndex (param_4) - Resource type index (0-31)
//   resourceID (param_5) - Unique resource identifier
// Fields:
// +0x00: word0 (unknown)
// +0x10: smart pointer (offset 0x40) - ref-counted object
// +0x11: someFlag (offset 0x44)
// +0x13: uniqueHandle (offset 0x4C) - 64-bit handle built from typeIndex and globalID
// +0x15: resourceID (offset 0x54) - 64-bit (stored in two words)
// +0x17: someCounter (offset 0x5C) - set to 0

void ResourceHandle::initialize(int isNew, uint32 extraData, int hasSubObject, uint32 typeIndex, uint32 resourceID)
{
    // Smart pointer management at this+0x10 (offset 0x40)
    void** oldPtr = (void**)thisPtr[0x10];  // +0x40
    void** newPtr = (void**)unaff_EDI;     // new smart pointer target (passed via register)

    if (oldPtr != newPtr) {
        if (oldPtr != nullptr) {
            // Decrement reference count at oldPtr+2 (short at +6)
            short* refCount = (short*)((uint8*)oldPtr + 6);
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                // Call virtual destructor/release via vtable
                (**(void (__thiscall**)(void*, int))(*oldPtr))(oldPtr, 1);
            }
        }

        thisPtr[0x10] = newPtr;

        if (newPtr != nullptr) {
            // Increment reference count
            short* newRefCount = (short*)((uint8*)newPtr + 6);
            *newRefCount = *newRefCount + 1;
        }
    }

    // Set some flag at +0x44
    thisPtr[0x11] = hasSubObject;

    if (isNew == 0) {
        // New object: initialize multiple fields with global sentinel
        FUN_0045cbe0();  // Likely memory initializer
        uint32 sentinel = DAT_00e2b1a4;  // Global constant (maybe 0 or -1)
        thisPtr[0x00] = sentinel;        // +0x00
        thisPtr[0x05] = sentinel;        // +0x14
        thisPtr[0x0A] = sentinel;        // +0x28
        thisPtr[0x0F] = 0;               // +0x3C
        thisPtr[0x0E] = 0;               // +0x38
        thisPtr[0x0D] = 0;               // +0x34
        thisPtr[0x0C] = 0;               // +0x30
    } else {
        // Reusing existing: initialize sub-object entity
        FUN_005420c0(isNew + 0xe0);       // Initializes some component at isNew+0xe0
        if (hasSubObject != 0) {
            FUN_00556fd0(isNew);          // Setup sub-object specific data
            FUN_00556f70(thisPtr, extraData); // Link extra data to this handle
        }
    }

    // Build unique handle
    uint32 part1;
    if (hasSubObject != 0) {
        part1 = FUN_0043b490();  // Some random or sequential ID generator
    } else {
        part1 = 0;
    }

    // Read global array for upper 32 bits of handle
    uint32 globalID = *(uint32*)(*(uint32*)DAT_01223480 + 0x54 + typeIndex * 4);
    // Lower 32 bits: (part1 & 0xFFF) << 16 | (typeIndex & 0x1F)
    uint32 lower = ((part1 & 0xFFF) << 0x10) | (typeIndex & 0x1F);
    lower |= 0x3E0;  // Set some flags

    // Combine into 64-bit handle
    uint64 handle = ((uint64)globalID << 32) | lower;
    *(uint64*)(&thisPtr[0x13]) = handle;  // +0x4C

    // Store resourceID at +0x54
    *(uint64*)(&thisPtr[0x15]) = resourceID;

    // Clear counter at +0x5C
    thisPtr[0x17] = 0;
}