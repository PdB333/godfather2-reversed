// FUNC_NAME: UIPopup::activateButtonByPath
// Function address: 0x0098dd70
// Role: Searches for a UI button path in a popup (button_0 or button_1) and triggers a rollout animation.
// Takes a button path string (e.g., "/text/popup_root/popup/button_0/button"), a callback function and context.
// Returns 1 if a matching button was found and rolled out, 0 otherwise.

#include <cstring> // for string comparison (inlined below)

// Forward declarations for external functions (guessed based on context)
extern int FUN_005c4630(char* buffer, int size, const char* format, int arg);
extern void* FUN_004d3b00(int buttonIndex); // Returns a pointer to a struct containing button path string as first element
extern void FUN_005a04a0(const char* action, int unk0, void* unk1, int unk2, const char* buttonPath); // "RollOutButton"

// Constants
const char* DEFAULT_BUTTON_PATH = "\x0\x54\x6e\x20"; // Likely "RollOutButton" default string (DAT_0120546e)

char UIPopup::activateButtonByPath(const char* buttonPath, void (*callback)(int), int callbackContext) {
    char result = 0;

    // Only two buttons (index 0 and 1) are considered
    for (int i = 0; i < 2; ++i) {
        // Format the expected button path: /text/popup_root/popup/button_%d/button
        char formattedPath[96];
        FUN_005c4630(formattedPath, 0x60, "/text/popup_root/popup/button_%d/button", i);

        // Compare input path with formatted path (inline string comparison)
        const char* pFormatted = formattedPath;
        const char* pInput = buttonPath;
        int cmpResult;
        do {
            signed char c1 = *pFormatted;
            signed char c2 = *pInput;
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            ++pFormatted;
            ++pInput;
        } while (true);

        if (cmpResult == 0) {
            // Found matching button index
            // Get the actual button's path from the button data structure
            void* buttonData = FUN_004d3b00(i);
            const char* actualButtonPath = *(const char**)buttonData; // First field is a string pointer
            if (actualButtonPath == nullptr) {
                actualButtonPath = DEFAULT_BUTTON_PATH;
            }

            // Trigger the "RollOutButton" action
            FUN_005a04a0("RollOutButton", 0, &DAT_00e3d7ac, 1, actualButtonPath);

            // If a callback was provided, invoke it
            if (callbackContext != 0) {
                callback(callbackContext);
            }

            result = 1;
        }

        if (result) {
            break;
        }
    }

    return result;
}