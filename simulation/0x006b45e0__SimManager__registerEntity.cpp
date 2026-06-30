// FUNC_NAME: SimManager::registerEntity

struct PtrVector {
    int* data;     // +0x00
    int size;      // +0x04
    int capacity;  // +0x08
};

void __thiscall SimManager::registerEntity(int* thisPtr, PtrVector* entityList, int entity, bool isNew)
{
    bool skipFlagChange = true;

    // If isNew is false and the manager has an active "no-spawn" flag, skip setting the "registered" flag
    if (!isNew && *(int*)(thisPtr + 0xD4) != 0 && FUN_00791230() != 0) {
        skipFlagChange = false;
    }

    // Modify the flags at offset 0x5C of the entity: set or clear bit 23 (0x800000)
    if (skipFlagChange) {
        *(unsigned int*)(entity + 0x5C) |= 0x800000;
    } else {
        *(unsigned int*)(entity + 0x5C) &= 0xFF7FFFFF;
    }

    // Clear bit 26 (0x4000000) and set bit 27 (0x8000000) in the entity's flags
    *(unsigned int*)(entity + 0x5C) &= 0xFBFFFFFF;
    *(unsigned int*)(entity + 0x5C) |= 0x8000000;

    // Check if entity is already in the list
    int count = entityList->size;
    int index = 0;
    if (count > 0) {
        int* current = entityList->data;
        do {
            if (*current == entity) {
                // Already present; return
                return;
            }
            index++;
            current++;
        } while (index < count);
    }

    // Not found; ensure capacity
    int newSize = entityList->size + 1;
    if (newSize > entityList->capacity) {
        int newCapacity = (entityList->capacity == 0) ? 1 : entityList->capacity * 2;
        FUN_006b1e10(newCapacity);  // reallocate the vector's storage
    }

    // Add entity at the end
    int* slot = entityList->data + entityList->size;
    entityList->size++;
    if (slot != nullptr) {
        *slot = entity;
    }

    // Log the addition (likely using a global logger)
    void* local_stack[3];  // stack-based logging parameters
    local_stack[0] = (void*)&PTR_LAB_00d5dbb0;  // format string?
    local_stack[1] = (void*)DAT_0112a5a4;        // data
    local_stack[2] = (void*)thisPtr;             // context
    FUN_00408a00(&local_stack[1], 0);

    // Check if various manager subsystems are initialized (offsets 0x88, 0xA0, 0xAC, 0xB8)
    if (*(int*)(thisPtr + 0x88) == 0 &&
        *(int*)(thisPtr + 0xA0) == 0 &&
        *(int*)(thisPtr + 0xAC) == 0 &&
        *(int*)(thisPtr + 0xB8) == 0) {
        FUN_004086d0(&DAT_0112a640);   // e.g., disable something
    } else {
        FUN_00408680(&DAT_0112a640);   // e.g., enable something
    }
}