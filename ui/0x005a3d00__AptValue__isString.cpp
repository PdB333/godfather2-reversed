// FUNC_NAME: AptValue::isString
// Address: 0x005a3d00
// Returns true if the value type is string (type 4) and the high bit is set.

bool __thiscall AptValue::isString() const
{
    // Debug assertion: this must be non-null (see _AptValue.h line 400)
    // In release this check is removed.

    uint32_t typeField = *reinterpret_cast<const uint32_t*>(this); // +0x00: type/flags field

    // Verify type ID in low 15 bits equals 4 (string type in GFx)
    if ((typeField & 0x7FFF) != 4)
        return false;

    // Check that bit 15 is set (indicates a string handle/object)
    if (((~(typeField >> 15) & 1) != 0)
        return false;

    return true;
}