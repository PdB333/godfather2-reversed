// FUNC_NAME: EARSObject::EARSObject

class EARSObject {
public:
    // Virtual function table at offset 0x00
    void* vtable;
    // Other members from offset 0x04 to 0x3B (size 0x3C)
    // Virtual function table at offset 0x3C
    void* secondaryVtable;
    // Virtual function table at offset 0x48
    void* tertiaryVtable;
    // Remaining members start at offset 0x4C
};

// External symbol for primary vtable
extern void* PTR_FUN_00e33088;    // Primary vtable
// External symbols for secondary and tertiary vtables
extern void* PTR_LAB_00e330a8;    // Secondary vtable
extern void* PTR_LAB_00e330b8;    // Tertiary vtable

// Global memory manager structure (used for allocation/deallocation)
extern int* g_engineGlobals;      // DAT_01223410

// Base class constructor called internally
void baseConstructor(void);       // FUN_004cf700

// Reconstructed constructor
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte constructFlags) {
    // Set primary vtable
    this->vtable = &PTR_FUN_00e33088;
    // Set secondary vtable at offset 0x3C (0x0F * 4)
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00e330a8;
    // Set tertiary vtable at offset 0x48 (0x12 * 4)
    *(void**)((char*)this + 0x48) = &PTR_LAB_00e330b8;
    
    // Call base class constructor
    baseConstructor();
    
    // If the "destroy" flag (bit 0) is set, perform additional cleanup via
    // a static virtual function call from the memory manager's vtable at offset 0x2D4.
    // This typically invokes a deletion or unregistration function.
    if (constructFlags & 1) {
        // Retrieve the memory manager's vtable from global structure at offset 0x2D4
        int* allocatorVtable = *(int**)((char*)g_engineGlobals + 0x2D4);
        // Call the second virtual method (offset 4) with (this, 0)
        void (*freeFunc)(EARSObject*, int) = (void (*)(EARSObject*, int))(*(void**)((char*)allocatorVtable + 4));
        freeFunc(this, 0);
    }
    
    return this;
}