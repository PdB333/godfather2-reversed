// FUNC_NAME: EARSObject::constructor
// Function address: 0x00476850
// Constructor for EARSObject (or similar base class). The parameter flags determine whether to call a virtual setup function.
// The global at DAT_01223410 + 0x2d4 likely points to a memory manager or factory singleton.

// Assuming DAT_01223410 is a global pointer to a structure with a vtable
typedef void (__thiscall *VirtualFunction)(void* obj, int param);

// Forward declaration of the base initializer (FUN_00476880)
void __thiscall baseClassInitializer(void* this);

// Global offset: 0x2d4 from DAT_01223410 points to a pointer to a factory/manager object
#define g_pFactoryManager (*(int**)(DAT_01223410 + 0x2d4))

void* __thiscall EARSObject::constructor(void* this, byte flags)
{
    // Call base class init (likely constructor of parent)
    baseClassInitializer(this);

    // If the lowest bit of 'flags' is set, call a virtual function via the factory
    // The factory's vtable+4 is called with (this, 0).
    if ((flags & 1) != 0)
    {
        // Retrieve the factory object from global offset
        int* factoryObj = *g_pFactoryManager;  // Dereference to get actual object
        // Get vtable pointer from factory object
        int* vtable = *(int**)factoryObj;
        // vtable+4 is the second virtual function (likely a setup/register/initialize)
        VirtualFunction setupFunc = (VirtualFunction)vtable[1]; // +4 bytes = second entry
        setupFunc(this, 0);
    }

    return this;
}