// FUNC_NAME: Entity::isActive
// Function at 0x0074a070: checks if entity is active (non-zero fields at +0x00 and +0x14)
int Entity::isActive() {
    // m_pOwner (+0x00) and m_stateFlags (+0x14) both zero -> inactive
    if ((m_stateFlags == 0) && (m_pOwner == 0)) {
        return 0;
    }
    return 1;
}