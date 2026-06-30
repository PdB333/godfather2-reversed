// FUNC_NAME: Entity::getCachedHealth
__thiscall short Entity::getCachedHealth(void) {
    short cachedValue = *(short *)(this + 0x1C);  // +0x1C: cached health value (short)
    if (cachedValue == 0) {
        short result = 0x800;  // default max health (2048)
        int* component1 = *(int**)(this + 0x20);  // +0x20: pointer to primary damage component
        int* component2 = *(int**)(this + 0x28);  // +0x28: pointer to secondary damage component
        if (component1 != 0) {
            result = *(short *)(component1 + 0x10C / sizeof(int));  // offset 0x10C in component1
            *(short *)(this + 0x1C) = result;  // cache it
            return result;
        }
        if (component2 != 0) {
            result = *(short *)(component2 + 0x16 / sizeof(int));  // offset 0x16 in component2
        }
        *(short *)(this + 0x1C) = result;  // cache result
        return result;
    }
    return cachedValue;
}