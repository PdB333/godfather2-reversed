// FUNC_NAME: PlayerController::initialize
void __fastcall PlayerController::initialize(int *this)
{
    int *nodePtr;
    int *listHead;
    int *parent;
    int currentOffset;

    // Allocation tracker call (0x30 bytes)
    FUN_007f63e0(0x30);

    // Clear lower 3 bits of flags
    this[0x27] &= 0xfffffff8;  // flags at +0x9C

    // Get global controller manager base
    if (*(int **)(DAT_012233a0 + 4) == 0) {
        parent = 0;
    } else {
        // Offset to parent controller (subtract 0x1f30)
        parent = *(int **)(DAT_012233a0 + 4) - 0x1f30;
    }

    // Node1 at +0xB0
    nodePtr = this + 0x2c;
    if (parent == 0) {
        currentOffset = 0;
    } else {
        currentOffset = parent + 0x48; // offset to node in manager
    }

    if (*nodePtr != currentOffset) {
        if (*nodePtr != 0) {
            FUN_004daf90(nodePtr); // remove from old list
        }
        *nodePtr = currentOffset;
        if (currentOffset != 0) {
            this[0x2d] = *(int *)(currentOffset + 4); // store previous pointer
            *(int **)(currentOffset + 4) = nodePtr;     // link back
        }
    }

    // Call vtable function at offset 0x290 on object at +0xA0
    (*(void (**)(int, int))(*(int *)this[0x28] + 0x290))(0, 8);

    // Check if force feedback should be enabled
    if (parent != 0 && (*(byte *)(parent + 0x8e4) & 1) == 0 &&
        ((uint)this[0x27] >> 4 & 1) == 0) {
        FUN_007f4490(1, 0, DAT_00d5ef90); // enable vibration (1, 0, frequency)
        this[0x27] |= 0x10; // set bit 4 (vibration enabled)
    }

    // Lookup a hash string (0xb47bb605) in global table
    int *hashResult = FUN_00625050(0xb47bb605, 0);
    
    // Node2 at +0xA8
    nodePtr = this + 0x2a;
    if (hashResult == 0) {
        currentOffset = 0;
    } else {
        currentOffset = hashResult + 0x98; // offset within hash result object
    }

    if (*nodePtr != currentOffset) {
        if (*nodePtr != 0) {
            FUN_004daf90(nodePtr);
        }
        *nodePtr = currentOffset;
        if (currentOffset != 0) {
            this[0x2b] = *(int *)(currentOffset + 4);
            *(int **)(currentOffset + 4) = nodePtr;
        }
    }

    // Set flags on the object at +0xA0
    *(uint *)(this[0x28] + 0x970) |= 0x800;
    *(uint *)(this[0x28] + 0x974) |= 0x800;

    FUN_009c4ea0(0); // some init function

    // Set bit 1 in flags
    this[0x27] |= 2;

    // Check if node2 is valid and clear bit 0 in linked object
    if (*nodePtr != 0 && *nodePtr != 0x98) {
        hashResult = (int *)(*nodePtr - 0x98); // back to container
        if ((*(byte *)(hashResult + 0x1d0) & 1) != 0) {
            *(uint *)(hashResult + 0x1d0) &= 0xfffffffe;
            this[0x27] &= 0xfffffffd; // clear bit 1
        }
    }

    // If the object at +0xA0 has a specific state (0x04)
    if (*(char *)(this[0x28] + 0x1b8c) == '\x04') {
        this[0x29] = 0x2ca3cff6; // store a hash
        // Call vtable function at offset 0x2c with hash and parameters
        void (*func)(int, int, int, int, float, float) = *(void (**)(int, int, int, int, float, float))(*(int *)this[0x28] + 0x2c);
        func(0x2ca3cff6, 1, 1, 0, 3.0f, 3.0f);
        // Call another vtable function at offset 0x234 on the same object
        (*(void (**)(int, int))(*(int *)this[0x28] + 0x234))(0, 1);
    }

    // Store a global configuration value
    *(int *)(this[0x28] + 0x1eb4) = DAT_01205224;

    FUN_007ca8a0(); // finalization
}