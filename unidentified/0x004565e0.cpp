// FUN_004565e0: SlotManager::updateActiveSlot
int SlotManager::updateActiveSlot(void) {
    // +0x14 = pointer to current slot object (ResourceSlot*)
    // +0x1c = copy of the slot pointer (used as active handle)
    this->m_pActiveSlot = this->m_pSlot; // offset 0x1c = offset 0x14

    if (this->m_pSlot != nullptr) {
        // FUN_004cb440 returns a handle/pointer derived from the slot (maybe via global state)
        int* pHandle = (int*)FUN_004cb440();
        int data8 = pHandle[2]; // dereference offset +8
        FUN_00456530(data8); // process the data
        FUN_004c9550(DAT_01223404, data8); // register with global manager
        return (int)pHandle;
    }
    return 0;
}