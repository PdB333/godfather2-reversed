// FUNC_NAME: GameObject::release
void __fastcall GameObject::release(GameObject* this) {
    // Decrement counter at offset 0x16c (likely reference count or pending action timer)
    this->referenceCount--; // *(int*)(this + 0x16c) -= 1
}