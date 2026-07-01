// FUNC_NAME: EntityManager::updateActiveEntities
void __thiscall EntityManager::updateActiveEntities() {
    int iVar1;
    uint uIndex;

    uIndex = 0;
    if (this->m_objectCount != 0) {
        do {
            // Dereference the pointer array to get the object pointer
            iVar1 = this->m_objectArray[uIndex];
            // Check if object type ID is not 0x637b907 and bit 5 of flags is clear
            if ((iVar1->m_typeId != 0x637b907) &&
                ((iVar1->m_flags >> 5) & 1) == 0) {
                // Call some update/processing function (global or static?)
                FUN_008c4df0();
            }
            uIndex = uIndex + 1;
        } while (uIndex < this->m_objectCount);
    }
}