// FUN_NAME: EntityManager::getEntityFromHandle
uint __thiscall EntityManager::getEntityFromHandle(uint handle) {
    uint convertedHandle;

    if (handle != 0) {
        convertedHandle = convertHandle(handle); // FUN_0071ce70
        if (convertedHandle != 0) {
            // +0x14c likely pointer to entity table or container
            return getEntityFromTable(*(uint *)(this + 0x14c), convertedHandle); // FUN_0071c320
        }
    }
    // Return handle with low byte masked (error/invalid flag?)
    return handle & 0xFFFFFF00;
}