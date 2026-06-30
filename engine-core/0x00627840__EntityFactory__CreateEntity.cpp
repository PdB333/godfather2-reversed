// FUNC_NAME: EntityFactory::CreateEntity
// Address: 0x00627840
// Role: Allocates and initializes a game entity (size 0x58) with default values, then calls initObject.

undefined4* EntityFactory::CreateEntity(void)
{
    undefined4* newEntity;
    int initResult;

    // Allocate 0x58 bytes from custom allocator (pool or heap)
    newEntity = (undefined4*)(*allocator)(0, 0x58);
    if (newEntity != (undefined4*)0x0) {
        // Initialize all fields to default values
        // +0x04: byte set to 8 (some flag or type)
        *(undefined1*)(newEntity + 1) = 8;
        // +0x05: byte set to 0
        *(undefined1*)((int)newEntity + 5) = 0;
        // +0x4C: integer set to 0
        newEntity[0x13] = 0;
        // +0x00: first dword set to 0
        *newEntity = 0;
        // +0x1C: integer set to 0
        newEntity[7] = 0;
        // +0x20: integer set to 0
        newEntity[8] = 0;
        // +0x50: integer set to 0
        newEntity[0x14] = 0;
        // +0x3C: integer set to 0
        newEntity[0xf] = 0;
        // +0x32: byte set to 0
        *(undefined1*)((int)newEntity + 0x32) = 0;
        // +0x30: byte set to 0
        *(undefined1*)(newEntity + 0xc) = 0;
        // +0x34: integer set to 0
        newEntity[0xd] = 0;
        // +0x31: byte set to 1 (likely active flag)
        *(undefined1*)((int)newEntity + 0x31) = 1;
        // +0x38: integer set to 0
        newEntity[0xe] = 0;
        // +0x48: integer set to 0
        newEntity[0x12] = 0;
        // +0x2C: short set to 0
        *(undefined2*)(newEntity + 0xb) = 0;
        // +0x2E: short set to 0
        *(undefined2*)((int)newEntity + 0x2e) = 0;
        // +0x14: integer set to 0
        newEntity[5] = 0;
        // +0x28: integer set to 0
        newEntity[10] = 0;
        // +0x54: integer set to 0
        newEntity[0x15] = 0;
        // +0x40: integer set to 0
        newEntity[0x10] = 0;
        // +0x10: integer set to 0
        newEntity[4] = 0;

        // Call object initialization with static config data (vtable or constants)
        initResult = initObject(newEntity, s_configData, 0);
        if (initResult == 0) {
            // Success: return the newly created entity
            return newEntity;
        }
        // Initialization failed; cleanup and return null
        cleanupObject();
    }
    return (undefined4*)0x0;
}