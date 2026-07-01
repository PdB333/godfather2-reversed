// FUNC_NAME: Destructible::Constructor
// Function address: 0x008cb170
// Reconstructed C++ from Ghidra decompilation. This is a constructor for a class
// with multiple inheritance (vtables at offsets 0, 0xC, 0x2C, 0x50).
// The second parameter indicates whether the object was heap-allocated (bit 0 set).
// If heap-allocated, the constructor calls a memory deallocation handler (likely for
// placement delete on allocation failure, but here it's called unconditionally after
// all other construction steps — may be a pool manager registration).

class Destructible;

// Forward declare vtable structures (defined externally in the binary)
struct VTable_Base1;
struct VTable_Base2;
struct VTable_Base3;
struct VTable_Base4;
struct VTable_Derived; // final vtable after overriding base's slot

// Known external functions (not reconstructed)
extern void initObjectStatic(void* globalStatic); // FUN_004086d0
extern void baseClassConstructor();                // FUN_008cc370
extern int* getScalarDeletingDestructorVTable();   // FUN_009c8f80

// Constructor implementation
Destructible* __thiscall Destructible::Constructor(Destructible* this, byte param2)
{
    // Set up vtables for multiple base classes
    this->vtable1 = &PTR_FUN_00d7c240;   // +0x00: vtable for primary base
    this->vtable2 = &PTR_LAB_00d7c230;   // +0x0C: vtable for second base
    this->vtable3 = &PTR_FUN_00d7c21c;   // +0x2C: vtable for third base
    this->vtable4 = &PTR_LAB_00d7c210;   // +0x50: vtable for fourth base (temporary)

    // Register this object with the static lifecycle manager (e.g., atexit)
    initObjectStatic(&DAT_012069d4);

    // Override the fourth base's vtable with the final derived class vtable
    this->vtable4 = &PTR_LAB_00d7c15c;

    // Invoke base class constructor (likely the fourth base)
    baseClassConstructor();

    // If the object was allocated on the heap (param2 & 1), handle deletion.
    // This is unusual for a constructor — it may be a pool manager registration
    // for deferred cleanup, or a fallback for failed construction.
    if ((param2 & 1) != 0)
    {
        // Get pointer to scalar deleting destructor vtable
        int* deleteVTable = getScalarDeletingDestructorVTable();
        // Call the destructor/deallocation function through the vtable
        // Signature: void __thiscall operatorDelete(void* this, unsigned int size)
        ((void (*)(Destructible*, unsigned int))(deleteVTable[1]))(this, 0x60);
    }

    return this;
}