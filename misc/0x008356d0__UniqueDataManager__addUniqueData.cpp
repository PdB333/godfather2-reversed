// FUNC_NAME: UniqueDataManager::addUniqueData
void __thiscall UniqueDataManager::addUniqueData(UniqueData* data) {
    // Check for duplicates based on four int fields (likely a unique key at +0x88 to +0x94)
    uint count = this->dataCount; // +0xD4
    if (count != 0) {
        int** array = this->dataArray; // +0xD0
        for (uint i = 0; i < count; i++) {
            UniqueData* entry = (UniqueData*)(array[i]); // Each entry is a pointer to a UniqueData
            // Compare the four ints (key) at offsets 0x88, 0x8C, 0x90, 0x94
            if (entry->field_88 == data->field_88 &&
                entry->field_8C == data->field_8C &&
                entry->field_90 == data->field_90 &&
                entry->field_94 == data->field_94) {
                // Duplicate found – do not add
                return;
            }
        }
    }

    // Copy the name string from data->name (+0x50) to data->nameBuffer (+0xDC)
    // Default to a null placeholder if name pointer is null
    const char* sourceName = data->name; // +0x50
    if (sourceName == nullptr) {
        sourceName = "DAT_0120546e"; // Placeholder string constant
    }
    copyString(data->nameBuffer, sourceName); // FUN_004089b0 (string copy destination at +0xDC)

    // Ensure the dynamic array has enough capacity; resize if needed
    if (this->dataCount == this->dataCapacity) { // +0xD4 == +0xD8
        int newCapacity = (this->dataCapacity == 0) ? 1 : (this->dataCapacity * 2);
        resizeDataArray(newCapacity); // FUN_00834f20
    }

    // Add the new data pointer to the array
    int** slot = this->dataArray + this->dataCount; // +0xD0 + count*4
    this->dataCount++;
    if (slot != nullptr) {
        *slot = data;
    }
}