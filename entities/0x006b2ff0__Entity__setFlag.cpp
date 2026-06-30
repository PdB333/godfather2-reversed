// FUNC_NAME: Entity::setFlag
void __thiscall Entity::setFlag(int newFlag, int associatedData) {
    // Only update if the boolean state of the flag is changing
    // +0x174: flag (int, treated as boolean: 0=off, non-zero=on)
    // +0x178: associated data (e.g., enum or identifier)
    if ((m_flag != 0) != (newFlag != 0)) {
        m_flag = newFlag;            // +0x174
        m_flagData = associatedData; // +0x178
        this->onFlagChanged();       // FUN_006b2f70 (internal update)
    }
}