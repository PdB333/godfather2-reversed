//FUNC_NAME: handleMobfButtonRollOut
// Function address: 0x00958420
// Checks if the given button path matches one of the predefined mobface button paths (button_0 to button_5).
// If a match is found, it formats a new path and calls a function to roll out the button.
// Returns 1 if a match was processed, 0 otherwise.

#include <cstring>

char handleMobfButtonRollOut(const char* buttonPath) {
    char result = 0;
    for (unsigned int index = 0; index <= 5; ++index) {
        char buffer[64];
        // Format: "/mobf/buttons/button_%d/button"
        snprintf(buffer, sizeof(buffer), "/mobf/buttons/button_%d/button", index);
        if (strcmp(buffer, buttonPath) == 0) {
            // Match found – format the rollout path and trigger the rollout
            snprintf(buffer, sizeof(buffer), &DAT_00e3266c, index);  // DAT_00e3266c is likely a format string like "/mobf/buttons/button_%d/rollout"
            FUN_005a04a0("RollOutButton", 0, &DAT_00d8c478, 1, buffer);  // DAT_00d8c478 is likely a string constant (e.g., "rollout")
            result = 1;
        }
        if (result != 0) {
            return result;
        }
    }
    return result;
}