// FUNC_NAME: Entity::getCachedValue

struct Entity {
    void **vtable;           // +0x00
    // ... other members ...
    int32_t cachedValue;     // +0x20
    uint8_t flagDirty;       // +0x28
    // +0x2C padding/end
};

int Entity::getCachedValue() {
    if (flagDirty != 0) {
        // Call virtual function at vtable offset 0x34 (index 13)
        // The function takes a temporary 8-byte buffer and returns a 4-byte value
        uint8_t tempBuffer[8]; // local_14
        // Virtual function signature: int (__thiscall *)(Entity* this, uint8_t buffer[8])
        int (*computeFunc)(Entity*, uint8_t[8]) = (int (*)(Entity*, uint8_t[8]))vtable[13];
        return computeFunc(this, tempBuffer);
    }
    return cachedValue;
}