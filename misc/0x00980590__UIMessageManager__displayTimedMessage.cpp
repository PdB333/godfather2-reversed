// FUNC_NAME: UIMessageManager::displayTimedMessage
void __fastcall UIMessageManager::displayTimedMessage(UIMessageManager* this) {
    char stringBuffer[12];
    int result;

    // Check if message display is suppressed (offset +0x12B)
    if (*(char*)((int)this + 0x12B) == '\0') {
        int messageId = *(int*)((int)this + 0x6C); // Index into message table (+0x6C)
        if (messageId != -1) {
            // Check mission/game state at +0x108 (7=Failed, 8=Completed)
            if (*(int*)((int)this + 0x108) == 8 || *(int*)((int)this + 0x108) == 7) {
                goto LAB_0098067b;
            }
            if (messageId != -1) {
                // DAT_0112989c + 0x18 + messageId * 0x24 is a pointer to message data
                if (*(int*)((int)*(int*)0x0112989c + 0x18 + messageId * 0x24) == 0) {
                    return;
                }
                result = FUN_0090a5a0(); // Possibly check if message should be shown
                if (result == 0) {
                    return;
                }
                // FUN_00790d90 likely gets formatted message text
                int formattedText = FUN_00790d90();
                FUN_0097f4a0(formattedText); // Display message in a specific style
                return;
            }
        }
        // Check alternative message source at +0x11C
        if (*(int*)((int)this + 0x11C) != 0) { // Pointer to a dialog/string object
            result = FUN_008ff210(*(int*)((int)this + 0x11C)); // Validate object
            if (result != 0) {
                // FUN_008fe280: copy localized string into buffer
                char* stringCopy = FUN_008fe280(stringBuffer);
                if (stringCopy != '\0') {
                    int maxLength = 500;
                    char* originalString = stringBuffer;
                    int someGlobal = *(int*)0x00D5E288; // Probably font or screen handle
                    int formattedCopy = FUN_008fe260(originalString, 500, someGlobal);
                    FUN_0097b440(formattedCopy, originalString, 500, someGlobal); // Display with timeout
                    return;
                }
            }
        }
    }
    else {
LAB_0098067b:
        // Alternative display path for mission end states
        result = FUN_00471610(); // Get current time or mission result text
        int timeOrText = result + 0x30; // Offset to append text
        FUN_0097b440(*(int*)(*(int*)0x0112A66C + 8), timeOrText, 500, *(int*)0x00D5E288);
    }
}