// FUNC_NAME: SimManager::processEntityMessage
void __thiscall SimManager::processEntityMessage(int this, int entityId, int data) {
    if (entityId != 0) {
        int index = FUN_00849a70(entityId); // lookup index from entity ID
        if (index >= 0) {
            // this+0x10: pointer to array of entity object pointers (each 4 bytes)
            int** entityArray = *(int***)(this + 0x10);
            int* entity = entityArray[index];
            // Check if entity exists and its first field (e.g., m_id or m_refCount) is non-zero
            if (entity != nullptr && *entity != 0) {
                FUN_00849560(data); // process the message/data
            }
        }
    }
}