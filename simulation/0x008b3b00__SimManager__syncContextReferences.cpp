// FUNC_NAME: SimManager::syncContextReferences
void __thiscall SimManager::syncContextReferences(int thisPtr, int context) {
    uint i = 0;
    // Check if there are any items in the array at thisPtr+0xf8 (array base) with count at thisPtr+0xfc
    if (*(int*)(thisPtr + 0xfc) != 0) {
        do {
            // Each entry is 8 bytes; first 4 bytes is the object pointer
            int objPtr = *(int*)(*(int*)(thisPtr + 0xf8) + i * 8);
            // Skip null pointers or type marker 0x48 (invalid type)
            if (objPtr != 0 && objPtr != 0x48) {
                // Call a global check function (e.g., isObjectActive)
                bool isActive = (bool)FUN_00481620();  // FIXME: likely uses this or context
                if (isActive) {
                    // Get a reference value from the context (e.g., current target ID)
                    int* refPtr = (int*)FUN_004baf90(context);
                    if (refPtr != (int*)0x0) {
                        // Compare with object's stored reference at offset 0x1eac
                        if (*refPtr != *(int*)(objPtr + 0x1eac)) {
                            // Mismatch: remove object from context
                            FUN_008ae030(context);
                        }
                    }
                }
            }
            i++;
        } while (i < *(uint*)(thisPtr + 0xfc));
    }
}