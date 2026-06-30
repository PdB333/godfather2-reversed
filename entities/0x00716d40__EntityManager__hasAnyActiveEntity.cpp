// FUNC_NAME: EntityManager::hasAnyActiveEntity
bool EntityManager::hasAnyActiveEntity() {
    uint32_t count = *(uint32_t*)(this + 0x744); // number of entities
    if (count != 0) {
        for (uint32_t i = 0; i < count; i++) {
            void* entity = getEntityByIndex(i); // FUN_00704130 - returns pointer to entity
            if (entity != nullptr &&
                *(char*)(entity + 0x1a8) == 0x02 &&   // status byte 1
                *(char*)(entity + 0x1aa) == 0x02) {   // status byte 2
                return true;
            }
        }
    }
    return false;
}