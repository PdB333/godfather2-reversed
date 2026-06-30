// FUNC_NAME: EARS::Framework::Array::resize
int EARS::Framework::Array::resize(void* allocator, int* thisPtr)
{
    int* dataPtr;
    int defaultValue;
    uint newCount;
    int containerPtr;
    uint currentCapacity;
    int i;
    int remaining;

    // Virtual call to get the desired number of elements (e.g., from a source object)
    newCount = (**(code (***)(int*))(*thisPtr + 0x220))();

    // Get thread-local storage (likely allocator context)
    TlsGetValue(DAT_01139810);

    // Allocate the container structure (size 0x18, flags 0xb)
    containerPtr = FUN_00aa2680(0x18, 0xb);
    *(short*)(containerPtr + 4) = 0x18; // Element size (0x18? Actually 0xc per element, but this might be stride)

    // Get the internal buffer pointer and current capacity from the container
    containerPtr = FUN_00bef230(); // This might be a getter for the container's internal state
    dataPtr = (int*)(containerPtr + 8);
    currentCapacity = *(uint*)(containerPtr + 0x10) & 0x3fffffff;

    // If current capacity is less than needed, reallocate
    if ((int)currentCapacity < (int)newCount) {
        currentCapacity = currentCapacity * 2;
        if ((int)currentCapacity <= (int)newCount) {
            currentCapacity = newCount;
        }
        FUN_00aa4110(dataPtr, currentCapacity, 0xc); // Reallocate with element size 0xc
    }

    defaultValue = DAT_00e2b1a4; // Default value for each element (likely 0 or -1)
    *(uint*)(containerPtr + 0xc) = newCount; // Store the new count

    // Initialize the buffer with default values (each element is 0xc bytes)
    if (3 < (int)newCount) {
        i = 0;
        remaining = (newCount - 4 >> 2) + 1; // Process 4 elements per iteration
        uint processed = remaining * 4;
        do {
            *(int*)(i + *dataPtr) = defaultValue;
            *(int*)(i + 4 + *dataPtr) = defaultValue;
            *(int*)(i + 0xc + *dataPtr) = defaultValue;
            *(int*)(i + 0x10 + *dataPtr) = defaultValue;
            *(int*)(i + 0x18 + *dataPtr) = defaultValue;
            *(int*)(i + 0x1c + *dataPtr) = defaultValue;
            *(int*)(i + 0x24 + *dataPtr) = defaultValue;
            *(int*)(i + 0x28 + *dataPtr) = defaultValue;
            i += 0x30; // Advance by 4 elements (4 * 0xc = 0x30)
            remaining--;
        } while (remaining != 0);
    }

    // Handle remaining elements (less than 4)
    if (processed < newCount) {
        i = processed * 0xc;
        remaining = newCount - processed;
        do {
            *(int*)(i + *dataPtr) = defaultValue;
            *(int*)(i + 4 + *dataPtr) = defaultValue;
            i += 0xc;
            remaining--;
        } while (remaining != 0);
    }

    // Call another initialization/registration function
    FUN_00548440(allocator, thisPtr);

    return containerPtr;
}