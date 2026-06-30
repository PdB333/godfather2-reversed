// FUNC_NAME: TaskManager::~TaskManager

// Destructor for TaskManager (manages job threads, mutexes, and embedded resources).
// Address: 0x004c0f60
// Called from multiple cleanup paths (at 0x004c0f30, 0x00901990, 0x009018b0).
// The object layout uses vtable pointers and a flag byte at +0x1C4, job thread pointer at +0x1C0,
// embedded objects at +0x1CC, +0x1D4, +0x1DC, +0x1E4, +0x1EC, and optional pointer at +0x200.

void __thiscall TaskManager::~TaskManager(TaskManager* this)
{
    // Override vtable pointers (likely allows polymorphic cleanup)
    // +0x00: primary vtable
    this->vtable = &PTR_FUN_00e35f80;
    // +0x3C: secondary vtable (for embedded object?)
    this->embeddedVtable1 = &PTR_LAB_00e360dc;
    // +0x48
    this->embeddedVtable2 = &PTR_LAB_00e360ec;
    // +0x50
    this->embeddedVtable3 = &PTR_LAB_00e360f0;
    // +0x54
    this->embeddedVtable4 = &PTR_LAB_00e360f8;
    // +0x58
    this->embeddedVtable5 = &PTR_LAB_00e36158;

    // Check if bit 3 of the flag byte at +0x1C4 is set
    if ((this->flags & 0x08) != 0)
    {
        // Cleanup a child object (likely a thread or callback)
        destructChildObject(this);                     // FUN_004c10b0
        decrementRefCount(&globalResourceA);           // FUN_004086d0, using DAT_0120e924
    }

    // If a job thread handle exists (+0x1C0)
    if (this->jobThread != 0)
    {
        // Lock a mutex twice (nested lock or separate locks)
        enterCriticalSection();                        // FUN_004c2390
        enterCriticalSection();                        // FUN_004c2390
        // Free the thread resource
        freeThreadMemory(this->jobThread);             // FUN_009c8eb0
    }
    this->jobThread = 0;

    // Release reference on a global resource
    decrementRefCount(&globalResourceB);               // FUN_004086d0, using DAT_012069c4

    // Shutdown a subsystem (thread pool, etc.)
    shutdownSubsystem();                              // FUN_004c2130

    // If optional 3rd‑party pointer exists (+0x200)
    if (this->optionalObject != 0)
    {
        // Destroy it
        destroyOptionalObject();                      // FUN_009f01a0
    }

    // Release and destroy a series of embedded objects at +0x1CC, +0x1D4, +0x1DC, +0x1E4, +0x1EC
    // Each is a small structure (e.g., std::string or reference‑counted object)
    decrementRefCount(&this->embeddedObj1);            // FUN_004086d0, at +0x1CC
    destroyEmbeddedObject(&this->embeddedObj1);        // FUN_00408310, at +0x1CC

    decrementRefCount(&this->embeddedObj2);            // FUN_004086d0, at +0x1D4
    destroyEmbeddedObject(&this->embeddedObj2);        // FUN_00408310, at +0x1D4

    decrementRefCount(&this->embeddedObj3);            // FUN_004086d0, at +0x1DC
    destroyEmbeddedObject(&this->embeddedObj3);        // FUN_00408310, at +0x1DC

    // Note: only destroy, no release for the next ones
    destroyEmbeddedObject(&this->embeddedObj4);        // FUN_00408310, at +0x1E4

    // Destroy two global embedded objects
    destroyEmbeddedObject(&globalEmbedded1);            // FUN_00408310, at DAT_012180f8
    destroyEmbeddedObject(&globalEmbedded2);            // FUN_00408310, at DAT_012180f0

    destroyEmbeddedObject(&this->embeddedObj5);        // FUN_00408310, at +0x1EC

    // Final cleanup – e.g., free internal caches
    finalCleanup();                                   // FUN_0046ea20
}