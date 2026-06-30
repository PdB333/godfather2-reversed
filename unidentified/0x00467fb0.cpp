// FUN_00467fb0: GameObject::GameObject
undefined4 * __thiscall GameObject::GameObject(undefined4 *this, byte flags) {
    // Set up initial vtable pointers (likely two levels of inheritance)
    *this = &PTR_FUN_00e31f54;         // First vtable pointer
    this[1] = &PTR_LAB_00e31f60;       // Second vtable pointer (or interface)

    // Call base class constructor (e.g., base class init)
    FUN_0043e380(this);

    // Adjust second vtable pointer after base init
    this[1] = &PTR_LAB_00e31f64;

    // Set final vtable pointer (the actual class vtable)
    *this = &PTR_LAB_00e30ea0;

    // Clear a global flag (e.g., g_bGameObjectInitialized)
    DAT_01223470 = 0;

    // If the object was heap-allocated, perform additional initialization
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);            // Possibly register with a manager or adjust reference count
    }

    return this;
}