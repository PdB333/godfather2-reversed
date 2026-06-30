// FUNC_NAME: CSomeManager::findSlotByID
// Address: 0x005e2150
// Role: Searches a fixed-size array of 5 slots (each 0x4A4 bytes) for a matching ID. Returns pointer to start of slot data (offset +4) on success, nullptr on failure.
// Array base at this+0x490, each slot begins with an int ID at offset 0, followed by 0x4A0 bytes of data.

int* __thiscall CSomeManager::findSlotByID(int id) {
    int* result;

    if (id != 0) {
        // Iterate over 5 slots
        for (int i = 0; i < 5; i++) {
            // Check if slot ID matches (slot begins at this+0x490 + i*0x4A4)
            if (id == *(int*)(((char*)this) + 0x490 + i * 0x4A4)) {
                // Return pointer to slot data (offset +4)
                result = (int*)(((char*)this) + 0x490 + i * 0x4A4 + 4);
                return result;
            }
        }
    }
    return 0;
}