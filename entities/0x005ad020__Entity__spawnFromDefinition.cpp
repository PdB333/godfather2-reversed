// FUNC_NAME: Entity::spawnFromDefinition
int __thiscall Entity::spawnFromDefinition(int this, undefined4 definition) {
    // Local variables for hash/string operations
    char cVar1;
    char *in_EAX; // Likely a string pointer from this->definitionName
    undefined4 uVar2;
    int iVar3;
    undefined8 *puVar4;
    int local_20; // Probably a result or count
    undefined8 local_10; // 8-byte buffer
    undefined8 local_8;  // 8-byte buffer

    puVar4 = &local_10;
    local_10 = 0;
    local_8 = 0;

    // If the entity's definition name is empty, return this (no spawning needed)
    if (*in_EAX == '\0') {
        return this;
    }

    // Call to parse or set up the definition (e.g., load from data system)
    FUN_005ad100(this, definition);

    if (local_20 != 0) {
        // Get something like a class or type ID from the buffer
        uVar2 = FUN_005bc1e0(puVar4);
        // Try to find or create the entity instance from the type
        iVar3 = FUN_005bb050(uVar2, puVar4);
        if ((iVar3 != 0) &&
           ((cVar1 = FUN_0059c5c0(0), cVar1 != '\0' || (cVar1 = FUN_005abd70(), cVar1 != '\0')))) {
            // If successful and game is not paused or is able to spawn, return the new entity
            return iVar3;
        }
    }
    return 0; // Failed to spawn
}