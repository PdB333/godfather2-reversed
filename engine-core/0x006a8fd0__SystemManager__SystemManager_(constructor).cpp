// FUNC_NAME: SystemManager::SystemManager (constructor)

#include <cstdint>

// External function declarations (mapped to addresses)
extern void* __fastcall allocateMemory(uint32_t size);      // FUN_009c8e80
extern void __fastcall registerFrameCallback(void(*callback)()); // FUN_005e6620
extern void __fastcall copyBuffer(void* dest, void* src, uint32_t size); // FUN_00408900 (dest, src, size)
extern void __fastcall sub_00ab5fb0(uint32_t, uint32_t);   // FUN_00ab5fb0

// External global variables
extern SystemManager* g_pSystemManager;                    // DAT_01129950
extern void* g_initialDataBuffer;                          // DAT_01206940

// Vtable symbols from .rdata
extern void* g_vtable1;    // PTR_FUN_00d5d914
extern void* g_vtable2;    // PTR_LAB_00d5d910
extern void* g_tempPtr;    // PTR_LAB_00d5d900 (temporary)

// Forward declaration of callback function
void __fastcall systemUpdateCallback(); // FUN_006a8f10

class SystemManager {
public:
    // +0x00: vtable pointer (first virtual table)
    void* m_vtable1;
    // +0x04: initialization flag (set to 1)
    uint32_t m_initialized;  
    // +0x08: some counter (set to 0)
    uint32_t m_counter;
    // +0x0C: second vtable pointer (or base class pointer) – overwritten
    void* m_vtable2;
    // Padding or other fields up to +0x40
    // +0x40: unknown (set to 0)
    uint32_t m_field40;
    // +0x44: unknown (set to 0)
    uint32_t m_field44;
    // +0x48: pointer to an allocated sub‑object (0x14 bytes)
    void* m_subObject;
    // +0x4C: sub‑object size or count (set to 5)
    uint32_t m_subCount;
    // +0x50: unknown (set to 0)
    uint32_t m_field50;
    // +0x54: unknown (set to 0)
    uint32_t m_field54;

    void __thiscall constructor() {
        // Step 1: set basic fields and temporary vtable2
        m_initialized = 1;
        m_counter = 0;
        m_vtable2 = &g_tempPtr;                 // temporarily assign

        // Step 2: register global singleton
        g_pSystemManager = this;

        // Step 3: set final vtables (multiple inheritance pattern)
        m_vtable1 = &g_vtable1;
        m_vtable2 = &g_vtable2;

        // Step 4: some engine initialization (params 0, 1)
        sub_00ab5fb0(0, 1);

        // Step 5: zero fields at +0x40 and +0x44
        m_field40 = 0;
        m_field44 = 0;

        // Step 6: allocate a 20‑byte sub‑object
        m_subObject = allocateMemory(0x14);

        // Step 7: configure sub‑object parameters
        m_subCount = 5;
        m_field50 = 0;
        m_field54 = 0;

        // Step 8: register the frame update callback
        registerFrameCallback(systemUpdateCallback);

        // Step 9: if a global initial data buffer exists, copy its contents
        //         into the SystemManager (overwrites many fields – likely loads
        //         a pre‑computed state)
        if (g_initialDataBuffer != nullptr) {
            copyBuffer(this, &g_initialDataBuffer, 0x8000);
        }
    }
};