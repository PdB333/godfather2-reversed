// FUNC_NAME: GameManager::GameManager
// Address: 0x005e42a0
// Role: Constructor for the game manager (singleton). Initializes large object, sets vtable,
// zeros a block of fields (offsets +0x6010 to +0x6040), assigns global pointer, and releases
// any previously allocated memory at specific offset slots (likely resource handles).

#include <cstdlib>

// Forward declare the vtable pointer (defined elsewhere)
extern void* PTR_FUN_00e3f6a4;

// Global singleton pointer
extern GameManager* gGameManager;

class GameManager {
public:
    GameManager() {
        // Set vtable pointer (offset +0x00)
        *(void**)this = &PTR_FUN_00e3f6a4;

        // Zero out an array of 13 integer-sized fields starting at offset +0x6010
        // Offsets in int32 units: 0x1804 through 0x1810 inclusive
        int* fields = reinterpret_cast<int*>(this) + 0x1804;
        for (int i = 0; i <= 0xC; ++i) { // 13 fields: 0x1804..0x1810
            fields[i] = 0;
        }

        // Assign the global singleton pointer
        gGameManager = this;

        // Release and nullify two pointer fields at offsets +0x6020 and +0x602c
        // (int32 units 0x1808 and 0x180b)
        free(reinterpret_cast<void**>(this)[0x1808]);
        reinterpret_cast<void**>(this)[0x1808] = nullptr;
        reinterpret_cast<int*>(this)[0x180a] = 0; // field at +0x6028
        reinterpret_cast<int*>(this)[0x180c] = 0; // field at +0x6030

        free(reinterpret_cast<void**>(this)[0x180b]);
        reinterpret_cast<void**>(this)[0x180b] = nullptr;
        reinterpret_cast<int*>(this)[0x180d] = 0; // field at +0x6034
    }
};