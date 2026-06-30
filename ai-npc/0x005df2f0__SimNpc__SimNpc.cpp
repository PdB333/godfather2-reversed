// FUNC_NAME: SimNpc::SimNpc
SimNpc* __thiscall SimNpc::SimNpc(SimNpc* this, byte doFullInit) {
    // Set vtable pointer for SimNpc class (vtable at 0x00e3f2d0)
    this->vtable = (void*)&SimNpc::vtable;

    // Call base class constructor (likely Entity or Sentient)
    Entity::Entity(this); // FUN_004de130

    // Perform additional setup only when the object was dynamically allocated (bit 0 set)
    if (doFullInit & 1) {
        this->postInitialize(); // FUN_009c8eb0 (e.g., register with manager or physics init)
    }

    return this;
}