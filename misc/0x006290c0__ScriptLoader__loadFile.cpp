// FUNC_NAME: ScriptLoader::loadFile
// Function address: 0x006290c0
// Role: Loads a script or resource file (text or binary) into an internal token buffer.

// Assumed class layout (offsets from this):
// +0x08: m_pTokenCurrent (int*) - current write position in token buffer
// +0x0c: m_pTokenEnd (int*) - end of token buffer (read limit)
// +0x10: m_pStreamInfo (StreamInfo*) - pointer to stream info structure with fields:
//   +0x20: m_streamReadPos (unsigned int)
//   +0x24: m_streamSize (unsigned int)

// External helper function declarations (renamed based on behavior)
extern void flushBuffer();                          // FUN_00627360
extern int getNextTokenID();                        // FUN_00638920
extern FILE* getNullFileHandle();                   // FUN_00b995f7
extern void scriptDebugPrintf(int* format, char* str); // FUN_00625d40
extern void checkPreviousToken();                   // FUN_00633990
extern undefined4 readFileIntoBuffer();             // FUN_00626310
extern undefined4 handleFileError(int lineNum);     // FUN_006255e0
extern undefined4 finalizeLoad(undefined4 result);  // FUN_00625630
extern undefined4 reportError(int lineNum);         // FUN_00629050

// The function returns an undefined4 (likely an error code or handle)
undefined4 __thiscall ScriptLoader::loadFile(char *filename)
{
    undefined4 *pToken;
    undefined4 uVar2;
    int lineNum;
    int fileError;
    FILE *fileHandle;
    int *piVar7;
    FILE *local_204; // actual file handle used

    // Calculate expected line number from current buffer position
    // Each token is 8 bytes, so (current - end) >> 3 gives offset in tokens, +1 for 1-based line
    lineNum = (*(int *)(this + 8) - *(int *)(this + 0xc) >> 3) + 1;

    if (filename == (char *)0x0)
    {
        // No filename: load from internal default source (stdin?)
        // If stream read position is past stream size, flush buffer
        if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24))
        {
            flushBuffer();
        }
        // Write a new token of type 4 (e.g., string start) into the token buffer
        pToken = *(undefined4 **)(this + 8);
        *pToken = 4; // token type
        uVar2 = getNextTokenID();
        pToken[1] = uVar2; // token value (ID)
        *(int *)(this + 8) = *(int *)(this + 8) + 8; // advance buffer pointer
        local_204 = getNullFileHandle(); // get a placeholder file handle
    }
    else
    {
        // Load from a file
        scriptDebugPrintf((int*)&PTR_LAB_00e41624, filename);
        local_204 = _fopen(filename, "r");
    }

    if (local_204 == (FILE *)0x0)
    {
        // File open failed
    LAB_0062913c:
        uVar2 = reportError(lineNum);
        return uVar2;
    }

    // Peek at first character to determine if file is binary
    fileHandle = local_204;
    int firstChar = FID_conflict__getc(local_204);
    firstChar = _ungetc(firstChar, fileHandle);

    int isSpace = _isspace(firstChar);
    if (((isSpace == 0) && (firstChar = _isprint(firstChar), firstChar == 0)) &&
        (fileHandle = getNullFileHandle(), local_204 != fileHandle))
    {
        // Not printable and not space → treat as binary, reopen in binary mode
        _fclose(local_204);
        local_204 = _fopen(filename, "rb");
        if (local_204 == (FILE *)0x0) goto LAB_0062913c;
    }

    // Check if previous token was not type 4 (the one we just wrote? or the one before?)
    piVar7 = (int *)(*(int *)(this + 8) + -8); // get pointer to last written token
    if (((piVar7 != (int *)0x0) && (*piVar7 != 4)) &&
        (checkPreviousToken(),
         *(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)))
    {
        flushBuffer();
    }

    uVar2 = readFileIntoBuffer(); // parse the file data
    fileError = _ferror(local_204);
    fileHandle = getNullFileHandle();
    if (local_204 != fileHandle)
    {
        _fclose(local_204);
    }

    if (fileError != 0)
    {
        handleFileError(lineNum);
        uVar2 = reportError(lineNum);
        return uVar2;
    }

    finalizeLoad(uVar2);
    return uVar2;
}