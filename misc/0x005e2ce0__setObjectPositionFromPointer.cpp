// FUNC_NAME: setObjectPositionFromPointer
bool setObjectPositionFromPointer(void* unused, const Vec3* position) {
    // Check if we can set position (global flag at g_GameManager + 0x1744)
    if (*(uint8*)(g_GameManager + 0x1744) == 0) {
        return false;
    }

    // Retrieve the active object (likely player or current entity)
    void* obj = getActiveObject();
    if (obj == nullptr) {
        return false;
    }

    // Copy position vector to object offset +0x288 (presumably m_position)
    *(Vec3*)((uint8*)obj + 0x288) = *position;
    return true;
}