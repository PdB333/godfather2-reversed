// FUNC_NAME: ObjectManager::markAllDirty
// Function address: 0x00626910
// Marks all managed objects as dirty (flag bit 0 at offset +5).
// Iterates over multiple object lists and a struct list, setting the dirty flag.
// Calls handleCleanObject(FUN_00626640) for objects in m_pObjectList3 that are not dirty and not bit4 set.

class ObjectManager {
public:
    // Offset +0x20: pointer to a single object
    // Offset +0x08: array of (id, pointer) pairs (8 bytes each)
    // Offset +0x1c: array of pointers
    // Offset +0x10: array of pointers
    // Offset +0x18: array of 12-byte structs (first 4 bytes: pointer to object)
    // Offsets +0x28, +0x24, +0x34, +0x38: counts for the arrays

    void __thiscall markAllDirty() {
        byte *dirtyByte;
        int *ptr;
        int idx;
        int innerIdx;

        // Set dirty on the single object at offset 0x20
        dirtyByte = (byte *)(*(int *)(this + 0x20) + 5);
        *dirtyByte = *dirtyByte | 1;

        // Process array at offset 0x08 (id, pointer pairs)
        idx = 0;
        if (0 < *(int *)(this + 0x28)) {
            do {
                // Check if the id equals 4
                if (*(int *)(*(int *)(this + 0x08) + idx * 8) == 4) {
                    dirtyByte = (byte *)(*(int *)(*(int *)(this + 0x08) + 4 + idx * 8) + 5);
                    *dirtyByte = *dirtyByte | 1;
                }
                idx = idx + 1;
            } while (idx < *(int *)(this + 0x28));
        }

        // Process array at offset 0x1c (pointer array)
        idx = 0;
        if (0 < *(int *)(this + 0x24)) {
            do {
                dirtyByte = (byte *)(*(int *)(*(int *)(this + 0x1c) + idx * 4) + 5);
                *dirtyByte = *dirtyByte | 1;
                idx = idx + 1;
            } while (idx < *(int *)(this + 0x24));
        }

        // Process array at offset 0x10 (pointer array with condition)
        idx = 0;
        if (0 < *(int *)(this + 0x34)) {
            do {
                // If object flags (bit0 and bit4) are not set, call handleCleanObject
                if ((*(byte *)(*(int *)(*(int *)(this + 0x10) + idx * 4) + 5) & 0x11) == 0) {
                    handleCleanObject();
                }
                idx = idx + 1;
            } while (idx < *(int *)(this + 0x34));
        }

        // Process array at offset 0x18 (struct array of 12 bytes each)
        idx = 0;
        if (0 < *(int *)(this + 0x38)) {
            innerIdx = 0;
            do {
                ptr = (int *)(innerIdx + *(int *)(this + 0x18));
                idx = idx + 1;
                *(byte *)(*ptr + 5) = *(byte *)(*ptr + 5) | 1;
                innerIdx = innerIdx + 0xc; // 12 bytes per struct
            } while (idx < *(int *)(this + 0x38));
        }
    }

private:
    // Unknown function, likely handles clean objects
    void handleCleanObject();
};