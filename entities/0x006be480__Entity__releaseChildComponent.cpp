// FUNC_NAME: Entity::releaseChildComponent
void __fastcall Entity::releaseChildComponent(Entity* this) {
    // Offset +0x50 likely stores a pointer to a child component or sub-object
    if (this->m_pChildComponent != nullptr) {
        // Get interface or handle from child component (e.g., via a cast or factory)
        void* pInterface = (void*)FUN_006b0ee0(this->m_pChildComponent);
        if (pInterface != nullptr) {
            // Offset +0x40 from the interface is a resource handle/pointer to release
            FUN_006be3f0(*(int*)((byte*)pInterface + 0x40));
        }
    }
}