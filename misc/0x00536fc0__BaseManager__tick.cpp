// FUNC_NAME: BaseManager::tick
void BaseManager::tick() {
    // +0x04: pointer to an object or array (used repeatedly in loop)
    uint32_t* dataPtr = *(uint32_t**)((uint8_t*)this + 4);
    // +0x02: iteration count (short)
    int16_t count = *(int16_t*)((uint8_t*)this + 2);

    int16_t i = 0;
    if (count > 0) {
        do {
            FUN_00577b30(dataPtr);  // process with dataPtr (same each iteration)
            FUN_00414aa0();         // periodic check / yield
            ++i;
        } while (i < count);
    }
}