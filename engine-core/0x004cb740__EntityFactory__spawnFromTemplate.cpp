// FUNC_NAME: EntityFactory::spawnFromTemplate

void EntityFactory::spawnFromTemplate(int creationParams) // +0x84, +0x88
{
    // Recursion guard
    g_spawnDepthCounter += 1; // _DAT_01205a30

    int newObjectIndex = 0;

    htonl(0); // Possibly a debug or stub call

    // Virtual pre-spawn validation (vtbl offset 0xC)
    (**(code **)(*(int *)this + 0xC))();

    // Check if spawning is allowed
    bool canSpawn = someValidationCheck(creationParams); // FUN_004cb6e0

    if (!canSpawn)
    {
        // Allocate memory for new object (size 0x230)
        int allocatedBlock = allocateMemory(0x230); // FUN_009c8e50

        if (allocatedBlock != 0)
        {
            // Initialize the new object (returns an index or pointer)
            newObjectIndex = initializeNewObject(); // FUN_004bf850
        }

        // Copy data from creation parameters into the new object
        int field84 = *(int *)(creationParams + 0x84);
        int field88 = *(int *)(creationParams + 0x88);

        *(int *)(newObjectIndex + 0xB0) = field84; // New object offset +0xB0
        *(int *)(newObjectIndex + 0xB4) = field88; // New object offset +0xB4

        // Post-creation hook
        postSpawnHook(); // FUN_00653fd0
    }

    g_spawnDepthCounter -= 1;
}