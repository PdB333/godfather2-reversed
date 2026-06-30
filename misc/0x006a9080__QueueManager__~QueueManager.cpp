// FUNC_NAME: QueueManager::~QueueManager
// Function at 0x006a9080: Destructor for a class that manages a circular FIFO queue of dynamically allocated objects.
// The class has multiple vtable pointers, indicating inheritance or interface implementation.
// Offsets: +0x00 vtable, +0x0C second vtable?, +0x10 buffer pointer, +0x11 size?, +0x12 array pointer, +0x13 capacity, +0x14 read index, +0x15 count.

void __thiscall QueueManager::~QueueManager(void* this)
{
    undefined4 uVar1;
    int iVar2;

    // Set vtables to specific implementations
    *(void**)this = &PTR_FUN_00d5d914;          // vtable for this class
    *(uint*)((int)this + 0xC) = &PTR_LAB_00d5d910; // second vtable

    // Unregister from global managers / cleanup globals
    FUN_004086d0(&DAT_01206940);
    FUN_005e6640(FUN_006a8f10);                // Register a callback? (maybe unregister)
    FUN_00ab4db0(&DAT_00d5d8e0);              // Another global cleanup

    // Free a separate buffer if allocated
    if (*(void**)((int)this + 0x10) != 0) {
        FUN_005e3c00(*(void**)((int)this + 0x10)); // Free memory
        *(undefined4*)((int)this + 0x10) = 0;
        *(undefined4*)((int)this + 0x11) = 0;
    }

    FUN_00ab4e70();                           // Some static cleanup

    // Drain the circular queue
    iVar2 = *(int*)((int)this + 0x54);        // current count
    while (iVar2 != 0) {
        uVar1 = *(undefined4*)(*(int*)((int)this + 0x48) + *(int*)((int)this + 0x50) * 4);
        iVar2 = *(int*)((int)this + 0x50) + 1;
        *(int*)((int)this + 0x50) = iVar2;
        if (*(int*)((int)this + 0x4C) <= iVar2) {
            *(int*)((int)this + 0x50) = 0;    // wrap around
        }
        *(int*)((int)this + 0x54) = *(int*)((int)this + 0x54) - 1;
        FUN_00603210(uVar1);                  // Destructor for queued object
        FUN_005e3c00(uVar1);                  // Free memory
        iVar2 = *(int*)((int)this + 0x54);    // reload count
    }

    // Free the array pointer itself
    if (*(void**)((int)this + 0x48) != 0) {
        FUN_009c8f10(*(void**)((int)this + 0x48)); // delete[] array
    }

    FUN_00ab4d30();                           // Another static cleanup

    // Set vtable to base class (probably before deletion)
    *(uint*)((int)this + 0xC) = &PTR_LAB_00d5d900;

    DAT_01129950 = 0;
    FUN_004083d0();                           // Final global cleanup
    return;
}