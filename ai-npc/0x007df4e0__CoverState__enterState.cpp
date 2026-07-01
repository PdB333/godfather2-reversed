// FUNC_NAME: CoverState::enterState
void __thiscall CoverState::enterState(int this) {
    // Log debug event with hash 0x180e537e (likely "EnterCover")
    FUN_004ac480(0x180e537e, 0, *(uint *)(*(int *)(this + 0x58) + 0x6e8) >> 2, 1, 0, 1, 0,
                 *(undefined4 *)(*(int *)(this + 0x58) + 0x1dbc));

    // Check if current state is non-zero and not the target state (0x48)
    if (*(int *)(this + 0x74) != 0 && *(int *)(this + 0x74) != 0x48) {
        // Play sound effect (ID 0x2f)
        FUN_0079f100(0x2f, 0);

        // Set flag 0x1000 on the owner object (e.g., player flags)
        uint *flags = (uint *)(*(int *)(this + 0x58) + 0x24a0);
        *flags |= 0x1000;

        // Compute new state index (subtract base 0x48)
        int newState;
        if (*(int *)(this + 0x74) == 0) {
            newState = 0;
        } else {
            newState = *(int *)(this + 0x74) - 0x48;
        }

        int owner = *(int *)(this + 0x58);
        int *listHead = (int *)(owner + 0x30c0); // Pointer to list head (active states?)
        int currentHead = *listHead;

        // If the list head differs from new state, update the list
        if (currentHead != newState) {
            if (currentHead != 0) {
                FUN_004daf90(listHead); // Remove old head from list
            }
            *listHead = newState;
            if (newState != 0) {
                // Insert new state into linked list (likely doubly linked)
                *(int *)(owner + 0x30c4) = *(int *)(newState + 4); // Set head's prev to new node's prev
                *(int **)(newState + 4) = listHead; // Set new node's prev to head pointer
            }
        }

        // Record start time (from FUN_0043b490, likely GetTickCount)
        *(int *)(this + 0x7c) = FUN_0043b490();
    }
}