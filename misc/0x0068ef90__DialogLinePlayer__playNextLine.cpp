// FUNC_NAME: DialogLinePlayer::playNextLine
void __thiscall DialogLinePlayer::playNextLine(void *thisPtr, int context) {
    // +0x04: state (0=idle, 1=playing, 2=finished)
    // +0x08: flags (bit 1 = enabled)
    // +0x0c: dataSource (pointer)
    // +0x10: linePlayedFlag
    // +0x14: currentLineIndex (-1 = no limit)
    char *lineText;
    int state = *(int *)((char *)thisPtr + 4);
    char flags = *(char *)((char *)thisPtr + 8);
    int limit = *(int *)((char *)thisPtr + 0x14);
    int dataSource = *(int *)((char *)thisPtr + 0xc);

    // Check if enabled, state less than 3, and dataSource is valid
    if ((flags & 2) != 0 && state < 3) {
        int *sourceStruct = (int *)FUN_004973e0(dataSource);
        if (sourceStruct != NULL) {
            int uVar5 = sourceStruct[1];
            int uVar1 = sourceStruct[0];
            // Iterate up to 2 lines or until limit (if limit != -1)
            int i;
            for (i = 0; (limit == -1 || i < limit) && i < 2; i++) {
                char lineChar = FUN_0049a870(uVar1, uVar5, i);
                if (lineChar != 0) {
                    int tempObj[3]; // local_10
                    code *destructor; // local_4
                    lineText = (char *)FUN_0068ebf0(tempObj, lineChar, context);
                    if (lineText == NULL) {
                        lineText = (char *)0x0120546e; // Default empty string?
                    }
                    FUN_004d3d90(lineText);
                    *(char *)((char *)thisPtr + 0x10) = 1; // Mark line played
                    if (tempObj[0] != 0) {
                        (*destructor)(tempObj[0]); // Cleanup temporary
                    }
                    // Guard: re-check enabled and state
                    flags = *(char *)((char *)thisPtr + 8);
                    state = *(int *)((char *)thisPtr + 4);
                    if ((flags & 2) != 0 && state < 3) {
                        *(int *)((char *)thisPtr + 4) = 2; // Advance state
                    }
                    *(int *)((char *)thisPtr + 0x14) = i; // Store current index
                    return;
                }
            }
            // If no line found and state is idle
            if (*(int *)((char *)thisPtr + 4) == 0) {
                char *defaultText = (char *)FUN_0068b910(0x33371f37);
                FUN_004d3d90(defaultText);
                *(char *)((char *)thisPtr + 0x10) = 1;
                flags = *(char *)((char *)thisPtr + 8);
                state = *(int *)((char *)thisPtr + 4);
                if ((flags & 2) != 0 && state < 3) {
                    *(int *)((char *)thisPtr + 4) = 2;
                }
            }
        }
    }
    return;
}