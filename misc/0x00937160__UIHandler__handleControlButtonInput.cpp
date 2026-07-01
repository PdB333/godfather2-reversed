// FUNC_NAME: UIHandler::handleControlButtonInput
// Address: 0x00937160
// Role: Processes UI control button path strings, determines if they match specific patterns and triggers appropriate actions.

#include <string.h>

bool handleControlButtonInput(const char* buttonPath)
{
    // Compare with "/fopt/buttons/button_2/button"
    const char* rollOverButtonPath = "/fopt/buttons/button_2/button";
    bool isRollOverButton = true;
    const char* src = rollOverButtonPath;
    const char* dst = buttonPath;
    int compareLen = 30;
    while (compareLen != 0) {
        if (*src != *dst) {
            isRollOverButton = false;
            break;
        }
        src++;
        dst++;
        compareLen--;
    }

    if (isRollOverButton) {
        // This is the rollover button – show "RollOverButton" tooltip or action
        // FUN_005a04a0 – likely execUIAction or showTooltip
        execUIAction("RollOverButton", 0, &DAT_00d8a0dc, 1, &DAT_00d796d4);
        // Build a button state structure and set it
        int buttonState = DAT_011302b0; // global state
        int zero1 = 0;
        char zero2 = 0;
        setButtonState(&buttonState, 0); // FUN_00408a00
        return true;
    }

    // Check against control content patterns "/fopt/content/control_%d/item" for indices 0..6
    for (int index = 0; index <= 6; index++) {
        char formattedPath[64];
        buildFormattedString(formattedPath, "/fopt/content/control_%d/item", index); // FUN_00910160 (sprintf-like)
        if (strcmp(formattedPath, buttonPath) == 0) {
            handleControlContentItem(index); // FUN_00936f80
            return true;
        }
    }
    return false;
}