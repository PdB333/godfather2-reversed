// FUNC_NAME: AptValue::isBool
bool AptValue::isBool()
{
    // Assert: this pointer must not be null (line 395 of _AptValue.h)
    if (this == nullptr)
    {
        if (g_assertEnabled)
        {
            // Trigger assertion failure with source info
            // (Simplified: debug break and crash)
            __debugbreak();
        }
        return false;
    }

    // Check if the value type is BOOL (type code 7) and the high bit (bit 15) is clear
    // The internal representation: bits 0-14 = type, bit 15 = some flag (e.g., immediate/object?)
    return ((*reinterpret_cast<const uint32_t*>(this) & 0x7FFF) == 7 &&
            ((*reinterpret_cast<const uint32_t*>(this) >> 15) & 1) == 0);
}