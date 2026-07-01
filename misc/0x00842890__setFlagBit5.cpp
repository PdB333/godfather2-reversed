// FUNC_NAME: setFlagBit5
// Function address: 0x00842890
// Role: Sets or clears bit 5 (0x20) in the flags field at offset 0x4c.
// This is likely a member function of a class that uses a bitfield for state flags.

void __thiscall SomeClass::setFlagBit5(bool enable) {
    // Offset +0x4c: uint32_t m_flags; // Bitfield of various flags
    if (enable) {
        m_flags |= 0x20;   // Set bit 5
    } else {
        m_flags &= ~0x20;  // Clear bit 5
    }
}