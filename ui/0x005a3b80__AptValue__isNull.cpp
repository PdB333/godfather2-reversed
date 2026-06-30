// FUNC_NAME: AptValue::isNull
// Address: 0x005a3b80
// Returns true if the value represents a null/undefined type (type 8 with bit 15 set).

bool AptValue::isNull() const {
    // Debug assertion: this must not be null
    if (this == nullptr) {
        // Assertion: "m_pData != 0" failed at line 0x17c in _AptValue.h
        if (gAssertionEnabled) {
            // Trigger assertion error
            DebugAssert("c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h", 0x17c, "m_pData != 0");
        }
    }

    uint value = m_data; // +0x00: internal data word
    // Type is stored in lower 15 bits; bit 15 used as a flag (likely "isNull" or "isUndefined")
    // Type 8 = null/undefined
    if ((value & 0x7FFF) == 8 && ((value >> 15) & 1) == 1) {
        return true;
    }
    return false;
}