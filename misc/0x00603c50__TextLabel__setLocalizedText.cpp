// FUNC_NAME: TextLabel::setLocalizedText

void __thiscall TextLabel::setLocalizedText(char useAllocatedCopy) {
    // this pointer stored in EDI (unaff_EDI)
    // struct TextLabel: +0x00: some ID/hash (int), +0x04: char internalBuffer[?]
    int textId = *(int *)this;  // +0x00
    char *resourceStr = 0;      // local_10
    uint length = 0;            // local_c
    void *tempAlloc = 0;        // local_8
    void (*deleter)(void *) = 0; // local_4
    char *allocStr = 0;         // pcVar4
    char *src;
    
    // local_14 is a buffer (maybe output of string lookup)
    undefined4 lookupResult;
    
    if (textId != 0) {
        char bResult = FUN_006039d0(textId, &lookupResult, &useAllocatedCopy);
        if (bResult != 0) {
            // lookup succeeded
            if (useAllocatedCopy == 0) {
                FUN_004d3d90(lookupResult);  // maybe assign resource directly?
            } else {
                FUN_004ddaf0(lookupResult, &resourceStr);  // allocate new copy
            }
            
            // Check for bracketed string: e.g. "[text]"
            if ((length > 1) && (resourceStr[0] == '[') && (resourceStr[length - 1] == ']')) {
                FUN_004d3920(length - 1); // strip last bracket
                FUN_004d3920(0);          // strip first bracket (index 0)
            }
            
            allocStr = resourceStr;
            if (length > 11) {
                // Truncate: write a space (0x20) into internal buffer
                *(short *)((char *)this + 4) = 0x0020; // +0x04, space + null terminator
                goto cleanup;
            }
            src = resourceStr;
            if (resourceStr == 0) {
                // goto fallback default
                goto useDefault;
            }
        } else {
            goto useDefault;
        }
    } else {
useDefault:
        src = &DAT_0120546e; // default string constant
    }
    
    // Copy string to internal buffer at +0x04
    {
        char *dest = (char *)this + 4;
        char ch;
        do {
            ch = *src;
            *dest = ch;
            src++;
            dest++;
        } while (ch != '\0');
    }

cleanup:
    if (allocStr != 0) {
        // Call destructor function for allocated string
        deleter(allocStr);
    }
    return;
}