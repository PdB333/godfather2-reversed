// FUNC_NAME: Player::toggleActiveState
// Function address: 0x005406c0
// Manages an active flag and releases a resource when deactivating.

void __thiscall Player::toggleActiveState(char newState) {
    // +0x86c: boolean active flag (char)
    // +0x868: pointer to resource (int*)
    // +0x68: some object used for resource management

    if (m_active && newState == 0 && m_pResource != nullptr) {
        // Release the resource via a manager/component at +0x68
        releaseResource(reinterpret_cast<void*>(&m_resourceManager), m_pResource); // FUN_009ea940(this+0x68, *(this+0x868))
        m_pResource = nullptr; // Clear pointer after release
    }
    m_active = newState; // Update active state
}