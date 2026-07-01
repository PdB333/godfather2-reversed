// FUNC_NAME: Player::setCurrentState
void __fastcall Player::setCurrentState(Player *this)
{
    int *headPtr;
    uint *flagPtr;
    int newState;

    // Play a sound or effect associated with state transition
    // Hash 0x537ad9e5 likely identifies the sound/effect
    // Third argument: some index from the entity's data (shifted right by 2)
    // Last argument: pointer to sound bank or similar
    FUN_004ac480(0x537ad9e5, 0, *(uint *)(*(int *)(this + 0x58) + 0x6e8) >> 2, 1, 1, 1, 0,
                 *(undefined4 *)(*(int *)(this + 0x58) + 0x1dbc));

    // Update some global state (e.g., animation system)
    FUN_007a5240();

    // Get the new state object (e.g., from a state machine)
    newState = FUN_00800a90();
    headPtr = (int *)(this + 0x74);  // +0x74: pointer to head of a linked list (e.g., state stack)

    // If the new state is null, treat as zero
    if (newState == 0) {
        newState = 0;
    } else {
        newState = newState + 0x48;  // +0x48: offset to get the actual node? (maybe state object has a node at +0x48)
    }

    // Update the linked list: remove old head if different, then insert new node
    if (*headPtr != newState) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr);  // Remove old head from list
        }
        *headPtr = newState;  // Set new head
        if (newState != 0) {
            // Save the old next pointer of the new node into this+0x78
            *(undefined4 *)(this + 0x78) = *(undefined4 *)(newState + 4);
            // Make the new node's next point to the head pointer (circular or intrusive list)
            *(int **)(newState + 4) = headPtr;
        }
    }

    // Clear a flag at offset 0x24a0 in the entity (bit 19, 0x80000)
    flagPtr = (uint *)(*(int *)(this + 0x58) + 0x24a0);
    *flagPtr = *flagPtr & 0xfff7ffff;  // Clear bit 19 (e.g., "isPlayingAnimation" or "isBusy")
}