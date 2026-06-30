// FUNC_NAME: Entity::forwardToComponent
// 0x005c3ce0 - Thunk that adjusts this pointer by +5 and forwards a virtual function call to a component object.
// The component interface is obtained via a helper function (FUN_005c3df0) using a value passed in EAX
// (likely the first argument to the function, as in __fastcall convention).

extern void* getComponentInterface(int param); // helper function returning a pointer to a component (vtable-based)

void __thiscall Entity::forwardToComponent(int param_2, int param_3, int param_4, int param_5,
                                           int param_6, int param_7) {
    // The value in EAX at entry is used to select the component.
    int eaxParam; // placeholder – actual source is the EAX register at function start
    int* component = (int*)getComponentInterface(eaxParam); // +0x00: vtable pointer

    // Call virtual function at vtable offset 0x14 (index 5).
    // Forward all stack arguments, but replace "this" with this+5 (the component subobject offset).
    (*(void (__thiscall**)(int, int, int, int, int, int, int))(*component + 0x14))(
        (int)this + 5, // adjusted this pointer (component data starts at +0x05)
        param_2, param_3, param_4, param_5, param_6, param_7
    );
}