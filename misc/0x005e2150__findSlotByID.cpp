// FUNC_NAME: findSlotByID
/**
 * Address: 0x005e2150
 * Role: Searches a fixed-size array of 5 entries (each 0x4A4 bytes) at this+0x490.
 * Each entry has an int ID at offset 0. Returns a pointer to the data at offset 4
 * within the matching entry, or 0 if not found or id==0.
 */
void* __fastcall findSlotByID(void* thisPtr, int id) {
    if (id == 0) {
        return 0;
    }

    char* base = (char*)thisPtr + 0x490;  // +0x490: array of 5 entries, each 0x4A4 bytes
    for (int i = 0; i < 5; i++) {
        if (*(int*)(base + i * 0x4A4) == id) {
            return base + i * 0x4A4 + 4;   // returns pointer to data after ID (offset 4)
        }
    }
    return 0;
}