// FUNC_NAME: WorldObjectManager::initializeSlot
// Function address: 0x00458d10
// Role: Initializes a slot in the object manager's slot array.
// Uses EDI (slotIndex) as implicit register parameter, this in ECX.
// Parameters: slotIndex (edi), param2, param3, param4 (likely transform data)

#include <cstdint>

class WorldObjectManager {
public:
    // SlotData structure: each slot points to an object with fields
    struct SlotData {
        uint8_t unknown_0x00[0x200];  // +0x00 to +0x1FF
        uint8_t activeFlag;          // +0x200
        uint8_t padding_0x201[0x201 - 0x200 - 1];
        uint32_t transformPart0;     // +0xD0
        uint32_t transformPart1;     // +0xD4
    };

    // Assumed structure for the manager itself (offset 8 is array of pointers)
    struct ManagerData {
        uint8_t unknown_0x00[0x08];
        SlotData* slotPtrs[2];      // +0x08 (2 slots in this example)
    };

    void __thiscall initializeSlot(int slotIndex, int param2, int param3, uint64_t param4) {
        // unaff_EDI is slotIndex, assumed < 2 based on caller loop
        if (slotIndex >= 2) {
            return;
        }

        // Retrieve string identifier from in_EAX (some two-field struct)
        // *in_EAX and in_EAX[1] are likely resource IDs
        // The function FUN_004d3ca0 loads a string and returns a pointer (puVar1)
        // along with a destructor function pointer (local_4)
        void (*stringDealloc)(void*) = nullptr;
        char* loadedString = nullptr;
        // Synthesized: FUN_004d3ca0 returns both via output params or a struct
        // Original: FUN_004d3ca0(*in_EAX, in_EAX[1], &DAT_00e31a8c, 4);
        // We assume it fills local_10 (loadedString) and local_4 (dealloc)
        // For reconstruction, we'll write as:
        loadedString = (char*)FUN_004d3ca0( /* params */);
        // The dealloc pointer is stored in local_4, set by the same call (not shown in decompiler)
        // We'll simulate: 
        stringDealloc = (void (*)(void*))FUN_004d3ca0_getDealloc();

        // If string is null, use default string
        const char* objName = loadedString ? loadedString : "CANNONBALL_DEFAULT"; // DAT_0120546e

        // Try to find an object by name
        void* foundObject = (void*)FUN_00456070(objName); // returns handle/pointer

        // Get pointer to the slot's object
        SlotData* slot = reinterpret_cast<ManagerData*>(this)->slotPtrs[slotIndex];

        if (foundObject == nullptr) {
            // Object not found, set active flag to 1
            slot->activeFlag = 1;
        } else {
            // Reset local transform structure
            int local_20[3] = {0, 0, 0};
            void (*transformCallback)(int) = nullptr;

            // Seed random or initialize math
            FUN_004a8460();

            // Compute transform from parameters
            FUN_00458110(local_20, param4, param2, param3);

            // Copy transform data from found object into slot
            slot->transformPart0 = *(uint32_t*)((uint8_t*)foundObject + 0x34);
            slot->transformPart1 = *(uint32_t*)((uint8_t*)foundObject + 0x3C);

            // If local_20[0] is non-zero, call callback with it
            if (local_20[0] != 0) {
                if (transformCallback) {
                    transformCallback(local_20[0]);
                }
            }
        }

        // Free the loaded string if originally allocated
        if (loadedString && stringDealloc) {
            stringDealloc(loadedString);
        }
    }

private:
    // Declare external functions (from game binary)
    void* FUN_004d3ca0(int id1, int id2, void* buffer, int size);
    void* FUN_004d3ca0_getDealloc(); // synth, not real
    int FUN_00456070(const char* name);
    void FUN_004a8460();
    void FUN_00458110(int* out, uint64_t param4, int param2, int param3);
};