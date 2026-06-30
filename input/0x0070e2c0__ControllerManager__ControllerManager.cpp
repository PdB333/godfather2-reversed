// FUNC_NAME: ControllerManager::ControllerManager
#include <cstdint>

// Unknown globals from decompiled
extern uint32_t g_defaultValue1; // DAT_00e445ac
extern uint32_t g_defaultValue2; // _DAT_00d5780c
extern uint32_t g_defaultData; // DAT_012069c4 (possibly pointer to defaults)

// Forward declarations
void __thiscall FUN_0046c590(uint32_t _unknownParam);
void __thiscall FUN_004ab130();
void __thiscall FUN_00408900(void* _dest, void* _src, uint32_t _size);

class ControllerManager {
public:
    // Vtable pointer at offset 0x00
    // Additional vtable pointer at offset 0x3C
    // Another additional vtable at offset 0x48
    // ... 

    ControllerManager(uint32_t unknownParam); // Constructor
};

ControllerManager::ControllerManager(uint32_t unknownParam) {
    // Call base class constructor (likely for an inner struct/allocation)
    FUN_0046c590(unknownParam);

    // Set vtable pointer
    *(void**)this = (void*)0x00d61854; // PTR_FUN_00d61854

    // Setup secondary vtable pointers (multiple inheritance?)
    *(void**)((uint8_t*)this + 0x3C) = (void*)0x00d61844; // PTR_LAB_00d61844
    *(void**)((uint8_t*)this + 0x48) = (void*)0x00d61840; // PTR_LAB_00d61840

    // Initialize 16 sub-objects (likely controller slots)
    int32_t loopCount = 0xF; // originally 15? but loop runs 16 times
    do {
        FUN_004ab130(); // Sub-object constructor
        loopCount--;
    } while (loopCount >= 0);

    // Zero out various control flags
    *(uint8_t*)((uint8_t*)this + 0x88) = 0;
    *(uint8_t*)((uint8_t*)this + 0x241) = 0;
    *(uint8_t*)((uint8_t*)this + 0x242) = 0;

    // Zero out arrays (indices 0x84..0x87, 0x94)
    for (int i = 0; i < 4; ++i) {
        *(uint32_t*)((uint8_t*)this + 0x84 + i*4) = 0;
    }
    *(uint32_t*)((uint8_t*)this + 0x250) = 0; // 0x94

    // Initialize defaults for some fields
    uint32_t val1 = g_defaultValue1;
    uint32_t val2 = g_defaultValue2;
    *(uint32_t*)((uint8_t*)this + 0x244) = val1; // 0x91*4
    *(uint32_t*)((uint8_t*)this + 0x248) = val1; // 0x92*4
    *(uint32_t*)((uint8_t*)this + 0x24C) = val2; // 0x93*4
    *(uint32_t*)((uint8_t*)this + 0x2D8) = val2; // 0xB6*4
    *(uint32_t*)((uint8_t*)this + 0x320) = 0; // 200*4 = 0x320

    // Initialize array of 24 entries (each entry: 2 shorts + 1 int)
    // Starting at offset 0x324
    uint32_t* intArray = (uint32_t*)((uint8_t*)this + 0x324);
    for (int entry = 0; entry < 24; ++entry) {
        int idx = entry * 2; // each entry uses two int slots (8 bytes)
        // Write zero to first int
        intArray[idx] = 0;
        // Write two shorts inside next int
        uint16_t* lowShort = (uint16_t*)&intArray[idx+1];
        *lowShort = 0;
        uint16_t* highShort = lowShort + 1;
        *highShort = 0;
    }

    // If default data exists, copy 32KB to offset 0x3C
    if (g_defaultData != 0) {
        FUN_00408900((uint8_t*)this + 0x3C, &g_defaultData, 0x8000);
        val2 = g_defaultValue2; // refresh maybe not needed
    }

    // Initialize two arrays of 16 elements each
    // First array at offset 0x298 (each element 4 bytes?)
    // Second array at offset 0x884 (each element 4 bytes?)
    uint32_t* array1 = (uint32_t*)((uint8_t*)this + 0x298);
    uint32_t* array2 = (uint32_t*)((uint8_t*)this + 0x884);
    for (int i = 0; i < 16; ++i) {
        // Initialize element i of array1
        array1[i] = val2;
        array1[i + 0x11] = val2; // 17 ints ahead? Possibly two separate offsets?
        // Zero out element i of array1? Actually sets array1[-0x10]? That seems like an error.
        // Based on decompiled pattern:
        // puVar1[0x11] -> array1[i+0x11]
        // *puVar1 -> array1[i]
        // puVar1[-0x10] -> array1[i-0x10] (but that's negative index, likely meant as separate init)
        // We'll write it as given:
        *(uint32_t*)((uint8_t*)array1 + (i*4) - 0x40) = 0; // puVar1[-0x10] = 0
        // Initialize second array
        array2[i] = 0;
        array2[i + 0x10] = 0;
    }
}