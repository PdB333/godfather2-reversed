// Xbox PDB: EARS_Godfather_LightingTODMessage_GetClassName
//FUNC_NAME: LightingTODManager::LightingTODManager
// Function address: 0x0082da00
// Constructor for the LightingTODManager class.
// Initializes multiple vtable pointers, registers a LightingTODMessage,
// allocates a 0x40-byte buffer, and sets up default string.

#include <cstdint>

class LightingTODManager {
public:
    // Vtable pointers (multiple inheritance)
    void* vtable1;          // +0x00
    uint32_t field_4;       // +0x04
    uint32_t field_8;       // +0x08
    uint32_t field_C;       // +0x0C
    uint32_t field_10;      // +0x10
    uint32_t field_14;      // +0x14
    uint32_t field_18;      // +0x18
    uint32_t field_1C;      // +0x1C
    uint8_t field_20;       // +0x20 (byte)
    uint32_t field_24;      // +0x24
    void* vtable2;          // +0x30 (offset 0xC * 4)
    // ... other fields up to offset 0x90
    void* vtable3;          // +0x90 (offset 0x24 * 4)
    uint32_t field_94;      // +0x94
    void* buffer;           // +0x98 (allocated 0x40 bytes)
    uint32_t field_9C;      // +0x9C
    uint32_t field_A0;      // +0xA0 (initialized to 0x10)
    // ... more fields

    // Constructor
    LightingTODManager() {
        // Zero-initialize fields 1-7 (offsets 0x04 to 0x1C)
        field_4 = 0;
        field_8 = 0;
        field_C = 0;
        field_10 = 0;
        field_14 = 0;
        field_18 = 0;
        field_1C = 0;

        // Set byte at offset 0x20 to 1
        field_20 = 1;

        // Set primary vtable
        vtable1 = &PTR_FUN_00d738e0; // External vtable symbol

        // Set field at offset 0x24 to 1
        field_24 = 1;

        // Call global initialization function (likely base class or static init)
        FUN_008334a0();

        // Set secondary vtable at offset 0x30
        vtable2 = &PTR_LAB_00d73688; // External vtable/data symbol

        // Call another initialization function
        FUN_009d3650();

        // Set tertiary vtable at offset 0x90
        vtable3 = &PTR_FUN_00d73788; // External vtable symbol

        // Clear field at offset 0x94
        field_94 = 0;

        // Allocate 0x40-byte buffer
        buffer = (void*)FUN_009c8e80(0x40);

        // Initialize fields at offsets 0x9C and 0xA0
        field_9C = 0;
        field_A0 = 0x10;

        // Local variables for message registration
        int local_10[3] = {0, 0, 0};
        void (*cleanupFunc)(int) = nullptr;

        // Register LightingTODMessage with sequence "Sequence"
        FUN_004d4ad0(local_10, &DAT_00e2f0b0, "LightingTODMessage", "Sequence");
        FUN_004d3e20(local_10);

        // Get default string if field_4 is null
        const char* str = (const char*)field_4;
        if (str == nullptr) {
            str = &DAT_0120546e; // Default string
        }

        // Convert string to some ID/handle and store at offset 0x0C
        field_C = FUN_004dafd0(str);

        // Cleanup if needed
        if (local_10[0] != 0) {
            cleanupFunc(local_10[0]);
        }
    }
};

// External function declarations (stubs)
extern void* PTR_FUN_00d738e0;
extern void* PTR_LAB_00d73688;
extern void* PTR_FUN_00d73788;
extern void FUN_008334a0();
extern void FUN_009d3650();
extern void* FUN_009c8e80(uint32_t size);
extern void FUN_004d4ad0(int* local, void* data, const char* msg, const char* seq);
extern void FUN_004d3e20(int* local);
extern uint32_t FUN_004dafd0(const char* str);
extern char DAT_00e2f0b0; // Some data
extern char DAT_0120546e; // Default string