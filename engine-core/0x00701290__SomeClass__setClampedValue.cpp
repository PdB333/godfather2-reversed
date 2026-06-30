// FUNC_NAME: SomeClass::setClampedValue
// Address: 0x00701290
// Clamps a value to a maximum stored at +0x32c, updates the value at +0x328,
// then notifies via a dirty flag mechanism through a manager object at +0x58.
// The global check "isSystemEnabled" (FUN_00481620) gates the operation.

void __thiscall SomeClass::setClampedValue(uint newValue) {
    // Global enable check; skip if not active
    if (!isSystemEnabled()) {
        return;
    }

    // Retrieve maximum allowed value (cap) at +0x32C
    uint cap = *(uint *)(this + 0x32C);
    // Reference to the target field at +0x328
    uint &target = *(uint *)(this + 0x328);

    // Clamp newValue to cap
    if (newValue > cap) {
        target = cap;
    } else {
        target = newValue;
    }

    // Obtain the internal manager object at +0x58
    void *manager = *(void **)(this + 0x58);
    // Call virtual function at vtable offset 0x28 (entry index 10) with flag 0x20
    // This likely marks the value as dirty or triggers an update notification.
    void (*notify)(uint) = (void (*)(uint))((*(int **)manager)[0x28 / 4]);
    notify(0x20);
}