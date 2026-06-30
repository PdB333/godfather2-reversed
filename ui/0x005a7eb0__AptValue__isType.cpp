// FUNC_NAME: AptValue::isType
bool AptValue::isType(const AptValue* pValue) {
    // Debug assertion from _AptValue.h line 0x19a
    if (pValue == nullptr) {
        // Original assertion: __debugbreak() and possibly abort
        // The decompiled code shows a complex assertion system.
        // Simplified for reconstruction:
        __debugbreak();
        // If assertion is disabled, continue
    }

    // Type field is stored in lower 15 bits (0x7FFF mask)
    // Flag in bit 15 must be set (0x8000)
    if ((*reinterpret_cast<const uint32_t*>(pValue) & 0x7FFF) == 9 &&
        ((*reinterpret_cast<const uint32_t*>(pValue) >> 15) & 1) != 0) {
        return true;
    }
    return false;
}