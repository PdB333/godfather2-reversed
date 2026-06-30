// FUNC_NAME: SubtitleManager::registerTextEntry
void __thiscall SubtitleManager::registerTextEntry(int this, undefined4 param_2, char *text, undefined4 param_4, char *urlParams, int *outId)
{
    int *entryData;
    int entryCount;
    int newId;
    int *entryPtr;
    char *pcVar5;
    undefined4 *puVar6;

    if (*outId == 0)
    {
        // Add new entry
        entryData = (int *)(this + 0x14); // +0x14: entryCount
        entryCount = *(int *)(this + 0x14) + 1;
        if (*(int *)(this + 0x18) < entryCount) // +0x18: capacity
        {
            uVar3 = reallocArray(*(undefined4 *)(this + 0x10), entryCount, 0x114, entryData, this + 0x18);
            *(undefined4 *)(this + 0x10) = uVar3; // +0x10: data pointer
        }
        entryPtr = (int *)(*entryData * 0x114 + *(int *)(this + 0x10));
        *entryData = *entryData + 1;

        newId = hashString(text);
        entryPtr[0] = newId; // +0: id
        *outId = newId;

        _strncpy((char *)&entryPtr[1], text, 0x40); // +4: text (64 chars)

        // Find last '/' in text and null-terminate after it (extract directory path?)
        int *piVar4 = &entryPtr[1];
        while (*piVar4 != '\0')
            piVar4++;
        for (pcVar5 = (char *)((int)piVar4 + (-1 - ((int)entryPtr + 5))); -1 < (int)pcVar5; pcVar5--)
        {
            if (*(char *)((int)entryPtr[1] + (int)pcVar5) == '/')
            {
                ((int)entryPtr + (int)pcVar5 + 4)[0] = '\0';
                break;
            }
        }

        // Extract _var= parameter
        pcVar5 = _strstr(urlParams, "_var=");
        if ((pcVar5 == (char *)0x0) || ((pcVar5 + 5) == (char *)0x0))
            puVar6 = (undefined4 *)0x0;
        else
        {
            _strncpy((char *)&g_tempBuffer, pcVar5 + 5, 0x40);
            g_tempBuffer[0x3F] = '\0';
            pcVar5 = _strchr((char *)&g_tempBuffer, '&');
            if (pcVar5 != (char *)0x0)
                *pcVar5 = '\0';
            puVar6 = &g_tempBuffer;
        }
        __snprintf((char *)(entryPtr + 0x11), 0x40, "%s/%s", &entryPtr[1], puVar6); // +0x44: varName

        // Extract _mc= parameter
        pcVar5 = _strstr(urlParams, "_mc=");
        if ((pcVar5 == (char *)0x0) || ((pcVar5 + 4) == (char *)0x0))
            pcVar5 = (char *)0x0;
        else
        {
            _strncpy((char *)&g_tempBuffer, pcVar5 + 4, 0x40);
            g_tempBuffer[0x3F] = '\0';
            pcVar5 = _strchr((char *)&g_tempBuffer, '&');
            if (pcVar5 != (char *)0x0)
                *pcVar5 = '\0';
            pcVar5 = (char *)&g_tempBuffer;
        }
        _strncpy((char *)(entryPtr + 0x21), pcVar5, 0x40); // +0x84: mc?

        // Extract _textinst= parameter
        pcVar5 = _strstr(urlParams, "_textinst=");
        if ((pcVar5 == (char *)0x0) || ((pcVar5 + 10) == (char *)0x0))
            pcVar5 = (char *)0x0;
        else
        {
            _strncpy((char *)&g_tempBuffer, pcVar5 + 10, 0x40);
            g_tempBuffer[0x3F] = '\0';
            pcVar5 = _strchr((char *)&g_tempBuffer, '&');
            if (pcVar5 != (char *)0x0)
                *pcVar5 = '\0';
            pcVar5 = (char *)&g_tempBuffer;
        }
        _strncpy((char *)(entryPtr + 0x31), pcVar5, 0x40); // +0xC4: textInst

        entryPtr[0x43] = 10; // +0x10C: some field (maybe type/flags), default 10
        entryPtr[0x44] = 0;  // +0x110: alignment (default 0)

        // Check for _align= parameter
        pcVar5 = _strstr(urlParams, "_align=");
        if ((pcVar5 != (char *)0x0) && (pcVar5 != (char *)0xFFFFFFF9))
        {
            int align = parseAlignmentString(); // FUN_005c71e0 returns alignment enum
            if (align == 1)
            {
                entryPtr[0x44] = g_alignmentGlobal1; // DAT_00e4481c
                return;
            }
            if (align == 2)
            {
                entryPtr[0x44] = g_alignmentGlobal2; // DAT_00e44818
                return;
            }
        }
    }
    else
    {
        // Modify existing entry by id
        int i = 0;
        if (*(int *)(this + 0x14) > 0)
        {
            int *data = *(int **)(this + 0x10);
            int *ptr = data;
            while (*ptr != *outId)
            {
                i++;
                ptr += 0x45; // each entry is 0x45 ints = 0x114 bytes
                if (*(int *)(this + 0x14) <= i)
                    return; // not found
            }
            if (i >= 0)
            {
                // Set flag: clear bits 3-5 and set bit 1
                data[i * 0x45 + 0x43] = (data[i * 0x45 + 0x43] & 0x38U) | 2;
            }
        }
    }
    return;
}