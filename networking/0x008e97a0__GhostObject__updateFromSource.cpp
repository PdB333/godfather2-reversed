// FUNC_NAME: GhostObject::updateFromSource
// Address: 0x008e97a0
// Role: Copies transform and link data from another ghost object if ghost IDs match.
// Updates a doubly-linked list node (at +0x1a0) to point to the source's node.

void __thiscall GhostObject::updateFromSource(GhostObject* this, GhostObject* source) {
    // Check if ghost IDs match (offsets 0x180 and 0x184 likely ghost ID and source ID)
    if (*(int*)(this + 0x180) == *(int*)(source + 0x184)) {
        int** thisLink = (int**)(this + 0x1a0);
        int* sourceLink = (int*)(source + 0x48); // head of source's link chain

        // If this object's link is not already pointing to source's link
        if (*thisLink != sourceLink) {
            // Remove this object from its current link chain
            if (*thisLink != 0) {
                FUN_004daf90(thisLink); // assume unlink or release
            }
            // Set this link to point to source's link
            *thisLink = sourceLink;

            if (sourceLink != 0) {
                // Set this's next link pointer to source's next pointer
                *(int*)(this + 0x1a4) = *(int*)(source + 0x4c);
                // Insert this's link into source's chain (source's next points to this's link ptr)
                *(int**)(source + 0x4c) = thisLink;
            }
        }

        // Copy transform data (likely position/rotation) from source
        // Offsets 0x20-0x2c: 4 consecutive ints/floats (e.g., position + rotation)
        *(int*)(this + 0x190) = *(int*)(source + 0x20);
        *(int*)(this + 0x194) = *(int*)(source + 0x24);
        *(int*)(this + 0x198) = *(int*)(source + 0x28);
        *(int*)(this + 0x19c) = *(int*)(source + 0x2c);
    }
}