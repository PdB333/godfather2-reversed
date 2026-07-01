// FUNC_NAME: CrimeManager::updateCrimeScenes
void __fastcall CrimeManager::updateCrimeScenes(void* this) {
    uint32_t idx = 0;
    // +0x1A8: count of items in the array
    // +0x1A4: pointer to array of pointers (crime scene items)
    if (*(int32_t*)((uint8_t*)this + 0x1A8) != 0) {
        do {
            int32_t* item = *(int32_t**)(*(int32_t*)((uint8_t*)this + 0x1A4) + idx * 4);
            // +0x04: type field; skip type 7 (e.g., inactive/completed)
            if (item != nullptr && item[1] != 7) {
                int32_t* subObject = (int32_t*)item[4]; // +0x10
                if (subObject != nullptr) {
                    // +0x64 (100): active flag (short)
                    if (*(int16_t*)((uint8_t*)subObject + 0x64) != 0) {
                        char pauseCheck = FUN_008fda60(); // likely isGamePaused()
                        if (pauseCheck == 0) {
                            int32_t managerRef = FUN_008fdd30(); // e.g., get current mission manager
                            char valid = FUN_00849ea0(managerRef); // e.g., isMissionActive
                            if (valid != 0) {
                                FUN_008c2290(&subObject); // process the sub-object (e.g., advance state)
                            }
                        }
                    }
                }
            }
            idx++;
        } while (idx < *(uint32_t*)((uint8_t*)this + 0x1A8));
    }
    return;
}