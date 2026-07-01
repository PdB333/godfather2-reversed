// FUNC_NAME: EntityDataManager::createEntity
// Function at 0x00832fd0 - Creates or retrieves an entity from data, optionally attaching to a parent.
// This is a factory method that either finds an existing entity or allocates a new one (0x50 bytes).
// param_1 (this) - EntityDataManager instance
// param_2 (data) - Pointer to entity data (4 ints: ID or template)
// param_3 (parent) - Optional parent object pointer (non-zero to attach)
// Returns 1 on success, 0 on failure.

int __thiscall EntityDataManager::createEntity(int *this, int *data, int parent)
{
    int iVar1;
    bool isNew;
    char canCreate;
    int *entity;
    int *allocator;

    // Virtual call: check if this data can create an entity (vtable+0x14)
    canCreate = (**(code **)(*this + 0x14))(data);
    if (canCreate == '\0') {
        return 0;
    }

    isNew = true;
    entity = (int *)findEntityByData(data);  // FUN_0082b8e0
    if (entity == (int *)0x0) {
        isNew = false;
        allocator = (int *)getGlobalAllocator();  // FUN_009c8f80
        entity = (int *)(**(code **)*allocator)(0x50, &stack0xfffffff0);  // Allocate 0x50 bytes
        if (entity == (int *)0x0) {
            return 0;
        }
        entityConstructor();  // FUN_008334a0
        *entity = (int)&PTR_LAB_00d73448;  // Set vtable pointer
        entity[0x13] = 0;  // +0x4C = 0 (some flag)
    }

    // Copy data fields into entity at offsets +0x1C to +0x28 (4 ints)
    entity[7] = *data;          // +0x1C
    entity[8] = data[1];        // +0x20
    entity[9] = data[2];        // +0x24
    entity[10] = data[3];       // +0x28

    // If this has a secondary data pointer (this[2]), copy its fields at +0x24..+0x30 into entity +0x3C..+0x48
    iVar1 = this[2];
    if (iVar1 != 0) {
        entity[0xf] = *(int *)(iVar1 + 0x24);  // +0x3C
        entity[0x10] = *(int *)(iVar1 + 0x28); // +0x40
        entity[0x11] = *(int *)(iVar1 + 0x2c); // +0x44
        entity[0x12] = *(int *)(iVar1 + 0x30); // +0x48
    }

    // If parent is provided, call virtual attach method (vtable+0x04)
    if (parent != 0) {
        (**(code **)(*entity + 4))(parent);
    }

    // If entity was newly created, register it
    if (!isNew) {
        registerEntity(entity);  // FUN_00832480
    }

    return 1;
}