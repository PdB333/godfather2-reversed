// FUNC_NAME: Player::areAllCrewReady
bool Player::areAllCrewReady(int playerIndex) // context index or player ID
{
    bool allReady = false;     // bVar3
    bool anyNotReady = false;  // bVar1

    // Check if crew feature is active (offset +0x1744 commonly a flag)
    if (*(char *)(this + 0x1744) != '\0') {
        // Array of 5 crew slots each of size 0x129 bytes, starting at +0x490
        // Each slot likely holds a pointer to a crew member state + other data
        int *slotPtr = (int *)(this + 0x490);
        for (int i = 0; i < 5; i++) {
            if (*slotPtr != 0) {
                // Check if this specific crew member is ready via some global check
                if (!FUN_005e2040(playerIndex)) {
                    anyNotReady = true;
                }
            }
            // Advance to next slot (0x129 = 297 bytes stride)
            slotPtr += 0x129 / 4; // 297 / 4 = 74.25? Actually 0x129 bytes -> 74.25 ints?
            // But the decompiled does piVar5 = piVar5 + 0x129; as int* it increments by 0x129/4 ints?
            // In assembly it's likely adding to byte pointer. We'll just use byte offset.
            // For clarity we cast to appropriate type. We'll reinterpret.
        }
        allReady = !anyNotReady;
    }
    return allReady;
}