// FUN_0046a720: BaseObject::constructor
// 0x0046a720 - Constructor for BaseObject (or derived class).
// Sets the vtable pointer array at offset +0x00, then calls an initialization function.
// Returns `this` pointer.

// Structure offsets:
// +0x00: vtable pointer (BaseObjectVTable*)

void* __thiscall BaseObject::constructor(void)
{
    // Assign vtable pointer (class-specific function table)
    this->vtable = (BaseObjectVTable*)0x00e324a8;

    // Call shared initialization (likely sets up other members or base sub‑object)
    // FUN_0043e2e0 does further object setup
    this->baseInitialize();

    return this;
}