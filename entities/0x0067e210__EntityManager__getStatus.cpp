// FUNC_NAME: EntityManager::getStatus
int EntityManager::getStatus(void)
{
    // Global pointer to the current entity
    void* entity = (void*)DAT_01129878;
    // Extract high 24 bits of the pointer (masking out low 8 bits)
    uint24_t high24 = (uint24_t)((uint32_t)entity >> 8);
    if (entity != nullptr) {
        // Check if the entity is alive by testing field at +0x1c (typically a generation/valid flag)
        int alive = (*(int*)((uint8_t*)entity + 0x1c) != 0) ? 1 : 0;
        // Return combined value: high 24 bits from pointer, low 8 bits indicate alive status
        return ( ((int)high24) << 8 ) | (alive & 0xFF);
    }
    // Null entity: return 0 (high24 shift yields 0)
    return ((int)high24) << 8;
}