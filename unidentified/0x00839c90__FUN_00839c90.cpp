// FUNC_NAME: SomeClass::clearCurrentIdIfEquals
void __thiscall SomeClass::clearCurrentIdIfEquals(int currentId) {
    // If the stored ID at offset 0x1c matches the given one, reset it to 0
    if (this->m_currentId == currentId) {
        this->m_currentId = 0;
    }
}