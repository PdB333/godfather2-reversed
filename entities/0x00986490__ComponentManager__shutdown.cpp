// FUNC_NAME: ComponentManager::shutdown
void __thiscall ComponentManager::shutdown() {
    // Set vtable pointers for this object and its sub-objects
    this->vtable1 = &PTR_FUN_00d90e18;          // +0x00
    this->vtable2 = &PTR_LAB_00d90df4;          // +0x10
    this->vtable3 = &PTR_LAB_00d90df0;          // +0x4C

    // Destroy 10 component slots (each 16 bytes, slot layout: [pData, ?, ?, pDestroyFunc])
    int slotCount = 9; // actually 10 iterations, index 9 down to 0
    // puVar2 points to the third dword of slot9 (offset +0x10C)
    int* pSlotEnd = &this->componentSlots[9].pDestroyFunc; // +0x10C

    do {
        // Each slot: pData at -4 dwords (offset -16) and pDestroyFunc at -1 dword (offset -4)
        if (*(pSlotEnd - 4) != 0) {
            // Call the destructor function on the data pointer
            ((void (*)(void*))*(pSlotEnd - 1))(*(pSlotEnd - 4));
        }
        slotCount--;
        pSlotEnd -= 4; // move to previous slot
    } while (slotCount >= 0);

    // Destroy an additional object stored elsewhere in this
    if (this->m_pAdditionalData != 0) {        // +0x54
        ((void (*)(void*))this->m_pAdditionalDestroy)(this->m_pAdditionalData); // +0x60
    }

    // Switch another vtable pointer
    this->vtable3 = &PTR_LAB_00d90dec;          // +0x4C

    // Clear a global initialization flag
    g_bSystemInitialized = 0;                  // DAT_01130048

    // Final cleanup
    systemCleanup();                           // FUN_005c16e0
}