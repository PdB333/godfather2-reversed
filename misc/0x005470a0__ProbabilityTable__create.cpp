// FUNC_NAME: ProbabilityTable::create
int ProbabilityTable::create(int param_1, int* param_2)
{
    // Call virtual function at offset 0x220 (0x88th entry) on the source object
    // Returns the number of entries (count)
    uint count = (**(code **)(*param_2 + 0x220))();

    // TLS get, likely for debugging or thread context
    TlsGetValue(DAT_01139810);

    // Allocate a memory block of size 0x34 (52 bytes) with tag 0xb
    int* alloc = (int*)FUN_00aa2680(0x34, 0xb);
    *(short*)(alloc + 4) = 0x34; // Store size at offset 4

    // Get a global object (likely a manager or system)
    int* obj = (int*)FUN_00bece40();

    // Pointer to an int array at offset 0x1c
    int** intArrayPtr = (int**)(obj + 0x1c); // +0x1c
    // Current capacity of int array at offset 0x24 (lower 30 bits)
    uint intCapacity = *(uint*)(obj + 0x24) & 0x3fffffff;

    // Resize int array if needed (minimum capacity 4)
    if (intCapacity < 4) {
        uint newCap = intCapacity * 2;
        if (intCapacity == 2 || newCap < 4) {
            newCap = 4;
        }
        FUN_00aa4110(intArrayPtr, newCap, 4); // Realloc array of ints
    }

    // Set new capacity at offset 0x20
    *(uint*)(obj + 0x20) = 4;
    // Clear the first 4 ints of the int array
    *(*intArrayPtr + 0) = 0;
    *(*intArrayPtr + 1) = 0;
    *(*intArrayPtr + 2) = 0;
    *(*intArrayPtr + 3) = 0;

    // Pointer to float array at offset 0x28
    float** floatArrayPtr = (float**)(obj + 0x28); // +0x28
    // Current capacity of float array at offset 0x30 (lower 30 bits)
    uint floatCapacity = *(uint*)(obj + 0x30) & 0x3fffffff;

    // Resize float array to accommodate 'count' entries
    if ((int)floatCapacity < (int)count) {
        uint newCap = floatCapacity * 2;
        if ((int)newCap <= (int)count) {
            newCap = count;
        }
        FUN_00aa4110(floatArrayPtr, newCap, 4);
    }

    // Store count at offset 0x2c
    *(uint*)(obj + 0x2c) = count;

    // Initialize float array with equal probabilities (1.0 / count)
    uint i = 0;
    if (count > 3) {
        float inv = 1.0f / (float)count;
        // Process 4 at a time
        do {
            (*floatArrayPtr)[i] = inv;
            (*floatArrayPtr)[i + 1] = inv;
            (*floatArrayPtr)[i + 2] = inv;
            (*floatArrayPtr)[i + 3] = inv;
            i += 4;
        } while (i < count - 3);
    }
    // Handle remaining elements
    if (i < count) {
        float inv = 1.0f / (float)count;
        do {
            (*floatArrayPtr)[i] = inv;
            i++;
        } while (i < count);
    }

    // Store a constant at offset 0x10 (maybe total weight or default)
    *(float*)(obj + 0x10) = DAT_00e448e4;

    // Call a secondary initialization function with param_1, the new object, and source object
    FUN_00547220(param_1, obj, param_2);

    return (int)obj;
}