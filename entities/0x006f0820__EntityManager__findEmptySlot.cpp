// FUNC_NAME: EntityManager::findEmptySlot
bool __thiscall EntityManager::findEmptySlot(int* outSlotPointer, uint* outIndex) {
    bool result = false;
    if (this->pSlotArray != nullptr && outSlotPointer != nullptr) {
        uint index = 0;
        char* usedFlag = this->pSlotArray + 0x29; // Start of first slot's used flag
        while (*usedFlag != '\0') {
            index++;
            usedFlag += 0x2c; // Stride to next slot
            if (index > 4) {
                return result; // No empty slot found
            }
        }
        // Mark slot as used
        *(this->pSlotArray + index * 0x2c + 0x29) = 1;
        *outSlotPointer = this->pSlotArray + index * 0x2c; // Pointer to slot base
        *outIndex = index;
        result = true;
    }
    return result;
}