// FUNC_NAME: EntityDataManager::resetAllEntities
// Address: 0x006278d0
// Role: Initializes/resets all entities held by the manager. Iterates an internal linked list of entity structures,
//       sets initial values, and calls a per-entity callback (likely an initializer or cleaner).
// Called by: 0x0043e6a0, 0x0043e860 (probably part of initialisation or shutdown)

void EntityDataManager::resetAllEntities()
{
    // this+0x10 -> internal list manager sub-object
    // +0x3c -> iterator/state structure for the entity list
    int *entityListState = *(int **)(*(int **)(this + 0x10) + 0x3c);

    // Acquire lock or begin critical section
    FUN_006382a0(); // likely mutex lock or state reset

    // Initialise the list state with a base address (maybe store 'this' pointer)
    FUN_006266e0(entityListState);

    // Clear a 32‑bit field at offset 0x54 of the list state
    *(int *)(entityListState + 0x54) = 0;

    // Walk the linked list of entities
    do {
        // Set current pointer (offset +0x14) to the head of the list (offset +0x28)
        *(int **)(entityListState + 0x14) = *(int **)(entityListState + 0x28);

        // Dereference head pointer to get the first entity pointer
        int *firstEntity = **(int ***)(entityListState + 0x28);

        // Store the entity pointer into both first and second slots
        // +0x08 and +0x0c are probably start/end or current/next hints
        *(int *)(entityListState + 0x08) = (int)firstEntity;
        *(int *)(entityListState + 0x0c) = (int)firstEntity;

        // Zero a 16‑bit field at offset +0x2e (likely an index or flag)
        *(short *)(entityListState + 0x2e) = 0;

        // Call the iterator callback (FUN_006278c0) for the current state.
        // Returns non‑zero if there are more entities to process.
    } while (FUN_00635ab0(entityListState, FUN_006278c0, 0) != 0);

    // Release lock or end critical section
    FUN_006276b0(); // likely mutex unlock or cleanup
}