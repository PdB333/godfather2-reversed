// FUNC_NAME: GameObject::setValueAndSetFlag
void __thiscall GameObject::setValueAndSetFlag(GameObject* this, int value) {
    // +0xFC: some member variable (e.g., m_optionValue)
    *(int*)((char*)this + 0xFC) = value;
    // +0xE8: flags field, set bit 0x10 (likely dirty flag or updated flag)
    *(unsigned int*)((char*)this + 0xE8) |= 0x10;
}