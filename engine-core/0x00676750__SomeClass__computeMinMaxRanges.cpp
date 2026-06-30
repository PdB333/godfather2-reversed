//FUNC_NAME: SomeClass::computeMinMaxRanges
// Function address: 0x00676750
// Role: Computes min and max of two integer arrays and stores them in the object at offsets +0x38, +0x3c, +0x40, +0x44.
// Calling convention: __thiscall (this in ECX, first array pointer in EAX, second array pointer and last index on stack)
// Note: The first array pointer is passed in EAX (not as a regular parameter), but we include it as a parameter for clarity.

void __thiscall SomeClass::computeMinMaxRanges(int* array1, int* array2, int lastIndex) {
    int min1, max1, min2, max2;

    // Process first array (passed in EAX originally)
    min1 = max1 = array1[0];
    for (int i = 1; i <= lastIndex; i++) {
        int val = array1[i];
        if (val < min1) min1 = val;
        if (val > max1) max1 = val;
    }

    // Process second array (param_2)
    min2 = max2 = array2[0];
    for (int i = 1; i <= lastIndex; i++) {
        int val = array2[i];
        if (val < min2) min2 = val;
        if (val > max2) max2 = val;
    }

    // Store results in object fields
    *(int*)((int)this + 0x38) = min1; // +0x38: first min
    *(int*)((int)this + 0x3c) = max1; // +0x3c: first max
    *(int*)((int)this + 0x40) = min2; // +0x40: second min
    *(int*)((int)this + 0x44) = max2; // +0x44: second max
}