// FUNC_NAME: GameObject::isActive
bool __thiscall GameObject::isActive(GameObject* this) {
    // Check if the flag at offset 0x34 is non-zero (likely m_bActive or similar)
    return *(int*)((uint8_t*)this + 0x34) != 0;
}