// Xbox PDB: EARS_Apt_UIRatingPopup_OnShow
// FUNC_NAME: UIPopup::buildAndShow
// Function address: 0x00981f50
// Reconstructed from Ghidra decompilation of The Godfather 2 (EARS engine)
// Role: Builds and displays a popup UI dialog with title, text, options, and button configuration

void __thiscall UIPopup::buildAndShow(uint* popupData) {
    // Local string buffers for formatted text (max 32 chars each)
    undefined1 titleBuffer[32];    // local_20 - from popupData[8]
    undefined1 textBuffer[32];     // local_40 - from popupData[7]

    // Lookup localized strings using string table PTR_LAB_00d78708
    // First: text body (key at popupData[8])
    stringLookup(&PTR_LAB_00d78708, (char*)titleBuffer, 0x20, popupData[8]); // FUN_005c4630
    // Second: title (key at popupData[7])
    stringLookup(&PTR_LAB_00d78708, (char*)textBuffer, 0x20, popupData[7]); // FUN_005c4630

    // Store popup type and some extra data into this object
    this->popupType = popupData[3]; // +0x74
    this->someField = popupData[2]; // +0x70

    // Get title string pointer, fallback to default "..." (DAT_0120546e)
    char* title = (char*)popupData[0xb];
    if (title == nullptr) {
        title = (char*)&DAT_0120546e; // default placeholder string
    }

    // Get body text string pointer, fallback to default
    char* body = (char*)popupData[0xf];
    if (body == nullptr) {
        body = (char*)&DAT_0120546e;
    }

    // Create the popup dialog with title and text
    // Note: DAT_00d90628 is a global context/pointer, 4 is a size parameter
    scriptCommand("DisplayPopup", 0, &DAT_00d90628, 4, title, titleBuffer, textBuffer, body); // FUN_005a04a0

    // Add options (buttons) from popupData
    uint optionCount = popupData[1];
    if (optionCount != 0) {
        // Options start at popupData[0x13] (offset 0x4C)
        for (uint i = 0; i < optionCount; i++) {
            char* optionText = (char*)popupData[0x13 + i];
            if (optionText == nullptr) {
                optionText = (char*)&DAT_0120546e;
            }
            scriptCommand("AddOption", 0, &DAT_00d90628, 1, optionText); // FUN_005a04a0
        }
    }

    // Configure special action buttons based on popup type
    char* extraButton = nullptr;
    switch (popupData[3]) {
        case 1:  // OK only
        case 0xb: // Also OK only? (11)
            // If options were added, skip adding buttons (case default)
            if (optionCount != 0) break;
            // else fallthrough to default (no button)
            break;

        case 0xc: // Cancel only (12)
            extraButton = (char*)&DAT_00e36da0; // "Cancel" string
            break;

        case 0xe: // Yes/No/Cancel (14)
            // Check flags: if bit2 of popupData[0] is clear, add "Yes" button
            if ((popupData[0] & (1 << 2)) == 0) {
                scriptCommand("ActivateButton", 0, &DAT_00d90628, 1, (char*)&DAT_00e36d94); // "Yes"
            }
            // Check additional flag at byte offset 0xEC
            if (*((char*)popupData + 0xEC) != '\0') {
                scriptCommand("ActivateButton", 0, &DAT_00d90628, 1, (char*)&DAT_00d796d4); // "No"
            }
            // Check another flag at byte offset 0xED
            if (*((char*)popupData + 0xED) != '\0') {
                extraButton = (char*)&DAT_00d796d0; // "Cancel"
            }
            break;

        default:
            break;
    }

    // Activate the extra button if one was set
    if (extraButton != nullptr) {
        scriptCommand("ActivateButton", 0, &DAT_00d90628, 1, extraButton); // FUN_005a04a0
    }

    // Finalize/register the popup (likely UI system callback)
    struct {
        undefined4 field_0;
        undefined4 field_4;
        undefined1 field_8;
    } regData;
    regData.field_0 = DAT_01130198;
    regData.field_4 = 0;
    regData.field_8 = 0;
    someInitFunction(&regData, 0); // FUN_00408a00

    return;
}