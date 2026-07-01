// FUNC_NAME: LocalizationManager::compareLocalizedStrings
void LocalizationManager::compareLocalizedStrings(int formatId1, int formatId2, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int *ptr1, *ptr2;
    char *str1, *str2;
    int handle1, handle2;
    int result1, result2;

    // Check if both string flags indicate availability
    if ((arg5 & 1) != 0 && (arg6 & 1) != 0) {
        // Get pointer to format string memory for both
        str1 = (char *)StringAlloc(&formatId1);  // FUN_004bb600
        str2 = (char *)StringAlloc(&formatId2);

        // Get actual string pointer (fallback to empty string)
        char *actualStr1 = (str1) ? str1 : emptyString; // DAT_0120546e
        char *actualStr2 = (str2) ? str2 : emptyString;

        // Resolve string to internal handle/ID
        handle1 = ResolveString(actualStr1);  // FUN_00568320
        handle2 = ResolveString(actualStr2);

        if (handle1 && handle2) {
            // Get string info objects
            result1 = GetStringInfo(&local8, &formatId1);  // FUN_008b3d60
            result2 = GetStringInfo(&local4, &formatId2);

            // Check if both info objects are valid and have content
            if (local8 && *(int *)(local8 + 4) && local4 && *(int *)(local4 + 4)) {
                // Compare first formatted string
                char *buffer1 = (char *)GetStringBuffer(&formatId1); // FUN_008b4100
                int vtable1 = *(int *)buffer1;
                unsigned int hash1 = (*(unsigned int (__thiscall **)(int))(*(int *)handle2 + 0xC))(); // vtable offset 0xC
                char cmpResult = (*(char (__thiscall **)(unsigned int))(vtable1 + 0x14))(hash1); // vtable offset 0x14

                if (cmpResult == '\0') {
                    // Compare second formatted string in reverse order
                    char *buffer2 = (char *)GetStringBuffer(&formatId2);
                    int vtable2 = *(int *)buffer2;
                    unsigned int hash2 = (*(unsigned int (__thiscall **)(int))(*(int *)handle1 + 0xC))();
                    cmpResult = (*(char (__thiscall **)(unsigned int))(vtable2 + 0x14))(hash2);
                }

                if (cmpResult == '\0') {
                    // Strings are equal, perform cleanup actions
                    char *buf1 = (char *)GetStringBuffer(&formatId1);
                    int vtable3 = *(int *)buf1;
                    unsigned int hashA = (*(unsigned int (__thiscall **)(int))(*(int *)handle2 + 0xC))();
                    (*(void (__thiscall **)(unsigned int))(vtable3 + 0xC))(hashA); // vtable offset 0xC

                    char *buf3 = (char *)GetStringBuffer(&formatId1 + 4); // local offset
                    (*(void (__thiscall **)(void))(**(int **)buf3))(); // vtable offset 0

                    (*(void (__thiscall **)(void))(*(int *)buf3 + 0x3C))(); // vtable offset 0x3C

                    char *buf4 = (char *)GetStringBuffer(&formatId2 + 4);
                    int vtable4 = *(int *)buf4;
                    unsigned int hashB = (*(unsigned int (__thiscall **)(int))(*(int *)this + 0xC))(); // using this
                    (*(void (__thiscall **)(unsigned int))(vtable4 + 0xC))(hashB);

                    char *buf5 = (char *)GetStringBuffer(&formatId2);
                    (*(void (__thiscall **)(void))(**(int **)buf5))();

                    (*(void (__thiscall **)(void))(*(int *)buf5 + 0x3C))();
                }
            }
        }
    }

    // Free allocated memory for arguments if non-zero
    if (arg3) FreeMemory(arg3);
    if (arg2) FreeMemory(arg2);
    if (arg1) FreeMemory(arg1);
    if (arg6) FreeMemory(arg6);
    if (arg5) FreeMemory(arg5);
    if (arg4) FreeMemory(arg4);
}