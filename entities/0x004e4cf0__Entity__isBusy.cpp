// FUNC_NAME: Entity::isBusy
bool Entity::isBusy(void) {
    // +0x00: m_type (int)
    // +0x04: m_state (int)
    if (this->m_type == 1 && this->m_state == 0) {
        return false;
    }
    return true;
}