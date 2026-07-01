// FUNC_NAME: Entity::operator==
// Address: 0x00818b10
// Role: Equality comparison operator for Entity objects, includes debug type-check assertion.

bool __thiscall Entity::operator==(const Entity& other) const
{
    // Verify that both entities have a valid type pointer and are of the same type.
    // The first field (offset +0x00) is likely a vtable pointer or type identifier.
    if (this->m_type == 0 || this->m_type != other.m_type) {
        // FUN_00b97aea is a debug assertion/breakpoint (likely __debugbreak or assert).
        // It triggers if type mismatch or null pointer.
        debugAssert(); // FUN_00b97aea
    }
    
    // Compare the instance ID (second field, offset +0x04).
    // The original decompiled code shows CONCAT31, which is an artifact of Ghidra's
    // interpretation of a setne/sete instruction followed by combining bits.
    // In reality, this returns a boolean indicating equality of the ID fields.
    return this->m_instanceId == other.m_instanceId;
}