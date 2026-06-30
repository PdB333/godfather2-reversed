// FUNC_NAME: GameObject::getOwner
int __thiscall GameObject::getOwner(GameObject* this)
{
    // Check pointer stored at +0x2178 (e.g., m_pOwnerComponent or internal subobject reference)
    if (*(int*)((uint8_t*)this + 0x2178) != 0) {
        // The stored pointer points to a member inside the owner (at +0x48).
        // Subtract 0x48 to obtain the base of the owner object.
        return *(int*)((uint8_t*)this + 0x2178) - 0x48;
    }
    return 0; // No owner
}