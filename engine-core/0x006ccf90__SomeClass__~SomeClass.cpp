// FUNC_NAME: SomeClass::~SomeClass

#include <cstddef>

// External functions (addresses known from Ghidra)
extern void __thiscall destroySubObject(void* pSubObject);   // 0x004daf90
extern void __cdecl globalCleanup();                         // 0x00473880
extern void __cdecl operatorDelete(void* pObj, size_t size); // 0x0043b960

// Vtable pointers (defined in the binary's data section)
extern void* g_vtable_SomeClass;         // PTR_FUN_00d5f134
extern void* g_vtable_SomeClassBase1;    // PTR_LAB_00d5f124
extern void* g_vtable_SomeClassBase2;    // PTR_LAB_00d5f120
extern void* g_vtable_SomeClassBase3;    // PTR_LAB_00d5f11c

// Class definition based on offset usage
class SomeClass {
public:
    // +0x00: Main vtable pointer
    void* vtable;

    // (other members up to offset 0x3c)

    // +0x3c (index 0x0f): First base class vtable pointer
    void* vtableBase1;

    // +0x48 (index 0x12): Second base class vtable pointer
    void* vtableBase2;

    // +0x50 (index 0x14): Third base class vtable pointer
    void* vtableBase3;

    // (other members up to offset 0x78)

    // +0x78 (index 0x1e): Pointer to dynamically allocated sub-object A
    void* m_pSubObjectA;

    // +0x80 (index 0x20): Pointer to dynamically allocated sub-object B
    void* m_pSubObjectB;

    // (rest of members up to total size 0x98 bytes)
};

// Destructor (combined with deallocation if deallocFlag is set)
void __thiscall SomeClass::~SomeClass(byte deallocFlag)
{
    // Set all vtable pointers to the current class's vtables
    // to ensure correct virtual dispatch during destruction.
    this->vtable = &g_vtable_SomeClass;
    this->vtableBase1 = &g_vtable_SomeClassBase1;
    this->vtableBase2 = &g_vtable_SomeClassBase2;
    this->vtableBase3 = &g_vtable_SomeClassBase3;

    // Destroy sub-object B if it exists
    if (this->m_pSubObjectB != 0) {
        destroySubObject(this + 0x20); // offset 0x80 = &m_pSubObjectB
    }

    // Destroy sub-object A if it exists
    if (this->m_pSubObjectA != 0) {
        destroySubObject(this + 0x1e); // offset 0x78 = &m_pSubObjectA
    }

    // Perform global cleanup (e.g., release shared resources)
    globalCleanup();

    // If the deallocation flag is set, free the object's memory
    if ((deallocFlag & 1) != 0) {
        operatorDelete(this, 0x98); // object size = 0x98 bytes
    }
}