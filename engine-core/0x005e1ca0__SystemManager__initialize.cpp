// FUNC_NAME: SystemManager::initialize

#include <cstdint>

// Forward declaration of helper function (likely initializes a sub-object)
void initializeSlot();

// Global singleton pointer
extern void* g_systemManager; // DAT_0122350c

class SystemManager {
public:
    // Constructor / Initialize
    void __thiscall initialize() {
        // Set global singleton to this instance
        g_systemManager = this;

        // Set vtable pointer (PTR_FUN_00e3f470)
        *reinterpret_cast<void**>(this) = &s_vtable;

        // Initialize 4 slots (sub-objects or entries)
        for (int i = 0; i < 4; ++i) {
            initializeSlot();
        }

        // Initialize pool/metadata fields
        // Offsets from this:
        m_unknown0 = 0;   // +0x5CE
        m_unknown1 = 0;   // +0x5CF
        m_unknown2 = 0;   // +0x5D0
        m_byteFlag = 0;   // +0x5D1 (byte)
        m_minSlots = 1;   // +0x5D2
        m_maxSlots = 5;   // +0x5D3
    }

private:
    void* vtablePtr; // +0x00

    // The following fields are at large offsets (0x5CE+)
    int32_t m_unknown0;   // +0x5CE
    int32_t m_unknown1;   // +0x5CF
    int32_t m_unknown2;   // +0x5D0
    uint8_t m_byteFlag;   // +0x5D1
    int32_t m_minSlots;   // +0x5D2
    int32_t m_maxSlots;   // +0x5D3

    // Static vtable (external)
    static void* s_vtable; // PTR_FUN_00e3f470
};

// Helper function declaration (likely member of same class or global)
void __thiscall initializeSlot();