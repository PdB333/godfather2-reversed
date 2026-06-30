// FUNC_NAME: EARSObject::EARSObject
// Function: 0x004776a0
// Role: Base class constructor for EARSObject. Calls common initialization,
//       then optionally invokes a memory management callback if the object
//       was dynamically allocated (bit 0 of param_2 set).

// Global pointer to engine globals (e.g., memory manager, system data)
// Offset +0x2d4: pointer to a function vtable or dispatch table
// The double dereference retrieves a function pointer at vtable+4 (second entry)
// that is called with (this, 0) for cleanup when bit0 of allocation flag is set.
extern void* gEngineGlobals; // DAT_01223410

// Forward declaration of the common initialization function
void EARSObject::initializeBase(); // FUN_004776d0

// Constructor
EARSObject::EARSObject(bool bAllocated) // param_2: byte flag, 0 = stack/static, 1 = heap allocated
{
    // Perform base initialization (sets up vtable, member defaults, etc.)
    this->initializeBase();

    if (bAllocated) // (param_2 & 1) != 0
    {
        // If dynamically allocated, call the second virtual function from the
        // global management structure to perform any required cleanup or registration.
        // Typically this might be "operator delete" or a destruction adapter.
        // The function is retrieved from: *(int**)(*(int**)(gEngineGlobals + 0x2d4)) + 4
        // where the first entry (offset 0) might be a destructor or memory deallocator.
        void* vtable = *(void**)((unsigned char*)gEngineGlobals + 0x2d4); // +0x2d4
        void* funcPtr = *(void**)(*(int**)vtable + 4); // second entry in the vtable
        ((void(__thiscall*)(void*, int))funcPtr)(this, 0);
    }
}