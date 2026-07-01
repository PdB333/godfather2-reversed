// FUNC_NAME: GameObject::scalarDeletingDestructor
// Address: 0x0094d420
// MSVC scalar deleting destructor pattern. If flag bit 0 is set, deallocates this of size 0xA0.
int __thiscall GameObject::scalarDeletingDestructor(GameObject* this, unsigned char flag) {
    // Call base class destructor (likely a virtual destructor chain)
    this->baseDestructor();  // FUN_0094d150
    // If flag indicates deletion, free memory
    if (flag & 1) {
        operatorDelete(this, 0xA0);  // ::operator delete(this, 160)
    }
    return reinterpret_cast<int>(this);
}