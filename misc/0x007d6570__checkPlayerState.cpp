//FUNC_NAME: checkPlayerState
unsigned int checkPlayerState(void)
{
    // Get system by ID 0x35 (likely a manager or subsystem)
    unsigned int systemHandle = getSystemByID(0x35);
    // Check if the system is active/ready
    unsigned int isActive = isSystemActive(systemHandle);
    if ((char)isActive != '\0') {
        // Check if a specific game flag (0x20000) is set (e.g., "in combat" or "mission active")
        unsigned int flagSet = hasGameFlag(0x20000);
        if ((char)flagSet != '\0') {
            // Get the current player object pointer
            int playerPtr = getPlayerObject();
            if (playerPtr != 0) {
                // Compute a value from player pointer + 0x3c (likely a field offset)
                unsigned int value = playerPtr + 0x3c;
                // Check bit 0 of byte at playerPtr + 0x40 (e.g., a flags field)
                if ((*(unsigned char *)(playerPtr + 0x40) & 1) != 0) {
                    // Return value with low byte set to 1, upper bytes from shifted value
                    return (value >> 8) | 0x1;
                }
                // Otherwise return value with low byte cleared
                return value & 0xffffff00;
            }
        }
    }
    // Default: return 0 with low byte cleared
    return 0;
}