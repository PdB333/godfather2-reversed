// FUNC_NAME: ValuePair::compareValues
// Function address: 0x00591f90
// Compares two values (constant floats or function results) and returns comparison flags.
// The class has a pointer at +0x8 to a pair of Value objects (each 8 bytes: type byte, padding, short index, float constant).
// param_2 is a context/result buffer (at least 4 pointers wide).

int __thiscall ValuePair::compareValues(void* thisPtr, uint32_t* pContext)
{
    // Get the pair of values from this+0x8
    // Structure at this+0x8 is a pointer to a struct with two char* (Value pointers)
    char** ppValuePair = *(char***)((char*)thisPtr + 8);
    // First value pointer
    char* pValue1 = ppValuePair[0];
    // Second value pointer
    char* pValue2 = ppValuePair[1];

    float val1, val2;
    uint32_t funcResult1, funcResult2; // used for bitfield extraction

    // Process first value
    if (*pValue1 == '\n') {
        // Function reference: short index at offset 2
        int16_t index = *(int16_t*)(pValue1 + 2);
        if (index >= 0 && index < g_functionTableSize) {
            // g_functionTable is an array of function pointers (size 0xc each)
            void* func = *(void**)(g_functionTableBase + 4 + index * 0xc);
            if (func != nullptr) {
                // Call function with context, index, and output float
                ((void (*)(uint32_t, int16_t, float*))func)(*pContext, index, &val1);
            }
        }
    } else {
        // Constant float at offset 4
        val1 = *(float*)(pValue1 + 4);
    }

    // Process second value
    if (*pValue2 == '\n') {
        int16_t index = *(int16_t*)(pValue2 + 2);
        if (index >= 0 && index < g_functionTableSize) {
            void* func = *(void**)(g_functionTableBase + 4 + index * 0xc);
            if (func != nullptr) {
                // Function returns a pointer that is used as bitfield; store in funcResult2
                funcResult2 = (uint32_t)((void (*)(uint32_t, int16_t, float*))func)(*pContext, index, &val2);
            }
        }
    } else {
        val2 = *(float*)(pValue2 + 4);
        funcResult2 = 0; // not used if constant
    }

    // Build comparison flags byte
    uint8_t flags = 0;
    if (val1 == val2) {
        flags |= 0x40; // bit 6: equal
    }
    if (isnan(val1) || isnan(val2)) {
        flags |= 0x04; // bit 2: NaN
    }
    flags |= 0x02; // bit 1: always set? (from code: 2U)
    if (val1 < val2) {
        flags |= 0x01; // bit 0: less than
    }

    // Combine with high 16 bits of funcResult2 (if function was called)
    uint32_t result = ((funcResult2 >> 16) & 0xFFFF) << 8 | flags;

    if (val1 != val2) {
        return result << 8; // shift left by 8 bits? Actually code returns (uint)uVar2 << 8
    } else {
        // Equal: store this pointer in pContext[3]
        pContext[3] = (uint32_t)thisPtr;
        // Combine result with a 1 in the lowest byte? CONCAT31(uVar2,1) likely means combine 3 bytes of uVar2 with 1
        return (result & 0xFFFFFF) | (1 << 24); // assuming CONCAT31 puts 1 in the highest byte
    }
}