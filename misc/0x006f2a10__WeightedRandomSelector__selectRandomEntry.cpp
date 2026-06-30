// FUNC_NAME: WeightedRandomSelector::selectRandomEntry
int __fastcall WeightedRandomSelector::selectRandomEntry(int thisPtr) {
    // thisPtr: pointer to a WeightedRandomSelector object
    // Layout:
    // +0x74: array[8] of MagicType (4 ints each) - magic numbers identifying empty slots (0xBABABABA, 0xBEFBEFBE, 0xEAC15A55, 0x91100911)
    // +0xF4: array[8] of float weights
    // +0x114: float randomScale (multiplier for random value)

    int randomInt = _rand();
    float randomValue = (float)randomInt * 0x00e44590; // scale factor (likely 1.0 / RAND_MAX)
    float accumulatedWeight = 0.0f;
    float currentRandom = randomValue * *(float *)(thisPtr + 0x114);

    float* weights = (float*)(thisPtr + 0xF4);
    int* magicSlotBase = (int*)(thisPtr + 0x7C); // points to third magic of first slot (slot->magic2)

    for (unsigned int i = 0; i < 8; i++) {
        // Each slot is 16 bytes: magic0, magic1, magic2, magic3
        int* slotMagic0 = magicSlotBase - 2;
        int* slotMagic1 = magicSlotBase - 1;
        int* slotMagic2 = magicSlotBase;
        int* slotMagic3 = magicSlotBase + 1;

        // Check if this slot is NOT the empty sentinel (skip slots with exact magic sequence)
        bool isNotEmpty = (*slotMagic0 != 0xBABABABA) ||
                          (*slotMagic1 != 0xBEFBEFBE) ||
                          (*slotMagic2 != 0xEAC15A55) ||
                          (*slotMagic3 != 0x91100911);

        if (isNotEmpty) {
            accumulatedWeight += *weights;
            if (currentRandom < accumulatedWeight) {
                // Slot is valid and passes weight test; retrieve the object pointer
                void* slotObject = (void*)FUN_00446100(slotMagic0, 0); // helper to get object from slot data
                if (slotObject != nullptr) {
                    int resultId = 0;
                    // Virtual function at vtable+0x10: likely returns bool and fills resultId
                    bool success = (*(bool(__thiscall**)(void*, int, int*))(*(int*)slotObject + 0x10))(slotObject, 0x862f2a73, &resultId);
                    if (success && resultId != 0) {
                        return resultId;
                    }
                }
            }
            // Reset currentRandom for next iteration (though not needed, but original code does)
            currentRandom = randomValue * *(float *)(thisPtr + 0x114);
        }

        weights++;
        magicSlotBase += 4; // advance 4 ints (16 bytes) for next slot
    }

    return 0;
}