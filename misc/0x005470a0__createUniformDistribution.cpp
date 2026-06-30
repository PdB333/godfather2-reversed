// FUNC_NAME: createUniformDistribution
int __stdcall createUniformDistribution(void* parentObj, int* vtablePtr)
{
    // Retrieve the count from a virtual function on the vtable object
    uint32_t count = (**(uint32_t (**)(void))(*vtablePtr + 0x220))();

    // Thread-local storage access (likely for memory context)
    TlsGetValue(DAT_01139810);

    // Allocate a 0x34-byte block from a custom allocator (tag 0xb)
    int* distBlock = (int*)FUN_00aa2680(0x34, 0xb);
    *(uint16_t*)(distBlock + 4) = 0x34;  // store allocation size

    // Get a reference to a per-thread distribution manager or context
    int* context = (int*)FUN_00bece40();

    // --- Initialize the first dynamic array (int array) ---
    // context+0x1c holds a pointer to a dynamic array structure
    int* intArrayPtr = (int*)(context + 0x1c);
    uint32_t intArrayCapacity = *(uint32_t*)(context + 0x24) & 0x3fffffff; // lower 30 bits

    // Grow capacity to at least 4 (if less)
    if (intArrayCapacity < 4) {
        uint32_t newCap = intArrayCapacity * 2;
        if (intArrayCapacity == 2 || newCap < 4) {
            newCap = 4;
        }
        FUN_00aa4110(intArrayPtr, newCap, 4);
    }

    // Set array size to 4 (overwrites previous capacity?)
    *(uint32_t*)(context + 0x20) = 4;

    // Clear first 4 elements of the int array 
    int* intData = (int*)*intArrayPtr;
    intData[0] = 0;
    intData[1] = 0;
    intData[2] = 0;
    intData[3] = 0;

    // --- Initialize the second dynamic array (float array) for weights ---
    int* floatArrayPtr = (int*)(context + 0x28);
    uint32_t floatArrayCapacity = *(uint32_t*)(context + 0x30) & 0x3fffffff;

    // Grow if necessary to accommodate 'count'
    if ((int)floatArrayCapacity < (int)count) {
        uint32_t newCap = floatArrayCapacity * 2;
        if ((int)newCap <= (int)count) {
            newCap = count;
        }
        FUN_00aa4110(floatArrayPtr, newCap, 4);
    }

    // Set the size of the float array
    *(uint32_t*)(context + 0x2c) = count;

    // Fill the float array with uniform probability (1.0f / count)
    float* floatData = (float*)*floatArrayPtr;
    if ((int)count > 3) {
        float invCount = 1.0f / (float)count; // Note: EA often uses a trick for unsigned->float conversion
        uint32_t i = 0;
        do {
            floatData[i + 0] = invCount;
            floatData[i + 1] = invCount;
            floatData[i + 2] = invCount;
            floatData[i + 3] = invCount;
            i += 4;
        } while (i < count - 3);
    }

    // Handle remaining elements
    float invCount = 1.0f / (float)count; // using direct cast (EA's trick handled by compiler)
    for (uint32_t i = count & ~3; i < count; ++i) {
        floatData[i] = invCount;
    }

    // Set a default probability threshold or scale
    *(float*)(context + 0x10) = DAT_00e448e4; // constant, likely a default value

    // Attach the distribution to the parent object
    FUN_00547220(parentObj, context, vtablePtr);

    return (int)context; // return pointer to the distribution structure
}