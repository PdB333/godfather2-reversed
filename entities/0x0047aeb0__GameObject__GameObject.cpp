// FUNC_NAME: GameObject::GameObject
// Address: 0x0047aeb0
// This is a constructor for a derived EARS object that optionally calls a virtual initialization function.
// The initFlags parameter controls whether the vtable-based initialization is invoked.

// Forward declaration of base class constructor (called at 0x0047af00)
void __thiscall BaseObject::BaseObject(void* this);

// Global pointer to manager structure (DAT_01223410)
extern void* g_pGlobalManager;

void* __thiscall GameObject::GameObject(void* this, byte initFlags) {
    // Call base class constructor (FUN_0047af00)
    BaseObject::BaseObject(this);

    // If the lowest bit of initFlags is set, invoke the second virtual function (index 1)
    if ((initFlags & 1) != 0) {
        // The manager structure at offset 0x2d4 contains a pointer to a vtable (or function table)
        // In the original decompilation: (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))
        // This retrieves the vtable pointer, then calls the function at offset 4 (index 1).
        void** vtable = *(void***)((char*)g_pGlobalManager + 0x2d4);
        typedef void (__thiscall* VirtualInitFunc)(void*, int);
        VirtualInitFunc initFunc = (VirtualInitFunc)vtable[1];
        initFunc(this, 0);
    }

    return this;
}