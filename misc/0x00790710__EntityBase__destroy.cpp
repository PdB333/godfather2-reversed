// FUNC_NAME: EntityBase::destroy
void EntityBase::destroy()
{
    // Static cleanup / reference decrement
    staticSystemCleanup(0); // FUN_00731e90(0)

    // Delete child component pointer at offset +0x9C if present
    if (m_pComponent != nullptr) { // *(int*)(this + 0x9C)
        deleteComponent(m_pComponent); // FUN_004daf90
        m_pComponent = nullptr;
    }

    // Member cleanup
    cleanupMemberData(); // FUN_00792d80
}