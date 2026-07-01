// FUNC_NAME: SomeClass::setFlag0x200
// Function address: 0x008428f0
// Sets or clears bit 9 (0x200) of the flags field at offset 0x4c.
// This is likely a control flag for some behavior (e.g., visibility, collision, enabled state).

void __thiscall SomeClass::setFlag0x200(bool enable)
{
    if (enable) {
        *(uint *)(this + 0x4c) |= 0x200;
    } else {
        *(uint *)(this + 0x4c) &= ~0x200;
    }
}