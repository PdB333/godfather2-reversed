// FUNC_NAME: CSACrewComponent::showCSAMessage

// Reconstructed from 0x00983cd0 - Displays a CSA (Crew Style Action) message, likely a debug/log string

void CSACrewComponent::showCSAMessage(uint messageID, int extraData)
{
    // Temporary structure for string retrieval (size 0x10?)
    struct CSAStringBuffer {
        char *buffer;   // +0x00
        int capacity;   // +0x04
        int length;     // +0x08
        void (*deleter)(void *); // +0x0C function pointer for freeing
    } strBuf;

    memset(&strBuf, 0, sizeof(strBuf));

    // Retrieve the localized string for the given message ID (from a static table at 0x00d78708)
    Func_004d4ad0(&strBuf, PTR_LAB_00d78708, messageID);

    // If no string was found, use a fallback default string
    const char *message = strBuf.buffer;
    if (message == nullptr) {
        message = (const char *)&DAT_0120546e;  // "Unknown CSA message"
    }

    // Log/show the CSA message (format string at 0x00d77dc0, severity 2)
    Func_005a04a0("ShowCSAMessage", 0, &DAT_00d77dc0, 2, message, extraData);

    // Free the temporary string buffer if it was allocated
    if (strBuf.buffer != nullptr) {
        strBuf.deleter(strBuf.buffer);
    }
}