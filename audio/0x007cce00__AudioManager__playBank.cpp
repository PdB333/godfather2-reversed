// FUNC_NAME: AudioManager::playBank
void __thiscall AudioManager::playBank(int thisPtr, int bankId, int fadeTimeMs)
{
    // mCurrentStream is at +0x1b0
    int *pCurrentStream = *(int **)(thisPtr + 0x1b0);
    
    // If a bank is already loaded and its ID matches, do nothing
    if (pCurrentStream != 0 && *(int *)(pCurrentStream + 0x94) == bankId)
        return;
    
    // Stop the current bank if different
    FUN_007cb510(0);
    
    // --- Linked list manipulation for "stop" and "play" actions ---
    // local_20 and local_1c are temporary nodes for a list chain.
    // They appear to be used as stack-based sentinel nodes for the stop list.
    int stopListHead = 0;
    int stopListPrevNext = 0; // actually the "next" pointer of the first node
    int stopListDummy = 0;
    int stopListDummyNext = 0;
    int stopListDummyPrev = 0; // unused
    
    // This block appears to save and replace the next pointer of a structure at this+0x58 (maybe "stopList" or "channelList")
    int *pChannelList = *(int **)(thisPtr + 0x58);
    if (pChannelList != 0 && (pChannelList + 0x48) != 0)
    {
        stopListPrevNext = *(int *)(pChannelList + 0x4c); // save previous next
        *(int **)(pChannelList + 0x4c) = &stopListHead;   // replace with our local head
        stopListHead = (int)(pChannelList + 0x48);         // point to the list node
    }
    
    // Another list at this+0x1b4 (maybe "playList" or "activeStreams")
    int *pPlayList = *(int **)(thisPtr + 0x1b4);
    int playListDummy = 0;
    int playListDummyNext = 0;
    int playListDummyPrev = 0;
    
    if (&playListDummy != (int *)(thisPtr + 0x1b4) && pPlayList != 0)
    {
        playListDummyPrev = 0;
        playListDummy = (int)pPlayList;
        if (pPlayList != 0)
        {
            playListDummyNext = *(int *)(pPlayList + 4); // save next
            *(int **)(pPlayList + 4) = &playListDummy;    // replace with our dummy
        }
    }
    
    // Set the bank ID in the temporary node (local_4)
    int newBankNode = bankId; // local_4
    
    // Allocate a new bank stream if not existing
    if (*(int *)(thisPtr + 0x1b0) == 0)
    {
        int *newStream = (int *)FUN_0043b910(0x98, 0);
        if (newStream != 0)
        {
            int *streamObj = (int *)FUN_006ccef0();
            *(int **)(thisPtr + 0x1b0) = streamObj;
        }
        else
        {
            *(int **)(thisPtr + 0x1b0) = 0;
        }
    }
    
    // Process the stop list (local_20 chain)
    FUN_006cd750(&stopListHead);
    
    // Set fade parameters from global state (volume, pitch, pan)
    int fadeParams[3];
    fadeParams[0] = DAT_00d5eee4;  // maybe volume
    fadeParams[1] = DAT_00d620ac;  // maybe pitch/pan
    fadeParams[2] = DAT_00d5d740;  // maybe pan or fade time
    FUN_0041e790(fadeParams, fadeTimeMs);
    
    // Actually start playback on the new stream
    // The first argument is derived from a global array plus the channel list pointer (weird offset)
    int *pChannelList2 = *(int **)(thisPtr + 0x58); // same as above
    // DAT_00002494 appears to be a base address for channel data; iVar1 is the channel list pointer
    int *channelData = (int *)((char *)&DAT_00002494 + (int)pChannelList2);
    FUN_00424dc0(*channelData, *(int *)(thisPtr + 0x1b0), fadeTimeMs, 1, 0);
    
    // Cleanup: remove temporary nodes from the linked lists
    if (playListDummy != 0)
        FUN_004daf90(&playListDummy);
    if (stopListHead != 0)
        FUN_004daf90(&stopListHead);
}