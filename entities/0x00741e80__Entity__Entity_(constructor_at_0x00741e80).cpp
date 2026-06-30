// FUNC_NAME: Entity::Entity (constructor at 0x00741e80)

#include <cstdint>

// Reconstructed C++ for The Godfather 2 (EA EARS engine)
// Fields offsets (relative to 'this', 4-byte indices):
//   +0x00: vtable pointer
//   +0x48 (index 0x12): pointer to internal data (owner/handle)
//   +0x50 (index 0x14): pointer to child/managed object
//   +0x54 (index 0x15): flag (cleared)
//   +0x58 (index 0x16): value copied from global manager+0x34
//   +0x5C (index 0x17): object reference (from global)
//   +0x60 (index 0x18): integer (initially 0)

class Entity {
public:
    Entity(void* arg0, void* arg1) {
        // Base class initialisation (likely EARS::Object::ctor or similar)
        FUN_004ac120(arg0, arg1);

        // Set vtable to this type's global vtable
        vtable = &VTable_Entity;

        // Clear field at +0x60
        field_60 = 0;

        // Resolve parent/internal pointer using container_of pattern
        int* internalPtr;
        if (field_48 == 0) {
            internalPtr = nullptr;
        } else {
            // The field at +0x48 points to some sub-object; subtract 0x48 to get its enclosing base
            internalPtr = reinterpret_cast<int*>(field_48 - 0x48);
        }

        // Call a virtual function on the resolved internal object (likely to register/generate a unique ID)
        // Hash 0x55859efa and a local bool pointer are passed
        char result;
        if (internalPtr != nullptr) {
            result = (**(char(__thiscall**)(int, void*))(*internalPtr + 0x10))(0x55859efa, &result);
        } else {
            result = 0;
        }

        // Reset field (maybe redundancy)
        field_60 = 0;
        // Clear another flag
        field_54 = 0;
        // Conditionally set field_50 based on result
        field_50 = (result != 0) ? unaff_retaddr : 0;   // unaff_retaddr is an unknown register value (likely a previous return address)

        // Query a global manager (e.g., GameManager or SimulationManager)
        int managerPtr = FUN_00471610();
        field_58 = *reinterpret_cast<uint32_t*>(managerPtr + 0x34);

        // If field_50 is valid, call a virtual function on that object
        if (field_50 != 0) {
            (**(void(__thiscall**)(int, int, int))(*reinterpret_cast<uint32_t*>(field_50) + 0x290))(0, 1);
        }

        // Allocate memory (size 0x2C) – possibly for an internal component or data
        void* alloc = FUN_007f63e0(0x2C); // Returns a pointer to allocated memory

        // Set field_5C based on a global variable
        if (field_50 != 0) {
            uint32_t uVar3 = FUN_0043b870(DAT_01130950); // Global handle or pointer
            field_5C = uVar3;
        } else {
            field_5C = 0;
        }

        // Constructor returns 'this' implicitly
    }

private:
    void* vtable;                           // +0x00
    // ... typical base class fields ...
    uint32_t field_48;                      // +0x48
    uint32_t field_50;                      // +0x50
    uint32_t field_54;                      // +0x54
    uint32_t field_58;                      // +0x58
    uint32_t field_5C;                      // +0x5C
    uint32_t field_60;                      // +0x60
};

// External function declarations (based on observed use)
extern void FUN_004ac120(void*, void*);
extern int FUN_00471610(void);                          // Possibly getSimulationManager() or getGameManager()
extern void* FUN_007f63e0(int size);                    // operator new / allocator
extern uint32_t FUN_0043b870(uint32_t global);          // Global resource lookup
extern uint32_t DAT_01130950;                           // Some global symbol
extern void* VTable_Entity;                             // VTable at address 0x00d63b48
```