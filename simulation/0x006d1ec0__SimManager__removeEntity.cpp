// FUNC_NAME: SimManager::removeEntity
void __fastcall SimManager::removeEntity(SimManager* this) {
    // this->m_entityId (offset +0xd4) used as index into global entity array
    int entityIndex = *(int*)((char*)this + 0xd4);

    // Global entity table: DAT_012233a0 points to SimManager singleton, +4 is pointer to entity handle array
    int** entityTable = (int**)(*(int*)(DAT_012233a0 + 4));
    int handle = entityTable[entityIndex];

    // Check if handle is invalid (0 or special invalid ID 0x1f30) and if table is still allocated
    if ((handle == 0 || handle == 0x1f30) && (*entityTable != 0)) {
        releaseEntity();
        return;
    }
    releaseEntity();
}