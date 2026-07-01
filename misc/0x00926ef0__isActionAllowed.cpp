// FUNC_NAME: isActionAllowed
// Address: 0x00926ef0
// Role: Checks conditions to allow a specific action, possibly related to player state and cooldown timer.

bool isActionAllowed(void)
{
    char isActive;
    
    // Check if global object pointer DAT_01130020 is valid and its +0x48 flag is set
    if (((DAT_01130020 != 0) && (*(char *)(DAT_01130020 + 0x48) != '\0')) &&
        // Check if counter at +0x78 is less than 1 (i.e., zero or negative)
        (*(int *)(DAT_01130020 + 0x78) < 1) &&
        // Check if another global object's +0x48 flag is clear
        (*(char *)(DAT_0112982c + 0x48) == '\0')) {
        // Check cooldown timer at global DAT_012233b4 + 0x544
        isActive = FUN_00955cf0(DAT_012233b4 + 0x544);
        if (isActive != '\0') {
            return 1;
        }
    }
    return 0;
}