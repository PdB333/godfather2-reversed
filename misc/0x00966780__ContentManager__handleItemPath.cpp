// FUNC_NAME: ContentManager::handleItemPath
undefined4 __thiscall ContentManager::handleItemPath(int this, wchar_t *inputPath)
{
    wchar_t formattedPath[32]; // 64 bytes = 32 wchar_t
    int itemCount;
    int i;
    int cmpResult;
    wchar_t *pFormatted;
    wchar_t *pInput;
    wchar_t c1, c2;
    bool less;

    // If flag at +0x180 is set, clear it and return 1 (success?)
    if (*(char *)(this + 0x180) != '\0') {
        *(char *)(this + 0x180) = '\0';
        return 1;
    }

    itemCount = getItemCount(); // FUN_00962e40 - returns number of items
    if (itemCount != 0) {
        for (i = 0; i < itemCount; i++) {
            // Format: "/onli/mcMain/content_mc/item%d/hspt"
            formatString(formattedPath, L"/onli/mcMain/content_mc/item%d/hspt", i); // FUN_00910160

            // Compare formattedPath with inputPath (wide string comparison)
            pFormatted = formattedPath;
            pInput = inputPath;
            do {
                c1 = *pFormatted;
                c2 = *pInput;
                less = (c1 < c2);
                if (c1 != c2) {
                    cmpResult = (1 - (uint)less) - (uint)(less != 0);
                    goto checkMatch;
                }
                if (c1 == 0) break;
                c1 = pFormatted[1];
                c2 = pInput[1];
                less = (c1 < c2);
                if (c1 != c2) {
                    cmpResult = (1 - (uint)less) - (uint)(less != 0);
                    goto checkMatch;
                }
                pFormatted += 2;
                pInput += 2;
            } while (c1 != 0);
            cmpResult = 0;

checkMatch:
            if (cmpResult == 0) {
                // Match found: format another path with offset
                // DAT_00e3266c is likely L"/onli/mcMain/content_mc/item%d/offset" or similar
                formatString(formattedPath, &DAT_00e3266c, i - *(int *)(g_pContentManager + 0xc4)); // g_pContentManager = DAT_01129930
                // Send command "MoveOffset" with parameters
                sendCommand(L"MoveOffset", 0, &DAT_00d8cdec, 1, formattedPath); // FUN_005a04a0
            }
        }
    }
    return 0;
}