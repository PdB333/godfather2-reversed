// FUNC_NAME: ManagedObject::~ManagedObject
void __fastcall ManagedObject::~ManagedObject(ManagedObject* this) {
    // Set vtable to class's own vtable (during destruction chain)
    this->vtable = &g_vtable_ManagedObject; // PTR_FUN_00d60804

    // Call base class destructor (likely a stub or base cleanup)
    BaseClass::~BaseClass(this); // FUN_006fc4c0 (address LAB_006f7670 passed, but reconstructed as base destructor)

    // Clean up member resources
    cleanupMember(this); // FUN_006f0e40

    // Release slot index if assigned (0xff = invalid/empty)
    if (this->m_slotIndex != 0xff) { // +0x28 (10th int offset)
        releaseSlot(this->m_slotIndex); // FUN_006f0d60
        this->m_slotIndex = 0xff;
    }

    // Free pointer member if not null
    if (this->m_pointerData != nullptr) { // +0x24 (9th int offset)
        freePointer(this->m_pointerData); // FUN_006f0800
        this->m_pointerData = nullptr;
    }

    // Perform global cleanup/deallocation
    globalCleanup(); // FUN_006fbc70
}