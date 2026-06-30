// FUNC_NAME: ComponentManager::findComponentByID
// 0x006fd420
// Searches through a fixed-size array (2 slots) for an entry whose stored type ID matches the given typeId.
// On match, writes the address of the corresponding data slot into outData.

void __thiscall ComponentManager::findComponentByID(int this, int* outData, int typeId) {
    if (typeId == 0) {
        return;
    }

    // Entry array starts at this + 0x190 (400), 2 entries of 0x38 (56) bytes each
    // Data array starts at this + 0x180 (384), same structure size
    for (unsigned int idx = 0; idx < 2; ++idx) {
        int* entry = (int*)(this + 0x190 + idx * 0x38); // each entry is 14 ints
        if (entry[2] == 0) { // offset +0x08: active flag
            continue;
        }

        int storedType;
        if (entry[0] == 0) { // offset +0x00: raw value (possibly a pointer)
            storedType = 0;
        } else {
            storedType = entry[0] - 0x48; // convert to type ID by subtracting offset
        }

        if (storedType == typeId) {
            *outData = this + 0x180 + idx * 0x38; // return pointer to matching data slot
            return;
        }
    }
    // Not found – falls through without setting outData
}