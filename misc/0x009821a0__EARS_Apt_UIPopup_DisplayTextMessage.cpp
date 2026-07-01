// Xbox PDB: EARS_Apt_UIPopup_DisplayTextMessage
// FUNC_NAME: UIDialogManager::displayMessage

class UIDialogManager {
public:
    // +0x78: pointer to message content string (null = use default message)
    char* msgContent;
    // +0x8c: flag controlling deactivation of default button (0 = deactivate)
    int deactivateDefaultButton;
    // +0x91: flag for fullscreen mode (0 = regular, non-zero = fullscreen)
    char fullscreen;
    // ... other class members not shown
};

void __fastcall UIDialogManager::displayMessage(void) {
    char* content;
    const char* command;

    if (fullscreen == '\0') {
        content = msgContent;
        if (content == (char*)0x0) {
            content = &DAT_0120546e; // default fallback message text
        }
        command = "DisplayTextMessage";
    } else {
        content = msgContent;
        if (content == (char*)0x0) {
            content = &DAT_0120546e; // default fallback message text
        }
        command = "DisplayTextMessageFullScreen";
    }

    // Execute script command to display text message
    // command: identifier for the UI action
    // second param: 0 (unused/context)
    // third param: pointer to script identifier DAT_00d90628
    // fourth param: count (1)
    // fifth param: message content string
    FUN_005a04a0(command, 0, &DAT_00d90628, 1, content);

    // Prepare a local structure (likely for debug overlay or timer)
    int local_c = DAT_011303d8; // global value, possibly a timer ID or handle
    int local_8 = 0;
    char local_4 = 0;
    FUN_00408a00(&local_c, 0); // initialize/start something with local_c

    // Optionally deactivate the default button if flag is zero
    if (deactivateDefaultButton == 0) {
        FUN_005a04a0("DeactivateDefaultButton", 0, &DAT_00d90628, 0);
    }
    return;
}