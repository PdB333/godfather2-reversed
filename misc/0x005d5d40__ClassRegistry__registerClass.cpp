// FUNC_NAME: ClassRegistry::registerClass

#include <cstdint>

// Global singleton pointer to the class registry (0x01206880)
extern int* g_pClassRegistry;

// Global multiplier for class entry size (0x012056bc)
extern int g_nClassEntryMultiplier;

// Global pointer to a vtable pointer (0x01126cf8)
extern void* g_pClassVTable;

// Some data blob (0x0119eac0)
extern char g_aClassData[0x10];

// External function: Registers a class entry (0x005d7490)
extern void RegisterClassEntry(int type, uint64_t combinedData, int extraSize1, int extraSize2);

// Registers a new class into the global class registry.
// Stores the class's vtable pointer into the registry's dynamic array
// and then calls the registration function with class-specific data.
void ClassRegistry::registerClass()
{
    // Calculate size offset (28 bytes per class entry)
    int sizeOffset = g_nClassEntryMultiplier * 0x1c;

    // Pointer to the dynamic array of vtable pointers in the registry (at offset +0x14)
    int** ppVtableArray = (int**)((char*)g_pClassRegistry + 0x14);

    // Store the address of the global vtable pointer into the current array slot
    (**ppVtableArray) = (int)&g_pClassVTable;

    // Advance the array pointer to the next slot (each slot is 4 bytes)
    (*ppVtableArray)++;

    // Combine size offset (high 32 bits) and class data address (low 32 bits) into a 64-bit value
    uint64_t combined = ((uint64_t)sizeOffset << 32) | (uint64_t)&g_aClassData;

    // Call the registration function with type 4, the combined data, and two sizes (0x10, 0x1c)
    RegisterClassEntry(4, combined, 0x10, 0x1c);
}