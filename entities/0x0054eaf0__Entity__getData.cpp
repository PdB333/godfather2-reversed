//FUNC_NAME: Entity::getData
void* __thiscall Entity::getData(void) {
    // Returns pointer stored at offset 0x18 (likely m_pData or similar)
    return *(void**)((char*)this + 0x18);
}