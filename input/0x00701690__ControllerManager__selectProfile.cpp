// FUNC_NAME: ControllerManager::selectProfile
void __thiscall ControllerManager::selectProfile(uint profileIndex) {
    // Validate profileIndex (must be 0-3)
    if (profileIndex >= 4) {
        return;
    }

    // Slot size is 0x10 bytes. Array of 4 slots starts at offset 0x42C.
    // Each slot has fields at relative offsets 0x00, 0x04, 0x08, 0x0C.
    int slotBase = profileIndex * 0x10 + this;
    uint32_t field0 = *(uint32_t*)(slotBase + 0x42C);
    uint32_t field4 = *(uint32_t*)(slotBase + 0x430);
    uint32_t field8 = *(uint32_t*)(slotBase + 0x434);
    uint32_t fieldC = *(uint32_t*)(slotBase + 0x438);

    // Copy selected profile data into active variables
    this->m_activeField0 = field0;      // +0x38C
    this->m_activeField0_dup = field0;  // +0x474
    this->m_activeField4 = field4;      // +0x390
    this->m_activeField4_dup = field4;  // +0x478
    this->m_activeField8 = field8;      // +0x32C
    this->m_activeFieldC = fieldC;      // +0x330
    this->m_activeProfileIndex = profileIndex; // +0x510

    // Update minimum threshold if necessary
    if (field8 < this->m_minField8) {   // +0x328
        this->m_minField8 = field8;     // +0x328

        // Notify virtual handler (vtable at +0x58, offset 0x28)
        void** vtable = *(void***)(this + 0x58);
        void (*onProfileChanged)(void*) = (void (*)(void*))vtable[0x28 / 4];
        onProfileChanged(this);
    }
}