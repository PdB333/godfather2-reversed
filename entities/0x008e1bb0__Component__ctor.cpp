// FUNC_NAME: Component::ctor
int __thiscall Component::ctor(int this, byte flags) {
    // Call base constructor (FUN_008e1b40)
    Component::baseCtor();
    // If the lowest bit of flags is set, initialize a sub-component at offset 0x1a0 (416 bytes)
    if ((flags & 1) != 0) {
        Component::initSubComponent(this, 0x1a0);
    }
    return this;
}