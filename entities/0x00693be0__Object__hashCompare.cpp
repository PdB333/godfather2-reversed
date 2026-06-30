// FUNC_NAME: Object::hashCompare
int __thiscall Object::hashCompare(const Object& other) const
{
    // First int at offset 0x00 likely a type ID or vtable pointer.
    // If it's zero or doesn't match the other object's type, trigger assertion.
    if (m_typeId == 0 || m_typeId != other.m_typeId)
    {
        // FUN_00b97aea -> Asserts type compatibility
        EARS_Assert("Type mismatch", __FILE__, __LINE__);
    }

    // Return a 32-bit value where:
    // - high 24 bits = (m_id >> 8) (i.e., the upper 24 bits of the second field)
    // - low 8 bits = equality of the second field (0 or 1)
    // This is used for fast hash-based ordering/equality checks.
    return ((m_id >> 8) & 0xFFFFFF) << 8 | (m_id == other.m_id);
}