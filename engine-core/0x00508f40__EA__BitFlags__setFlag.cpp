// FUNC_NAME: EA::BitFlags::setFlag

void EA::BitFlags::setFlag(uint32 mask, bool value) {
    if (value) {
        // Set the specified bits
        m_flags |= mask;
    } else {
        // Clear the specified bits
        m_flags &= ~mask;
    }
}