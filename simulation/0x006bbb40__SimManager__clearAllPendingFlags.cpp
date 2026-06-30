// FUNC_NAME: SimManager::clearAllPendingFlags
void __fastcall SimManager::clearAllPendingFlags(SimManager* this) {
    // Iterate over an array of object handles at +0xA0 with size +0xA4
    // Each handle is a 0x18-byte structure containing a pointer to an object.
    // For valid objects (non-null and with type != 0x48), clear bit 26 (0x04000000) of flags at +0x14.
    
    uint count = *(uint*)(this + 0xA4);
    if (count != 0) {
        uintptr_t* handleArray = *(uintptr_t**)(this + 0xA0);
        for (uint i = 0; i < count; i++) {
            uintptr_t pObject = handleArray[i * (0x18 / 4)]; // stride 0x18, first field is pointer
            if (pObject != 0 && pObject != 0x48) {
                // Clear the "pending" flag (bit 26) in the object's state at offset 0x14
                *(uint*)(pObject + 0x14) &= 0xFBFFFFFF;
            }
        }
    }
    
    // Finalization step (likely clears internal bookkeeping)
    FUN_006bb6d0(); // SimManager::onClearComplete (tentative)
}