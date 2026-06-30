// FUNC_NAME: DebugMemoryManager::DebugMemoryManager
// Address: 0x006d4dd0
// Constructor for a debug memory manager that initializes a global singleton and fills a debug array with sentinel values.
// The class uses multiple inheritance (multiple vtable pointers at offsets 0x00, 0x3C, 0x48, 0x50, 0x58, 0x5C?).
// The large array of 4-word groups from offset 0xB4 to 0x220 is filled with debug markers for memory tracking.

#include <cstdint>

// Forward declarations of vtable globals
extern void* PTR_LAB_00d5f3d0;
extern void* PTR_FUN_00d5f3f0;
extern void* PTR_LAB_00d5f3e0;
extern void* PTR_LAB_00d5f3dc;
extern void* PTR_LAB_00d5f3d8;
extern void* PTR_LAB_00d5f3d4;

// External global that holds the singleton pointer
extern DebugMemoryManager* DAT_0112a878;

// External data for initialization
extern uint32_t _DAT_00d5780c;
extern uint32_t DAT_00d5f00c;
extern uint32_t DAT_00e447a4;

// Forward declaration of base class constructor
void FUN_00473840(uint32_t param);

// Forward declaration of an internal init function
void FUN_00473750(void);

// Structure representing a group of 4 debug sentinels (16 bytes)
struct DebugSentinelGroup {
    uint32_t sentinel1;  // 0xBADBADBA
    uint32_t sentinel2;  // 0xBEEFBEEF
    uint32_t sentinel3;  // 0xEAC15A55
    uint32_t sentinel4;  // 0x91100911
};

class DebugMemoryManager {
public:
    // Constructor
    DebugMemoryManager(uint32_t param) {
        // Call base class constructor
        FUN_00473840(param);

        // Set up vtables (multiple inheritance)
        // Offset 0x58: first vtable?
        this->vtable1 = &PTR_LAB_00d5f3d0;           // +0x58
        // Store this as global singleton
        DAT_0112a878 = this;
        // Primary vtable at offset 0x00
        this->primaryVtable = &PTR_FUN_00d5f3f0;     // +0x00
        this->vtable2 = &PTR_LAB_00d5f3e0;           // +0x3C (offset 0xF * 4)
        this->vtable3 = &PTR_LAB_00d5f3dc;           // +0x48 (offset 0x12 * 4)
        this->vtable4 = &PTR_LAB_00d5f3d8;           // +0x50 (offset 0x14 * 4)
        this->vtable5 = &PTR_LAB_00d5f3d4;           // +0x58 (offset 0x16 * 4) - overwrites vtable1

        // Internal initialization
        FUN_00473750();

        // Fill the debug sentinel array (starts at offset 0xB4 = index 0x2D)
        // The array contains 23 groups of 4 sentinels (indices 0x2D to 0x88)
        for (int i = 0; i < 23; ++i) {
            debugSentinels[i].sentinel1 = 0xBADBADBA;
            debugSentinels[i].sentinel2 = 0xBEEFBEEF;
            debugSentinels[i].sentinel3 = 0xEAC15A55;
            debugSentinels[i].sentinel4 = 0x91100911;
        }

        // Initialize additional fields after the sentinel array
        // Offset 0xA0 (index 0x28)
        this->field_0xA0 = _DAT_00d5780c;
        // Offset 0xA4 (index 0x29)
        this->field_0xA4 = DAT_00d5f00c;
        // Offset 0xA8 (index 0x2A)
        this->field_0xA8 = 0;
        // Offset 0xAC (index 0x2B)
        this->field_0xAC = DAT_00e447a4;
    }

    // Placeholder members based on offsets
    void* primaryVtable;                 // +0x00
    // ... other members ...
    void* vtable1;                       // +0x58 (first set)
    void* vtable2;                       // +0x3C
    void* vtable3;                       // +0x48
    void* vtable4;                       // +0x50
    void* vtable5;                       // +0x58 (final, overwrites vtable1)
    uint32_t field_0xA0;                 // +0xA0
    uint32_t field_0xA4;                 // +0xA4
    uint32_t field_0xA8;                 // +0xA8
    uint32_t field_0xAC;                 // +0xAC
    DebugSentinelGroup debugSentinels[23]; // +0xB4 to +0x220 (indices 0x2D to 0x88)
};