// FUNC_NAME: setTransformSlot
// Function address: 0x0060add0
// Purpose: Updates a 4-float transform entry (e.g., orientation/position) in one of two global arrays
// and notifies a manager via vtable callback if the value changed.
// param_2: bit31 selects array (clear = g_transformArray1, set = g_transformArray2),
//          lower 8 bits are the index (0-255).
// param_3: pointer to 4 float values to copy (source transform)
// param_1: unused (possibly a this pointer from inlining)

void setTransformSlot(uint slotAndFlag, const float* sourceTransform)
{
    uint index = slotAndFlag & 0xFF;
    float* targetSlot;

    // Select array based on sign bit
    if ((slotAndFlag & 0x80000000) == 0) {
        // Array 1: 256 entries of 4 floats (0x10 bytes each)
        targetSlot = &g_transformArray1[index * 4]; // +0x0 per entry
    } else {
        // Array 2: same structure
        targetSlot = &g_transformArray2[index * 4]; // +0x0 per entry
    }

    // Compare and copy each float individually
    bool changed = false;
    // Copy first component
    if (targetSlot[0] != sourceTransform[0]) {
        targetSlot[0] = sourceTransform[0];
        changed = true;
    }
    // Copy second component
    if (targetSlot[1] != sourceTransform[1]) {
        targetSlot[1] = sourceTransform[1];
        changed = true;
    }
    // Copy third component
    if (targetSlot[2] != sourceTransform[2]) {
        targetSlot[2] = sourceTransform[2];
        changed = true;
    }
    // Copy fourth component
    if (targetSlot[3] != sourceTransform[3]) {
        targetSlot[3] = sourceTransform[3];
        changed = true;
    }

    // Notify manager if any component changed
    if (changed) {
        // gTransformManager is a global object with a vtable
        void* manager = gTransformManager; // DAT_01205750
        int* vtable = *(int**)manager;     // first field is vtable ptr

        if (slotAndFlag & 0x80000000) {
            // Call vtable function at offset 0x178 (no explicit parameters, likely thiscall)
            // This is a method on the manager object (receiver in ecx)
            typedef void (__thiscall *ManagerFunc0)(void*);
            ((ManagerFunc0)(vtable[0x178 / 4]))(manager);
        } else {
            // Call vtable function at offset 0x1b4 with parameters (manager, index, data, flag)
            typedef void (__thiscall *ManagerFunc1)(void*, uint, float*, int);
            ((ManagerFunc1)(vtable[0x1b4 / 4]))(manager, index, targetSlot, 1);
        }
    }
}

// Global arrays (DAT_011d97f0, DAT_011ea8f0) - each 256 entries of 4 floats
// The actual declaration would be something like:
// alignas(16) float g_transformArray1[256 * 4]; // +0x011d97f0
// alignas(16) float g_transformArray2[256 * 4]; // +0x011ea8f0
// Pointer to manager object (DAT_01205750)
// void* gTransformManager; // pointer to instance with vtable at +0x0