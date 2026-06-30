// FUNC_NAME: Entity::~Entity

// Destructor for Entity class (likely has multiple inheritance due to many vtable pointers)
// Cleans up all sub-objects, releases resources, and deallocates memory
void __fastcall Entity::~Entity(Entity* this)
{
    // Set vtable pointers to base class vtables (for proper destruction of multiple bases)
    this->vtable0 = &g_pEntityVTable;            // +0x00
    this->vtable1 = &g_pEntityVTable1;           // +0x3C (param_1[0xf])
    this->vtable2 = &g_pEntityVTable2;           // +0x48 (param_1[0x12])
    this->vtable3 = &g_pEntityVTable3;           // +0x50 (param_1[0x14])
    this->vtable4 = &g_pEntityVTable4;           // +0x54 (param_1[0x15])
    this->vtable5 = &g_pEntityVTable5;           // +0x58 (param_1[0x16])

    // Call placement delete with size 0xC (likely scalar deleting destructor)
    // (FUN_008f67c0 takes size and this pointer)
    EntityDeallocate(0xC, this);

    // Release audio component if present and flag bit 13 is set
    if (this->m_pAudioComponent != nullptr) {
        if (this->m_flags & (1 << 13)) {
            this->m_flags &= ~(1 << 13);
            ReleaseAudioComponent(this->m_pAudioComponent); // FUN_00540700
        }
        MemoryFree(); // FUN_009f01a0 - possibly cleanup internal allocator
    }

    // Release sub-object at +0x78 (e.g. animation controller) if present
    void* pSubObj = this->m_pSubObject; // +0x78
    if (pSubObj != nullptr) {
        if (*(int*)((char*)pSubObj + 8) != 0) {
            DestroySubObject(pSubObj); // FUN_009e7530
        }
        MemoryFree(); // FUN_009f01a0
    }

    // Check condition for possibly removing scheduled event
    if ( ((this->m_flags >> 4) & 1) && ((this->m_flags >> 15) & 1) &&
         (this->m_pScheduledEvent != nullptr) ) {
        // Get pointer to event manager minus 0x48 (0x48 = sizeof some header?)
        int* pEventMgr = (int*)((char*)this->m_pScheduledEvent - 0x48);
        if (pEventMgr != nullptr) {
            Entity* local_4 = nullptr;
            // Virtual call to check if this entity is in event's target list
            char result = (*(char(__thiscall**)(int, Entity**))(*(int*)pEventMgr + 0x10))
                          (0x9A37DA3C, &local_4); // hash or GUID
            if (result && local_4 != nullptr) {
                RemoveEntityFromEvent(this); // FUN_00704360
            }
        }
    }

    // Release scheduled event pointer and null it
    if (this->m_pScheduledEvent != nullptr) {
        ReleaseRef(&this->m_pScheduledEvent); // FUN_004daf90
        this->m_pScheduledEvent = nullptr;
    }

    // Decrement reference counts (?) - call twice as per pattern
    DecrementRefCount(); // FUN_004df590
    DecrementRefCount(); // FUN_004df590
    ProcessPendingDeletes(); // FUN_004df600

    // If flag bit 7 is set, clean up specific subsystem
    if (this->m_flags & (1 << 7)) {
        CleanupSubsystem(this); // FUN_008557f0
    }

    // Clear two arrays at +0xA6 and +0xA8 (likely small fixed-size arrays)
    ClearArray(this->m_array1); // FUN_00408310
    ClearArray(this->m_array2); // FUN_00408310

    // Call cleanup function with parameter 6 (type of cleanup?)
    CleanupByType(this, 6); // FUN_0043c5b0

    // Release pointer at +0x60 (e.g., child entity)
    if (this->m_pChild != nullptr) {
        DestroyChild(this->m_pChild); // FUN_008ca010
        if (this->m_pChild != nullptr) {
            ReleaseRef(&this->m_pChild); // FUN_004daf90
            this->m_pChild = nullptr;
        }
    }

    // If counter at +0x6B is less than 25, decrement it and possibly more cleanup
    if (this->m_entityCounter < 25) { // +0x6B as byte
        DecrementCounter(this); // FUN_008dddc0
    }

    // If entity has a unique ID and global registry is active, unregister
    if ((this->m_uniqueID != -1) && (g_pEntityIDRegistry != nullptr)) {
        UnregisterEntityID(&this->m_uniqueID); // FUN_00454610
    }

    // Call custom cleanup callback if set
    if (this->m_pCleanupFunc != nullptr) {
        (this->m_cleanupCaller)(this->m_pCleanupFunc); // FUN_??? at +0xB2
    }

    // Release three more sub-objects (animations, components)
    if (this->m_pAnimController != nullptr) {
        *(int*)((char*)this->m_pAnimController + 8) = 0;
        this->m_pAnimController = nullptr;
    }
    if (this->m_pComponent1 != nullptr) {
        *(int*)((char*)this->m_pComponent1 + 8) = 0;
        this->m_pComponent1 = nullptr;
    }
    if (this->m_pComponent2 != nullptr) {
        *(int*)((char*)this->m_pComponent2 + 8) = 0;
        this->m_pComponent2 = nullptr;
    }
    if (this->m_pComponent3 != nullptr) {
        *(int*)((char*)this->m_pComponent3 + 8) = 0;
        this->m_pComponent3 = nullptr;
    }

    // Release scheduled event pointer again (already done earlier? safety)
    if (this->m_pScheduledEvent != nullptr) {
        ReleaseRef(&this->m_pScheduledEvent);
    }

    // Release another callback object
    if (this->m_pCallbackObj != nullptr) {
        (this->m_callbackFunc)(this->m_pCallbackObj); // FUN_??? at +0x71
    }

    // Final release of child
    if (this->m_pChild != nullptr) {
        ReleaseRef(&this->m_pChild);
    }

    // Final memory cleanup for this object's allocator
    FinalAllocatorCleanup(); // FUN_0046ea20
}