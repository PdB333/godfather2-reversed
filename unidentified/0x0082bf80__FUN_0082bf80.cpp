// FUNC_NAME: SomeClass::SomeClass
// Address: 0x0082bf80
// Role: Constructor for a class (inherits BaseClass at +0x00 and InterfaceVTable at +0x30)
// The constructor may allocate a sub-object of size 0xD0 when creationFlags bit 0 is set

#include <cstddef>

class SomeClass : public BaseClass
{
public:
    void* m_pVTable;                     // +0x00
    /* ... other members ... */
    void* m_pInterfaceVTable;            // +0x30 (set after base constructor)
    /* ... rest of members ... */

    __thiscall SomeClass(byte creationFlags);
};

// Global vtable pointers (guessed labels)
extern void* PTR_FUN_00d73820;    // Primary vtable for SomeClass
extern void* PTR_LAB_00e32854;    // Interface vtable at offset +0x30

// Forward declarations of called functions
__thiscall void baseConstructor();        // FUN_0082b1c0
__thiscall void interfaceInit();          // FUN_00821f60
void* __cdecl operatorNew(size_t size);   // FUN_009c8f80

__thiscall SomeClass::SomeClass(byte creationFlags)
{
    // Set primary vtable
    this->m_pVTable = &PTR_FUN_00d73820;
    // Call base class constructor
    baseConstructor();
    // Set secondary (interface) vtable at offset 0x30
    this->m_pInterfaceVTable = &PTR_LAB_00e32854;
    // Initialize interface-specific data
    interfaceInit();
    // Optionally allocate a sub-object and call its virtual init
    if ((creationFlags & 1) != 0)
    {
        // Allocate 0xD0 bytes
        int* pSubObject = (int*)operatorNew(0xD0);
        // Call vtable entry at offset 4 (typically __thiscall with sub-object as 'this',
        // taking parent pointer and size as arguments)
        void (*init)(void*, void*, int) = (void (*)(void*, void*, int))((void**)pSubObject)[1];
        init(pSubObject, this, 0xD0);
    }
    return this;
}