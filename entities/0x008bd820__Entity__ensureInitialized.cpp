// FUNC_NAME: Entity::ensureInitialized
void __thiscall Entity::ensureInitialized() {
    // Check if initialization flag at +0x15c is false
    if (!*(bool *)(this + 0x15c)) {
        // Set value at +0x158 to 0
        *(int32_t *)(this + 0x158) = 0;
        // Set initialization flag to true
        *(bool *)(this + 0x15c) = true;
    }
}