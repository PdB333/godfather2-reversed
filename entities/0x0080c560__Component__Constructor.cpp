// FUNC_NAME: Component::Constructor
// Address: 0x0080c560
// This is a constructor for a class that inherits from another component (called at 0x0080c500).
// The param_2 flag (bit 0) controls whether to call FUN_0043b960, likely to initialize a subobject of size 0x7c (124 bytes).

Component* __thiscall Component::Constructor(Component* this, byte flag) {
    // Call base class constructor at 0x0080c500
    BaseComponent::Constructor(this);

    // If flag bit 0 is set, initialize a subobject of size 0x7c
    // FUN_0043b960 is likely a placement new or memset for a child object
    if ((flag & 1) != 0) {
        // Note: param_1 (this) is passed as first argument, size 0x7c as second
        InitSubobject(this, 0x7c); // calls FUN_0043b960
    }

    return this;
}