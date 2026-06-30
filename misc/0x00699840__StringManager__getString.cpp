// FUNC_NAME: StringManager::getString
uint __thiscall StringManager::getString(int this, int stringId, char* outBuf, size_t bufSize)
{
    char* sourcePtr;            // originally pcVar3
    int* pData;                 // originally piVar2
    size_t actualLen;           // originally sVar1
    char* tempBuf;              // reused param_3 alias
    uint resultFlags;           // originally param_3 used as integer

    // Initialize output buffer to empty string
    *outBuf = '\0';
    sourcePtr = nullptr;

    // Get pointer to internal string table entry; FUN_00698c00 may modify tempBuf (alias for outBuf?)
    // Note: &outBuf is passed as char** – likely the function returns a pointer to the actual string data
    pData = (int*)FUN_00698c00(&outBuf, stringId);

    // Check if the string belongs to this object (object ID stored at this+0x04)
    if (*pData == this + 4)
    {
        // Clear low byte of outBuf (used as flags) – indicates the string is "empty" or default
        outBuf = (char*)((uint)outBuf & 0xFFFFFF00);
    }
    else
    {
        // Call known function to process the string data (probably allocate or copy)
        FUN_004d3e20(*pData + 0x20);

        actualLen = bufSize;
        // Set low byte of outBuf to 1 (mark success or "valid") – high bytes unchanged from previous
        outBuf = (char*)((uint)outBuf | 1);

        // Determine source string; if null, use a default string constant
        sourcePtr = (char*)0x0;
        // Note: decompiled shows CONCAT31 on param_3 bytes – likely sourcePtr is derived from some flag in outBuf originally
        // But sourcePtr remains null in this path (pcVar3 = 0), so we use default
        if (sourcePtr == nullptr)
        {
            sourcePtr = &DAT_0120546e; // "Default" or empty string literal
        }

        // Safe copy into output buffer
        strncpy(outBuf, sourcePtr, bufSize);
        outBuf[actualLen - 1] = '\0';
    }

    // If source pointer was set (maybe from a different path), call virtual destructor or release
    if (sourcePtr != nullptr)
    {
        // Null dereference in decompiled – likely a vtable call: sourcePtr->Release() or similar
        // Placeholder: (*(sourcePtr->vtable->someMethod))(sourcePtr, sourcePtr, 0, 0);
        ((void(*)(char*,char*,int,int))0x0)(sourcePtr, sourcePtr, 0, 0); // original artifact
    }

    // Return the low byte of the outBuf flags (0 = empty, 1 = success)
    return (uint)outBuf & 0xFF;
}