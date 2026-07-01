// FUNC_NAME: SimManager::getSimSlot
uint8_t* SimManager::getSimSlot(int index) {
    // +0x1c: m_slots array start (each slot is 0x10 bytes)
    return reinterpret_cast<uint8_t*>(this) + 0x1c + index * 0x10;
}