// FUNC_NAME: SetAnalogValue
void SetAnalogValue(uint id, const float* value)
{
    if (id == 0) {
        return;
    }

    uint index = id & 0xFF;
    float* targetTable;

    // Select which table based on high bit of id
    if ((id & 0x80000000) == 0) {
        targetTable = (float*)((uint)gAbsoluteValues + index * 0x10);
    } else {
        targetTable = (float*)((uint)gRelativeValues + index * 0x10);
    }

    float oldX = targetTable[0];
    float oldY = targetTable[1];
    float newX = value[0];
    float newY = value[1];
    bool changed = false;

    if (oldX != newX) {
        targetTable[0] = newX;
        changed = true;
    }
    if (oldY != newY) {
        targetTable[1] = newY;
        changed = true;
    }

    if (changed) {
        // Notify the manager singleton that the value changed
        if ((id & 0x80000000) != 0) {
            // Call virtual method at vtable+0x178 (no extra args)
            typedef void (*Callback)(void*);
            Callback func = *(Callback*)(*(void**)gValueManager + 0x178 / 4);
            func(gValueManager);
        } else {
            // Call virtual method at vtable+0x1b4 (index, target table pointer, 1)
            typedef void (*Callback)(void*, uint, float*, int);
            Callback func = *(Callback*)(*(void**)gValueManager + 0x1b4 / 4);
            func(gValueManager, index, targetTable, 1);
        }
    }
}

// Global data referenced by the function
// Table of 256 entries of size 0x10 (4 floats); only first two floats used (x,y)
extern float gAbsoluteValues[256][4];   // offset: 0x011d97f0
extern float gRelativeValues[256][4];   // offset: 0x011ea8f0
// Singleton manager object with vtable pointer at offset 0
extern void* gValueManager;             // offset: 0x01205750