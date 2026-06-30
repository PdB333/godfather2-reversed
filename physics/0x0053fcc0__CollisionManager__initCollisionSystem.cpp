// FUNC_NAME: CollisionManager::initCollisionSystem
void CollisionManager::initCollisionSystem() {
    // Call to some global initialization (maybe physics engine init)
    FUN_00bf49c0();
    // Set something with global DAT_0103b26c (likely a singleton or configuration)
    FUN_00bf4b30(_DAT_0103b26c);

    // Determine a flag based on member at +0x28 (bool)
    // If true, local_23 = 3, else 2 (used later? Not used further – possibly a debug flag)
    local_23 = (*(char *)(this + 0x28) != '\0') + 0x02;

    // Build a temporary structure on stack (likely a GUID or hash input)
    local_d0 = 0;
    local_cc = DAT_00e4499c; // some constant
    local_c8 = 0;
    local_c4 = 0;
    local_34 = 0;
    local_b8 = 1; // marker

    // Get thread-local storage (memory manager?)
    TlsGetValue(DAT_01139810);

    // Allocate 0x310 bytes with tag 0x2f
    int buffer1 = allocateMemory(0x310, 0x2f);
    *(short *)(buffer1 + 4) = 0x310;

    // Generate a hash from the stack structure and constant 0xc544
    int hash = generateHash(local_e0, 0xc544);
    *(int *)(this + 0x24) = hash; // store hash

    // Get TLS again
    TlsGetValue(DAT_01139810);

    // Allocate 0x30 bytes for a vtable object
    int* vtableObj = allocateMemory(0x30, 0xd);
    *(short *)(vtableObj + 1) = 0x30; // size field

    // Initialize the vtable object (probably queries or debug)
    FUN_00a0ebb0(*(int *)(this + 0x24), 1);

    // Set vtable pointers for the 0x30-sized object
    *vtableObj = &PTR_FUN_00e3918c;
    vtableObj[2] = &PTR_LAB_00e391a0;
    vtableObj[3] = &PTR_LAB_00e391a8;

    // Ref count decrement for the vtable object (similar to smart pointer)
    if (*(short *)(vtableObj + 1) != 0) {
        *(short *)((int)vtableObj + 6) = *(short *)((int)vtableObj + 6) - 1;
        if (*(short *)((int)vtableObj + 6) == 0) {
            (**(code **)*vtableObj)(1); // release function
        }
    }

    // If member at +0x28 is true, allocate an additional object from TLS free list
    if (*(char *)(this + 0x28) != '\0') {
        LPVOID tls = TlsGetValue(DAT_01139810);
        int* freeNode = *(int **)((int)tls + 0x98);
        if (freeNode == NULL) {
            freeNode = allocateFromPool(0xc, 0xd); // allocate a node
        } else {
            // pop from free list
            *(int *)((int)tls + 0x9c) = *(int *)((int)tls + 0x9c) - 1;
            *(int *)((int)tls + 0x98) = *freeNode;
        }
        if (freeNode != NULL) {
            int obj = createNewObject(); // FUN_00561790
            *(int *)(this + 0x2c) = obj;
        } else {
            *(int *)(this + 0x2c) = 0;
        }
    }

    // Call some function on the hash object's internal pointer
    FUN_00c07180(*(int *)(*(int *)(this + 0x24) + 0x74));

    // Another initialization call
    FUN_00559ba0();

    // Now set up collision group matrix (0x100 bytes)
    TlsGetValue(DAT_01139810);
    int* groupMatrix = allocateMemory(0x100, 0x27);
    *(short *)(groupMatrix + 1) = 0x100;

    // Initialize collision system structure
    FUN_00a67a10();

    // Set vtable for group matrix object
    *groupMatrix = &PTR_FUN_00e39128;
    groupMatrix[2] = &PTR_LAB_00e39138;
    groupMatrix[3] = &PTR_LAB_00e39140;
    groupMatrix[4] = &PTR_LAB_00e39150;
    groupMatrix[5] = &PTR_LAB_00e39158;

    // Set default collision response (no collision?)
    setDefaultCollisionResponse(0xfffffffe, 0xfffffffe);

    // Enable collision between various object group pairs
    // Each pair: (groupA, groupB) – bitmask values
    // Common groups: 2 (player?), 4 (static?), 8 (dynamic?), 0x10 (vehicle?), etc.
    enableCollisionPair(4, 4);
    enableCollisionPair(4, 8);
    enableCollisionPair(4, 2);
    enableCollisionPair(4, 0x10);
    enableCollisionPair(4, 0x20);
    enableCollisionPair(4, 0x100);
    enableCollisionPair(4, 0x200);
    enableCollisionPair(4, 0x40000);
    enableCollisionPair(4, 0x20000);
    enableCollisionPair(4, 0x400);
    enableCollisionPair(0x8000, 4);
    enableCollisionPair(0x8000, 2);
    enableCollisionPair(0x8000, 0x10);
    enableCollisionPair(0x8000, 0x20);
    enableCollisionPair(0x8000, 0x100);
    enableCollisionPair(0x8000, 0x200);
    enableCollisionPair(0x8000, 0x40000);
    enableCollisionPair(0x8000, 0x400);
    enableCollisionPair(0x10, 0x10);
    enableCollisionPair(0x10, 2);
    enableCollisionPair(0x10, 0x20);
    enableCollisionPair(0x10, 0x20000);
    enableCollisionPair(0x10, 0x100);
    enableCollisionPair(0x10, 0x200);
    enableCollisionPair(0x10, 0x40000);
    enableCollisionPair(0x10, 8);
    enableCollisionPair(0x20, 0x20);
    enableCollisionPair(0x20, 2);
    enableCollisionPair(0x20, 8);
    enableCollisionPair(0x20, 0x100);
    enableCollisionPair(0x20, 0x200);
    enableCollisionPair(0x20, 0x40000);
    enableCollisionPair(0x20, 0x20000);
    enableCollisionPair(0x40, 8);
    enableCollisionPair(0x80, 2);
    enableCollisionPair(0x80, 0x100);
    enableCollisionPair(0x80, 0x20000);
    enableCollisionPair(0x100, 0x100);
    enableCollisionPair(0x100, 0x200);
    enableCollisionPair(0x100, 0x40000);
    enableCollisionPair(0x100, 0x20000);
    enableCollisionPair(0x100, 2);
    enableCollisionPair(0x200, 0x200);
    enableCollisionPair(0x200, 0x100);
    enableCollisionPair(0x200, 0x1000);
    enableCollisionPair(0x200, 0x40000);
    enableCollisionPair(0x200, 0x20000);
    enableCollisionPair(0x200, 2);
    enableCollisionPair(0x20000, 0x40000);
    enableCollisionPair(0x20000, 0x100);
    enableCollisionPair(0x20000, 2);
    enableCollisionPair(0x40000, 0x40000);
    enableCollisionPair(0x40000, 0x100);
    enableCollisionPair(0x40000, 2);
    enableCollisionPair(0x800, 4);
    enableCollisionPair(0x800, 0x10);
    enableCollisionPair(0x800, 0x20);
    enableCollisionPair(0x800, 0x100);
    enableCollisionPair(0x800, 0x40000);
    enableCollisionPair(0x800, 0x20000);
    enableCollisionPair(0x800, 0x200);
    enableCollisionPair(0x1000, 2);
    enableCollisionPair(0x1000, 0x100);
    enableCollisionPair(0x1000, 0x200);
    enableCollisionPair(0x1000, 0x40000);
    enableCollisionPair(0x1000, 0x20000);
    enableCollisionPair(0x1000, 0x20);
    enableCollisionPair(0x2000, 8);
    enableCollisionPair(0x4000, 2);
    enableCollisionPair(0x4000, 0x4000);
    enableCollisionPair(0x10000, 4);
    enableCollisionPair(0x10000, 2);
    enableCollisionPair(0x10000, 0x20);
    enableCollisionPair(0x10000, 0x200);
    enableCollisionPair(0x10000, 0x40000);

    // Store the group matrix pointer
    *(int **)(this + 0x54) = groupMatrix;

    // Finalize the group matrix (e.g., build acceleration structure)
    finalizeCollisionMatrix(groupMatrix, 1, 0, 1);
}