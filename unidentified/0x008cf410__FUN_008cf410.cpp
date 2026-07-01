// FUNC_NAME: SomeManager::checkAndExecuteAction
// Function address: 0x008cf410
// Purpose: Compares a stored identifier (offset +0x2c) with a global identifier.
//          If they match, resolves a sub-object through a complex pointer chain (offset +0x8)
//          and calls a virtual method at vtable offset 0x58 on that sub-object.
//          Returns the original identifier on failure.

#include <cstdint>

// Forward declaration of external helper – returns a global identifier (e.g., current player ID)
extern int __cdecl getGlobalIdentifier(void); // FUN_0042b400

// Declare a base class for the sub-object (vtable-based)
class SubObject {
public:
    // Virtual method at vtable offset 0x58 (slot 22 for 4-byte vtable entries)
    virtual int virtualMethodAt0x58() = 0;
};

class SomeManager {
public:
    // Offsets inferred from decompilation:
    // +0x08: pointer to a vtable-like structure or interface table
    // +0x2c: stored identifier (e.g., player slot, mission ID)

    int __thiscall checkAndExecuteAction() {
        int storedId = *(int*)((uint8_t*)this + 0x2c);       // Load stored identifier
        int globalId = getGlobalIdentifier();                 // Get global identifier

        if (storedId == globalId) {
            // Complex pointer chain to retrieve a sub-object pointer:
            //  - Read pointer at this+0x8
            //  - Dereference that pointer (expects an int**) to get a pointer to a vtable table
            //  - Add 8 to that pointer, treat as pointer to function pointer table
            //  - Add 0x24 (offset 9 entries? 0x24/4=9) to get a specific function pointer
            //  - Call that function; it returns a SubObject pointer
            SubObject* sub = reinterpret_cast<SubObject*>(
                (*(int*(__thiscall**)(void))(
                    (uint8_t*)(*(uint8_t*)(*(uint8_t*)this + 8) + 8) + 0x24
                ))()
            );

            if (sub != nullptr) {
                // Call virtual method at vtable offset 0x58 on the sub-object
                return sub->virtualMethodAt0x58();
            }
        }

        return storedId;  // Return the stored identifier if no action taken
    }
};