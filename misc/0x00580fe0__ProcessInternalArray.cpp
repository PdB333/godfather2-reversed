// FUNC_NAME: ProcessInternalArray
#include <cstdint>

void ProcessInternalArray(int32_t* pElements, int32_t* pContainer) {
    // Unidentified initialization call (likely global setup)
    FUN_00581080();

    int32_t i = 0;
    int32_t count = *(int32_t*)(pContainer + 0x1c);
    if (count > 0) {
        do {
            FUN_00581220(pElements);
            i++;
            pElements = (int32_t*)((uint8_t*)pElements + 0x20); // advance to next element (32 bytes each)
        } while (i < count);
    }
}