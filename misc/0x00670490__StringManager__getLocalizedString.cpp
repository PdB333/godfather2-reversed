// FUNC_NAME: StringManager::getLocalizedString
// Address: 0x00670490
// Retrieves a localized string by ID into a wide-character output buffer.
// The string ID is passed in EAX register (not a typical __thiscall parameter).
// Uses a request structure at offset +0x4 of 'this' to send the lookup.
// After lookup, copies the result (wide or narrow) to the output buffer.

void __thiscall StringManager::getLocalizedString(void *this, ushort *output)
{
    // 'this' points to a StringManager instance.
    // Internal data block at offset +0x4 (mStringRequest)
    int *requestData = *(int **)((int)this + 4);

    // Set up request header fields (likely a packet/command for string system)
    *(ushort *)(requestData + 0x1e28) = 3;        // +0x1e28: request type
    *(ushort *)(requestData + 0x1e2a) = 1;        // +0x1e2a: some flags
    *(ushort *)(requestData + 0x1e2c) = 0x409;    // +0x1e2c: message ID (likely "get string")
    *(ushort *)(requestData + 0x1e2e) = 1;        // +0x1e2e: version/size

    // The string ID is passed via EAX (register). 
    // Array of string entries at this + 40 (20 bytes per entry, indexed by ID).
    // Each entry contains a ushort key used in the lookup.
    ushort stringKey = *(ushort *)((int)this + (eax * 5 + 10) * 4); // eax = string ID

    // Perform the string lookup, storing result handle at this+8
    *(int *)((int)this + 8) = FUN_00671510(requestData, stringKey, &output);

    // Finish/process the lookup result
    FUN_00674e10();

    // Retrieve the string from the result structure (pointed by this+8)
    // The result contains either a wide string pointer at offset +0x54 or
    // a narrow string pointer at offset +0x50. Prefer wide if available.
    ushort *wideStr = *(ushort **)(*(int *)((int)this + 8) + 0x54);
    if (wideStr != (ushort *)0x0) {
        ushort ch = *wideStr;
        if (ch != 0) {
            do {
                wideStr++;
                *output = ch;
                output++;
                ch = *wideStr;
            } while (ch != 0);
        }
        *output = 0;
        return;
    }

    // No wide string; fall back to narrow (byte) string at +0x50
    byte *narrowStr = *(byte **)(*(int *)((int)this + 8) + 0x50);
    if (narrowStr != (byte *)0x0) {
        byte b = *narrowStr;
        while (b != 0) {
            narrowStr++;
            *output = (ushort)b; // convert to wide char
            output++;
            b = *narrowStr;
        }
    }
    *output = 0;
}