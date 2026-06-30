// FUNC_NAME: getPlayerHealth
// Function at 0x0050a610: Retrieves player's health from global player pointer.
// Calls FUN_00421170 (likely GetPlayer()) and returns the value at offset 0x14 (health).
// Returns 0 if player pointer is null.

int getPlayerHealth(void)
{
    // Get the global player instance (singleton accessor)
    void* player = GetPlayer();  // FUN_00421170
    if (player != 0) {
        // Dereference health field at offset 0x14 from player object
        return *(int*)((char*)player + 0x14);
    }
    return 0;
}