// FUNC_NAME: StreamManager::shutdown

void __fastcall StreamManager::shutdown(StreamManager* thisPtr)
{
    // Clear global resources (likely EA::StreamManager globals)
    releaseGlobal(&g_streamGlobal1);
    releaseGlobal(&g_streamGlobal2);
    releaseGlobal(&g_streamGlobal3);
    releaseGlobal(&g_streamGlobal4);
    releaseGlobal(&g_streamGlobal5);

    // Loop over 8 stream slots
    for (int i = 0; i < 8; ++i)
    {
        // Clear slot flag at [0x538 + i*40] // offset +0x00 per slot
        thisPtr->slotFlags[i] = 0;

        // Free slot data pointer at [0x53c + i*40] // offset +0x04 per slot
        if (thisPtr->slotData[i] != 0)
        {
            freeMemory(thisPtr->slotData[i]);
            thisPtr->slotData[i] = 0;
        }

        // Clear two fields of the current stream info array element
        // StreamInfo array at [0x558] with elements of size 0x28 (40 bytes)
        thisPtr->streamInfo[i].field0 = 0; // +0x00 relative to element
        thisPtr->streamInfo[i].field4 = 0; // +0x04 relative to element
    }

    // Call additional cleanup routine
    FUN_006a5740(); // likely clears stream data

    // Free two additional allocated members
    if (thisPtr->alloc1 != 0)
    {
        freeMemory(thisPtr->alloc1);
        thisPtr->alloc1 = 0;
    }
    if (thisPtr->alloc2 != 0)
    {
        freeMemory(thisPtr->alloc2);
        thisPtr->alloc2 = 0;
    }
}