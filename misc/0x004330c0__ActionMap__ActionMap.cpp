// FUNC_NAME: ActionMap::ActionMap
// Address: 0x004330c0
// This constructor initializes the ActionMap singleton, allocates a large mapping table (0x3b00 bytes),
// stores global reference values, and registers a default action binding into a global binding table.

#include <cstdint>

// Forward declarations
extern void* DefaultAllocator(); // FUN_009c8f80
extern void* ActionMapInit(void* block, ...); // FUN_0042c1f0 – placement init for the mapping table
extern void HandleActionBindingError(); // FUN_00609bf0 – error handler for invalid key codes

// Global state
extern ActionMap* g_pActionMapSingleton; // DAT_012233a8
extern uint32_t g_someGlobal1; // DAT_00e4494c
extern uint32_t g_someGlobal2; // DAT_00e4474c

// Global action binding table: each entry is 12 bytes.
// Layout: actionId1 (4B), actionId2 (4B), keyCode (4B, low byte used)
struct ActionBinding {
    uint32_t action1;  // +0x00 - first action identifier
    uint32_t action2;  // +0x04 - second action identifier
    uint32_t keyCode;  // +0x08 - virtual key code (only low byte significant, e.g. 0x80)
};
static_assert(sizeof(ActionBinding) == 12, "ActionBinding must be 12 bytes");

extern ActionBinding g_actionBindings[32]; // DAT_01222330 – up to 32 entries
extern int32_t g_numActionBindings;        // DAT_012224a8 – current entry count

class ActionMap {
public:
    ActionMap(void* allocator = nullptr);
    virtual ~ActionMap() = default; // vtable at offset0 = PTR_FUN_00e30bf0

private:
    // Layout:
    // +0x00: vtable pointer (set by constructor)
    // +0x04: pointer to allocated mapping table (0x3b00 bytes)
    void* m_pMappingTable;
};

ActionMap::ActionMap(void* allocator) {
    g_pActionMapSingleton = this;
    *reinterpret_cast<void***>(this) = &ActionMap_vtable; // PTR_FUN_00e30bf0

    // Obtain default allocator if none provided
    if (allocator == nullptr) {
        allocator = DefaultAllocator();
    }

    // Allocation parameters: alignment, count, flags
    int32_t align = 2;   // local_c
    int32_t count = 0x20; // local_8 = 32 (max entries?)
    int32_t flags = 0;    // local_4

    // Call allocator's allocate method (first virtual function)
    void* newBlock = reinterpret_cast<void*(__thiscall*)(void*, uint32_t, int32_t*)>(
        *(*reinterpret_cast<void***>(allocator)))(allocator, 0x3b00, &align);

    // Initialize the allocated memory (placement new / constructor)
    if (newBlock != nullptr) {
        // Additional arguments (param_2..param_8) are passed through but not stored locally
        newBlock = ActionMapInit(newBlock, flags, /* retaddr? */, 
                                 /* extra args omitted */);
    }

    this->m_pMappingTable = newBlock;

    // Store global reference values at fixed offsets in the mapping table
    *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(m_pMappingTable) + 0x39f0) = g_someGlobal1;
    *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(m_pMappingTable) + 0x39f4) = g_someGlobal2;

    // Scan existing bindings for invalid key codes (>0x80)
    uint32_t idx = 0;
    if (g_numActionBindings > 0) {
        uint8_t* pBinding = reinterpret_cast<uint8_t*>(g_actionBindings);
        do {
            if (*pBinding > 0x80) {
                HandleActionBindingError();
                return;
            }
            idx++;
            pBinding += sizeof(ActionBinding);
        } while (idx < g_numActionBindings);
    }

    // Register a new default binding if space remains
    if (g_numActionBindings < 32) {
        int32_t offset = g_numActionBindings * sizeof(ActionBinding);
        // Write the two action IDs as an 8-byte value (little-endian: action1=0x42abc0, action2=0x42abe000)
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(g_actionBindings) + offset) = 0x42abe00042abc0ULL;
        // Write key code (0x80) as the third uint32 of the entry
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(g_actionBindings) + offset + 8) = local_c;
        g_numActionBindings++;
    }
}