// FUNC_NAME: ResourceManager::loadLocalizedString
void __thiscall ResourceManager::loadLocalizedString(int thisPtr, int resourceInfo)
{
    undefined4 globalContext;
    int iVar2;
    undefined1 *defaultEmptyStr = &DAT_0120546e; // empty string constant
    undefined1 *string1 = 0;
    undefined4 string1_size = 0;
    undefined4 string1_unk = 0;
    code *string1_destructor = 0;
    undefined1 *string2 = 0;
    undefined4 string2_size = 0;
    undefined4 string2_unk = 0;
    code *string2_destructor = 0;
    undefined1 *string3 = 0;
    undefined4 string3_size = 0;
    undefined4 string3_unk = 0;
    code *string3_destructor = 0;

    char pathBuffer [4112]; // temporary buffer for path construction

    globalContext = DAT_012234a4; // global context token (e.g., registry handle)

    FUN_00604be0(); // push context / begin scope

    // Initialize three dynamically allocated string objects (resource lookups)
    FUN_00603330(0x5e5bfcbb, &string1); // hash for root name (e.g., "mission")
    FUN_00603330(*(undefined4 *)(resourceInfo + 0xb4), &string2); // resource name hash
    iVar2 = *(int *)(resourceInfo + 0x204);
    if (iVar2 == 0) {
        iVar2 = *(int *)(resourceInfo + 0x100); // fallback hash
    }
    FUN_00603330(iVar2, &string3); // asset type hash

    // Set name (0x6e = 'n') and resource (0x72 = 'r') strings
    if (string2 == 0) {
        string2 = defaultEmptyStr;
    }
    FUN_00604c10(0x6e, string2); // store as "name" component

    if (string3 == 0) {
        string3 = defaultEmptyStr;
    }
    FUN_00604c10(0x72, string3); // store as "resource" component

    // Build full path string using name and resource
    {
        undefined1 *resultString = 0;
        undefined4 resultSize = 0;
        undefined4 resultUnk = 0;
        code *resultDestructor = 0;

        if (string1 == 0) {
            string1 = defaultEmptyStr;
        }
        FUN_006038a0(globalContext, pathBuffer, &resultString, string1);
        // resultString now holds the path constructed via registry

        if (resultString == 0) {
            resultString = defaultEmptyStr;
        }
        // Load file content into this->buffer (+0xf0) with max size 0x100
        FUN_005c4660(*(undefined4 *)(thisPtr + 0xf0), resultString, 0x100, resultSize);

        FUN_00977ec0(); // post-load processing (e.g., decompress, decode)

        // Cleanup result string
        if (resultString != 0) {
            (*resultDestructor)(resultString);
        }
    }

    // Cleanup dynamically allocated strings
    if (string3 != 0) {
        (*string3_destructor)(string3);
    }
    if (string2 != 0) {
        (*string2_destructor)(string2);
    }
    if (string1 != 0) {
        (*string1_destructor)(string1);
    }

    FUN_00604c00(); // pop context / end scope
    return;
}