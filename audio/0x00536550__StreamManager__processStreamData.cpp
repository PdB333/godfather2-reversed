// FUNC_NAME: StreamManager::processStreamData
// Address: 0x00536550
// This function handles incoming data streams based on stream IDs (stored at +0x10 and +0x14).
// It copies data from various source buffers to destination buffers depending on the stream type.

int __thiscall StreamManager::processStreamData(int thisPtr)
{
    int streamId1;
    int streamId2;
    int result;

    debugEnter(); // FUN_00612a60 - likely debug/profiling

    streamId1 = *(int *)(thisPtr + 0x10); // m_streamId1
    if (streamId1 == *(int *)(thisPtr + 0x160)) // m_expectedIdA (type A)
    {
        // Copy 8 bytes from source at +0x130 to dest at +0xE0
        result = copy8Bytes(streamId1,
                            *(int *)(thisPtr + 0x130),  // m_sourceA
                            (void *)(thisPtr + 0xE0),    // m_destA
                            8);
    }
    else
    {
        if ((streamId1 == *(int *)(thisPtr + 0x174)) && (streamId1 != 0)) // m_expectedIdB (type B)
        {
            if (*(int *)(thisPtr + 0x134) != 0) // m_sourceB1
            {
                copy8Bytes(streamId1,
                           *(int *)(thisPtr + 0x134),  // m_sourceB1
                           (void *)(thisPtr + 0xE0),    // m_destA
                           8);
            }
            if (*(int *)(thisPtr + 0x148) != 0) // m_sourceB2
            {
                copyWithLength(streamId1,
                               *(int *)(thisPtr + 0x148),  // m_sourceB2
                               *(int *)(thisPtr + 0x128)); // m_lengthB
            }
            streamId1 = *(int *)(thisPtr + 0x15c); // m_extraPtr
            if (streamId1 == 0) goto LAB_005366aa;
            // Fall through to generic copy below
            result = copyData(streamId1,
                              *(int *)(thisPtr + 0x10),    // m_streamId1
                              (void *)(thisPtr + 0x110));  // m_destB
        }
        else if ((streamId1 == *(int *)(thisPtr + 0x178)) && (streamId1 != 0)) // m_expectedIdC (type C)
        {
            if (*(int *)(thisPtr + 0x138) != 0) // m_sourceC1
            {
                copyData(streamId1,
                         *(int *)(thisPtr + 0x138),  // m_sourceC1
                         (void *)(thisPtr + 0x100)); // m_destC1
            }
            if (*(int *)(thisPtr + 0x12C) != 0) // offset 300 = 0x12C, m_sourceC2
            {
                copyData(*(int *)(thisPtr + 0x10),   // m_streamId1
                         *(int *)(thisPtr + 0x12C),  // m_sourceC2
                         (void *)(thisPtr + 0xC0));  // m_destC2
            }
            if (*(int *)(thisPtr + 0x154) != 0) // m_sourceC3
            {
                copyData(*(int *)(thisPtr + 0x10),   // m_streamId1
                         *(int *)(thisPtr + 0x154),  // m_sourceC3
                         (void *)(thisPtr + 0xD0));  // m_destC3
            }
            if (*(int *)(thisPtr + 0x144) != 0) // m_sourceC4
            {
                copyWithLength(*(int *)(thisPtr + 0x10),   // m_streamId1
                               *(int *)(thisPtr + 0x144),  // m_sourceC4
                               *(int *)(thisPtr + 0x128)); // m_lengthC
            }
            streamId1 = *(int *)(thisPtr + 0x158); // m_extraPtr2
            if (streamId1 == 0) goto LAB_005366aa;
            result = copyData(streamId1,
                              *(int *)(thisPtr + 0x10),    // m_streamId1
                              (void *)(thisPtr + 0x110));  // m_destB
        }
        else
        {
            if ((streamId1 != g_specialStreamId) || (g_specialFlag == 0)) // globals
                goto LAB_005366aa;
            // Special global stream
            result = copyData(streamId1,
                              g_specialData,           // global data pointer
                              (void *)&g_globalDest);  // global dest buffer
        }
    }

LAB_005366aa:
    streamId2 = *(int *)(thisPtr + 0x14); // m_streamId2
    if (streamId2 == *(int *)(thisPtr + 0x17C)) // m_expectedIdD (type D)
    {
        result = *(int *)(thisPtr + 0x120); // m_someValue
        if (*(int *)(thisPtr + 0x13C) != 0) // m_flushFlag
        {
            result = flushStream(); // FUN_006063b0
            return result;
        }
    }
    else if (streamId2 == g_globalStreamId2) // global
    {
        copyData(streamId2, g_globalData2, (void *)(thisPtr + 0xC0));
        result = *(int *)(thisPtr + 0x120);
        if (g_globalFlag != 0)
        {
            result = flushStream();
            return result;
        }
    }
    else
    {
        if (streamId2 == *(int *)(thisPtr + 0x16C)) // m_expectedIdE
        {
            result = copyWithLength(streamId2,
                                    *(int *)(thisPtr + 0x140),  // m_sourceE
                                    *(int *)(thisPtr + 0x124)); // m_lengthE
            return result;
        }
        if (streamId2 == *(int *)(thisPtr + 0x170)) // m_expectedIdF
        {
            copyWithLength(streamId2,
                           *(int *)(thisPtr + 0x14C),  // m_sourceF
                           0xFFB);                     // fixed length 4091
            result = copyData(*(int *)(thisPtr + 0x14),   // m_streamId2
                              *(int *)(thisPtr + 0x150),  // m_sourceF2
                              (void *)(thisPtr + 0xB0));  // m_destF
        }
    }
    return result;
}