// FUNC_NAME: Entity::setRespawnPosition
bool Entity::setRespawnPosition(const Vector3& position) {
    // Check if respawning is allowed (offset 0x1744 likely a bool flag like m_bCanRespawn)
    if (*(bool*)((uintptr_t)this + 0x1744)) {
        // Retrieve a pointer to the respawn data structure (via a global or static function)
        void* respawnData = getRespawnData(); // 0x005e2150
        if (respawnData != nullptr) {
            // Copy the position vector (three floats) into respawnData offsets
            *(Vector3*)((uintptr_t)respawnData + 0x288) = position;
            return true;
        }
    }
    return false;
}