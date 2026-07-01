// FUNC_NAME: BaseObject::destroy
void __thiscall BaseObject::destroy() {
    // Clear flags: bit 0 and 1 (e.g., "destroying" or "inUse" bits)
    m_flags &= 0xFFFFFFFC;

    // Release first sub-object (e.g., a component or child object)
    if (m_subObj1 != nullptr) {
        beginDestruction();      // Lock/acquire resource
        releaseSubObject(m_subObj1);
        m_subObj1 = nullptr;
    }

    // Release second sub-object
    if (m_subObj2 != nullptr) {
        beginDestruction();
        releaseSubObject(m_subObj2);
        m_subObj2 = nullptr;
    }
}