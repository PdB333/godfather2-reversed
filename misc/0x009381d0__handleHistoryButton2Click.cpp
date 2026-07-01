// FUNC_NAME: handleHistoryButton2Click
// Address: 0x009381d0
// Role: Handles click on button_2 in history menu; plays roll-out sound and triggers audio event.

bool handleHistoryButton2Click(char* buttonPath)
{
    // Compare input path with expected button path
    const char* expectedPath = "/hist/buttons/button_2/button";
    bool match = true;
    int i = 0x1e; // max length (30 characters)
    do {
        if (i == 0) break;
        i--;
        match = (*expectedPath == *buttonPath);
        expectedPath++;
        buttonPath++;
    } while (match);

    if (match) {
        // Play "RollOutButton" sound with parameters from globals
        FUN_005a04a0("RollOutButton", 0, DAT_00d8a374, 1, DAT_00d796d4);

        // Set up audio handle and play
        struct {
            int field0; // +0x00
            int field4; // +0x04
            char field8; // +0x08
        } audioParams;
        audioParams.field0 = DAT_011302b0;
        audioParams.field4 = 0;
        audioParams.field8 = 0;
        FUN_00408a00(&audioParams, 0);
    }
    return match;
}