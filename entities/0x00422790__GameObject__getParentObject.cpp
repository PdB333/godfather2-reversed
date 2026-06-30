// FUNC_NAME: GameObject::getParentObject
// Function at 0x00422790: getter for parent object pointer stored at offset 0x178
// Likely part of EARSObject hierarchy (e.g., scene graph parent)
void* __fastcall GameObject::getParentObject() const {
    // +0x178 : m_pParentObject (pointer to parent GameObject or null)
    return *(void**)((uint8_t*)this + 0x178);
}