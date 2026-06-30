// FUNC_NAME: BNKStreamManager::tryRegisterStream
int __thiscall BNKStreamManager::tryRegisterStream(StreamDescriptor* descriptor, int maxSlots, int* outSuccess)
{
    uint uVar1;
    int result;
    uint* globalEntry;
    int loopIndex;
    int lockResult;
    uint currentEntryActive;
    int bufferSize;
    uint* entryBuffer;

    *outSuccess = 0;
    if ((uint)(maxSlots - 1) > 0xff) { // maxSlots must be <= 256
        return -3;
    }

    // Look for an already-registered stream with matching ID
    globalEntry = g_streamIDTable; // DAT_00e275c0 (256 entries)
    do {
        if (((descriptor->state != 1) && (*descriptor->flags < 2)) &&
            (*descriptor->streamID <= *globalEntry) &&
            (*globalEntry <= *descriptor->streamID)) {
            *outSuccess = 1;
            goto exitSuccess;
        }
        globalEntry++;
    } while ((int)globalEntry < (int)(g_streamIDTable + 256));

    // Not found; attempt to lock the stream list and register
    result = acquireStreamListLock(&lockResult); // FUN_00669520
    if (result == 0) {
        if (lockResult != 1) {
            entryBuffer = (uint*)_calloc(4, 0x40); // allocate 64 uint (256 bytes)
            if (entryBuffer == NULL) {
                return -2;
            }
            result = 0;
            currentEntryActive = 0;
            bufferSize = 0x40;
            // Process each existing entry up to maxSlots
            for (loopIndex = 0; loopIndex < maxSlots; loopIndex++) {
                globalEntry = entryBuffer; // reuse buffer each iteration
                uVar1 = g_streamIDTable[loopIndex];
                // Clear buffer (actually the whole 256 bytes)
                _memset(entryBuffer, 0, bufferSize * 4);
                currentEntryActive = (uint)((uVar1 & 0xfffffff) != 0);
                *entryBuffer = uVar1 & 0xfffffff; // store the masked ID
                result = processExistingStreamEntry(descriptor, ¤tEntryActive, &lockResult); // FUN_006696f0
                if ((result != 0) || (lockResult == 0)) {
                    goto cleanup;
                }
            }
            *outSuccess = 1;
cleanup:
            // Zero out the portion of buffer that was used (currentEntryActive * 4 bytes)
            _memset(entryBuffer, 0, currentEntryActive * 4);
            _free(entryBuffer);
            return result;
        }
exitSuccess:
        result = 0;
    }
    return result;
}