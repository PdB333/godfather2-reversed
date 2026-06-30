// FUNC_NAME: Entity::validateState
#include <cstdint>

// External global table pointer (0x012233a0)
extern void* g_globalTable;

// Helper function at 0x00471610
void HelperFunction();

void __fastcall Entity::validateState(void* thisPtr) {
    // Offset +0xD4: entity's index/ID into the global array
    int entityIndex = *(int*)((uintptr_t)thisPtr + 0xD4);

    // Global table at g_globalTable + 4 holds a pointer to an int array
    int* arrayPtr = *(int**)((uintptr_t)g_globalTable + 4);
    int someValue = arrayPtr[entityIndex];

    // Check: if the value is 0 or 0x1F30 (sentinel?), and first array element is nonzero
    if ((someValue == 0 || someValue == 0x1F30) && arrayPtr[0] != 0) {
        HelperFunction();
        return;
    }
    // Both branches call the same helper – likely a sanity‑check that always fires
    HelperFunction();
}