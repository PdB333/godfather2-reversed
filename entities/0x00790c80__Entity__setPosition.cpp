// FUNC_NAME: Entity::setPosition
void __thiscall Entity::setPosition(Vector3* newPosition) {
    // Check if notification component exists and is valid (not 0x48 sentinel)
    if (m_pNotifyComponent != nullptr && m_pNotifyComponent != (void*)0x48) {
        // Get the base object pointer by subtracting offset 0x48 (size of some base class?)
        void* baseObj = (m_pNotifyComponent == nullptr) ? nullptr : (char*)m_pNotifyComponent - 0x48;
        // Call virtual function at vtable index 7 (offset 0x1c) to notify of position change
        (*(void(__thiscall**)(void*, Vector3*))(* (uintptr_t*)baseObj + 0x1c))(baseObj, newPosition);
    }
    // Copy new position to object's own storage
    m_position.x = newPosition->x;
    m_position.y = newPosition->y;
    m_position.z = newPosition->z;
}