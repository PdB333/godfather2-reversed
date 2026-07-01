// FUNC_NAME: Entity::setFloatMember
// Address: 0x007ac550
// Sets a float property at offset 0x0C and marks a dirty flag byte at +0x64 when the value changes.
// The dirty flag likely triggers an update or synchronization later.

struct Entity {
    // +0x00: void* vtable
    // +0x0C: float m_floatMember;
    // +0x64: uint8_t m_dirtyFlag; // 1 = changed
};

void __thiscall Entity::setFloatMember(float newValue) {
    if (newValue != this->m_floatMember) {
        this->m_dirtyFlag = 1;
        this->m_floatMember = newValue;
    }
}