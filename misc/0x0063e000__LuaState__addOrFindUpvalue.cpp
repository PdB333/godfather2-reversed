// FUNC_NAME: LuaState::addOrFindUpvalue
uint LuaState::addOrFindUpvalue(void *value, int *key) {
    // param_1 (this) is LuaState*; first member (offset 0x0) is header pointer
    LuaHeader *header = *(LuaHeader **)this;
    uint idx;
    int i;

    // Search existing upvalues for matching key (key is 2 ints? Actually 5 ints stored but only 2 compared)
    if (header->upvalueCount != 0) {
        for (i = 0; i < (int)header->upvalueCount; i++) {
            // Upvalue entries are at this + 0x38 = 0xe*4 offset, each 20 bytes (5 ints)
            int *entry = this + 0xe + i * 5;
            if (entry[0] == key[0] && entry[1] == key[1]) {
                return (uint)i;
            }
        }
    }

    // Not found – add new upvalue
    idx = (uint)header->upvalueCount;
    uint newCount = (uint)(header->upvalueCount + 1);
    if (newCount > 0x20) {
        // Too many upvalues, error
        undefined4 errorMsg = FUN_00636c00("too many %s (limit=%d)", "upvalues", 0x20);
        undefined8 errorTuple = FUN_00638b80(errorMsg);
        // Error handling (likely longjmp)
    }

    // Reallocate values array if capacity insufficient
    if ((int)newCount > header->capacity) {
        int oldCapacity = header->capacity;
        int newCapacity = oldCapacity * 2;
        if (newCapacity < 4) {
            newCapacity = 4;
        } else if (oldCapacity > 0x3ffffffd) {
            if (oldCapacity > 0x7ffffff8) {
                // Overflow – error
                FUN_00633920(this[4], &DAT_00e2f044);
                code *handler = (code *)swi(3);
                return (*handler)();
            }
            newCapacity = 0x7ffffffd;
        }
        undefined4 newValues = FUN_006279a0(oldCapacity * 4, newCapacity * 4);
        header->capacity = newCapacity;
        header->values = (int *)newValues;
    }

    // Store the value in the values array at the old count (before increment)
    header->values[idx] = (int)value;

    // Store the key (5 ints) into the upvalue slot
    int *slot = this + 0xe + idx * 5;
    slot[0] = key[0];
    slot[1] = key[1];
    *(undefined8 *)(slot + 2) = *(undefined8 *)(key + 2); // copies key[2] and key[3]
    slot[4] = key[4];

    // Increment count
    header->upvalueCount = (byte)(header->upvalueCount + 1);
    return idx;
}