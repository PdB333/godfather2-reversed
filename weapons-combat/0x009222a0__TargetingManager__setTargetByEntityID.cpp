// FUNC_NAME: TargetingManager::setTargetByEntityID
void __thiscall TargetingManager::setTargetByEntityID(int targetID) {
    // Temporary container to hold a list of all entities retrieved from the engine.
    int entityListBase;
    uint entityCount;
    int tempData[3]; // local_c, local_8, local_4 combined for clarity

    // Initialize the list (allocates or fills from a global cache).
    FUN_009217e0(&tempData);
    entityListBase = tempData[0];
    entityCount = (uint)tempData[1];

    // Iterate over the entity list (each entry is a pointer stored at offset 0 in an 8-byte slot).
    for (uint idx = 0; idx < entityCount; idx++) {
        int entity = *(int *)(entityListBase + idx * 8);
        // Compare the entity's ID field at +0x7C with the target ID.
        if (targetID == *(int *)(entity + 0x7C)) {
            FUN_0093f760(); // Play selection sound or highlight effect.
            // Store the index of the selected entity.
            this->selectedEntityIndex = idx; // +0x74
            // Mark selection as active.
            this->selectionActive = 1; // +0x58

            // Retrieve a sub‑component from the entity (e.g., controller or behavior script).
            int subComponent = *(int *)(entity + 0x160);
            int subHandle;
            if (subComponent == 0) {
                subHandle = 0;
                subComponent = 0;
            } else {
                subHandle = FUN_00891220(); // Obtain a handle to the sub‑component.
            }
            // Attach or initialize the targeting relationship.
            FUN_00976ac0(subComponent, subHandle);
            break;
        }
    }

    // Free the temporary entity list if it was allocated.
    if (entityListBase != 0) {
        FUN_009c8f10(entityListBase);
    }
}