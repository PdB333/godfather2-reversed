// FUNC_NAME: ControllerManager::ControllerManager
// Function address: 0x00908820
// Role: Constructor for ControllerManager singleton.
// Initializes vtable pointers, clears a 16-entry array (each 8 bytes) at offset 0x14,
// sets two final fields, and stores the global pointer.

#include <cstdint>

// Forward declaration of the initialization function called from the constructor.
void sub_908110(void);  // TODO: identify this function, possibly ControllerManager::init()

class ControllerManager {
public:
    // Static singleton pointer (DAT_0112ff6c)
    static ControllerManager* s_pSingleton;

    // Vtable pointer at +0x00
    void* vtable0;

    // +0x04: some flag/count, initialized to 1
    int32_t field_0x04;

    // +0x08: initialized to 0
    int32_t field_0x08;

    // +0x0C: secondary vtable pointer (overwritten)
    void* vtable1;

    // +0x10: tertiary vtable pointer (overwritten)
    void* vtable2;

    // +0x14: array of 16 entries, each 8 bytes
    // Each entry: 4 bytes (pointer?), 2 bytes, 2 bytes
    struct ControllerSlot {
        uint32_t unknown0; // +0x00
        uint16_t unknown1; // +0x04
        uint16_t unknown2; // +0x06
    } controllerSlots[16]; // occupies 0x14 to 0x93

    // +0x94: set to 0
    int32_t field_0x94;

    // +0x98: set to 1
    int32_t field_0x98;

    // Total size at least 0x9C (156 bytes)

    __thiscall ControllerManager() {
        // Initialize non-array fields
        field_0x04 = 1;
        field_0x08 = 0;

        // Set vtable pointers (order may indicate multiple inheritance)
        vtable1 = &PTR_LAB_00d83010;   // temporary, overwritten
        vtable2 = &PTR_LAB_00e30fe0;   // temporary, overwritten

        vtable0 = &PTR_FUN_00d83028;   // primary vtable

        // Final assignments for secondary vtable pointers
        vtable1 = &PTR_LAB_00d83024;
        vtable2 = &PTR_LAB_00d83014;

        // Clear the controllerSlots array (16 entries * 8 bytes = 128 bytes)
        uint32_t* pCur = reinterpret_cast<uint32_t*>(controllerSlots);
        int32_t loopCount = 15;  // 0xF
        do {
            *pCur = 0;                        // zero 4 bytes
            *reinterpret_cast<uint16_t*>(pCur + 1) = 0;      // zero next 2 bytes (offset 4)
            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(pCur) + 6) = 0; // zero bytes at offset 6
            pCur += 2;                         // advance 8 bytes
            loopCount--;
        } while (loopCount >= 0);

        // Fields after the array
        field_0x94 = 0;
        field_0x98 = 1;

        // Store this as the global singleton
        s_pSingleton = this;

        // Call initialization
        sub_908110();  // TODO: likely ControllerManager::init() or similar
    }
};

// Define the global singleton pointer
ControllerManager* ControllerManager::s_pSingleton = nullptr;