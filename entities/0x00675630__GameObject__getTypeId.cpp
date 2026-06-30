// FUNC_NAME: GameObject::getTypeId
uint16_t GameObject::getTypeId() {
    // Cached type ID at +0x1c; if zero, fetch from data sources
    if (*(uint16_t *)(this + 0x1c) == 0) {
        uint16_t result = 0x800; // Default type ID (e.g., "none" or "generic")
        // Try primary data source at +0x20 (e.g., a data block pointer)
        if (*(void **)(this + 0x20) != 0) {
            result = *(uint16_t *)(*(void **)(this + 0x20) + 0x10c);
            *(uint16_t *)(this + 0x1c) = result;
            return result;
        }
        // Fallback to secondary data source at +0x28 (e.g., alternative definition)
        if (*(void **)(this + 0x28) != 0) {
            result = *(uint16_t *)(*(void **)(this + 0x28) + 0x16);
        }
        *(uint16_t *)(this + 0x1c) = result;
    }
    return *(uint16_t *)(this + 0x1c);
}