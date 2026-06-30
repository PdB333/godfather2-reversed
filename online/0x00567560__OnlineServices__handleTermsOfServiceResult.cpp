// FUNC_NAME: OnlineServices::handleTermsOfServiceResult
void __thiscall OnlineServices::handleTermsOfServiceResult(int thisPtr, char *tosString)
{
    char *pcVar1;
    char *pcVar2;
    void *newBuffer;
    int strLen;

    thisPtr->state = 4;  // +0x10: state (initializing)

    // Free previous string buffer if allocated
    if (thisPtr->dialogString != 0) {  // +0x20: current dialog string pointer
        thisPtr->dialogLength = 0;   // +0x24: length
        freeString(thisPtr->dialogString);  // FUN_009c8f10
    }

    // Store the Terms of Service string
    if (tosString == 0) {
        // Default error message
        thisPtr->dialogString = "An error occurred when receiving Terms of Service";
        pcVar1 = thisPtr->dialogString;
        do {
            pcVar2 = pcVar1;
            pcVar1 = pcVar2 + 1;
        } while (*pcVar2 != '\0');
        // Calculate length: pointer to null minus start minus 1? The decompiled code does weird arithmetic,
        // but likely sets to strlen of the string (approximately 50 chars)
        thisPtr->dialogLength = (int)pcVar1 - (int)(thisPtr->dialogString + 1);  // +0x24
    }
    else {
        pcVar1 = tosString;
        do {
            pcVar2 = *pcVar1;
            pcVar1 = pcVar1 + 1;
        } while (pcVar2 != '\0');
        strLen = (int)pcVar1 - (int)(tosString + 1);  // strlen minus 1? Actually strlen = (int)pcVar1 - (int)tosString - 1? Wait, pcVar1 points to after null, so length = pcVar1 - (tosString+1) = strlen(tosString) - 1? That would be off by one. Probably Ghidra misinterpreting, but we'll keep as is.
        thisPtr->dialogLength = strLen;  // +0x24
        newBuffer = allocateMemory(strLen + 1);  // FUN_009c8e80: allocate bytes
        thisPtr->dialogString = newBuffer;  // +0x20
        _memcpy(newBuffer, tosString, thisPtr->dialogLength + 1);
    }

    // Check flag at bit 2 (0x4 mask)
    if ((thisPtr->flags & 0x4) == 0) {  // +0x2c: bitfield
        thisPtr->substate = 2;  // +0x14: substate (char)
        thisPtr->state = 0;     // +0x10: state (idle/complete)
        return;
    }
    // Clear bit 7 (0x80 mask)
    thisPtr->flags = thisPtr->flags & 0xFFFFFF7F;  // +0x2c
    return;
}