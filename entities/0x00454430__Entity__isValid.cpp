// FUNC_NAME: Entity::isValid
// Address: 0x00454430
// Checks if this entity is valid. If this is the current entity (g_currentEntity), it is always valid;
// otherwise, checks a validity flag at offset +0x8. Returns 1 if valid, 0 otherwise.
bool Entity::isValid() {
    // g_currentEntity: global pointer to the currently active/selected entity (DAT_0120e9f4)
    if (g_currentEntity != this && *(int32_t*)((uint8_t*)this + 0x8) == 0) {
        return false;
    }
    return true;
}