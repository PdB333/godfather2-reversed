// FUNC_NAME: GameObject::releaseChildAndGetParent
int __fastcall GameObject::releaseChildAndGetParent(GameObject* this) {
    int* containerPtr;
    struct { int field0; int field1; char field2; } stackMessage; // size 0xC

    // If the active flag is set (offset +0x190)
    if (this->m_bActive != 0) {
        this->m_bActive = 0;

        // If there is a child component and it is not a sentinel value (0x48)
        if (this->m_pChild != nullptr && reinterpret_cast<int>(this->m_pChild) != 0x48) {
            // The child pointer is actually offset by 0x48 from its owning object
            containerPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this->m_pChild) - 0x48);
            // Call virtual destructor on the owning object (vtable+0x18)
            (containerPtr->vtable->destructor)();
        }

        // Check flag bit 1 at offset +0x25c
        if ((this->m_flags & 0x2) != 0 && this->m_pExtra != nullptr &&
            reinterpret_cast<int>(this->m_pExtra) != 0x48) {
            ExtraManager::releaseExtra(this->m_pExtra); // FUN_00728200
        }

        // If flag bit 1 still set
        if ((this->m_flags & 0x2) != 0) {
            // Prepare a message structure from a global constant
            stackMessage.field0 = g_messageTemplate; // DAT_0112b574
            stackMessage.field1 = 0;
            stackMessage.field2 = 0;
            MessageSystem::postMessage(&stackMessage, 0); // FUN_00408a00
        }

        // Clear the two lowest bits of flags
        this->m_flags &= 0xfffffffc;

        // Release a resource pointer if valid
        if (this->m_pResource != nullptr) {
            ResourceManager::release(this->m_pResource); // FUN_005e6660
            this->m_pResource = nullptr;
        }
    }

    // Return the owner of the child component (or null)
    if (this->m_pChild != nullptr) {
        return reinterpret_cast<int>(this->m_pChild) - 0x48;
    }
    return 0;
}