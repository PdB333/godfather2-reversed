// FUNC_NAME: EARSObject::release

// Address: 0x0091f0b0
// This function performs cleanup for an EARSObject, adjusting vtable pointers,
// releasing resources, resetting a global flag, and calling a global cleanup function.

#include <cstdint>

class EARSObject {
public:
    void* m_vtable1;      // +0x00
    void* m_vtable2;      // +0x04
    // padding/other members up to offset 0x4C
    void* m_vtable3;      // +0x4C (offset 0x13)
    // ...
    void* m_pResource;    // +0x78 (offset 0x1e)
    void (*m_fnRelease)(void*); // +0x84 (offset 0x21)
};

// External symbols (vtables and global cleanup)
extern void* PTR_FUN_00d86000;   // Vtable pointer (initial)
extern void* PTR_LAB_00d85fdc;  // Second vtable
extern void* PTR_LAB_00d85fd8;  // Third vtable (first set)
extern void* PTR_LAB_00d85d84;  // Third vtable (final set)
extern uint32_t g_globalFlag;   // DAT_0112982c
void FUN_005c16e0();            // Global cleanup function

void __thiscall EARSObject::release(void) {
    EARSObject* obj = this;

    obj->m_vtable1 = &PTR_FUN_00d86000;
    obj->m_vtable2 = &PTR_LAB_00d85fdc;
    obj->m_vtable3 = &PTR_LAB_00d85fd8;

    if (obj->m_pResource != nullptr) {
        obj->m_fnRelease(obj->m_pResource);   // Release owned resource
    }

    obj->m_vtable3 = &PTR_LAB_00d85d84;       // Final vtable update
    g_globalFlag = 0;                         // Reset global flag
    FUN_005c16e0();                           // Additional cleanup
}