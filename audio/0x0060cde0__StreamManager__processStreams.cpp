// FUNC_NAME: StreamManager::processStreams
void StreamManager::processStreams(void)
{
    int streamType; // iVar1 - opcode/type of stream
    int streamParam; // iVar2 - additional parameter
    int *pManager; // piVar3 - another manager (e.g., network or audio)
    undefined4 *pStreamStruct; // puVar4 - current stream structure
    undefined1 *pStreamData; // puVar5 - pointer to stream data
    undefined4 currentTime; // uVar6 - current timestamp

    pStreamStruct = g_pStreamStruct; // DAT_0120584c
    *g_pStreamManagerCount = 0; // *DAT_0120584c = 0 (reset count/state)
    // Call vtable offset 0x30 (likely "process" on main manager)
    (**(code **)(*(int *)*g_pStreamManager + 0x30))((int *)*g_pStreamManager);

    // Process incoming/outgoing data
    FUN_0060c820(*(undefined4 *)(g_pStreamStruct + 0x20), // +0x20: stream index
                 g_pStreamManager, // DAT_01205840
                 *(undefined4 *)(g_pStreamStruct + 0xc), // +0x0c: some size/flags
                 g_streamAccumulator); // DAT_01205844

    FUN_006102c0(); // Global update (e.g., audio mix)

    pManager = g_pSecondaryManager; // DAT_01205750
    streamType = *(int *)(g_pStreamStruct + 4); // +0x04: stream type/opcode
    if (streamType == 0xd) { // Opcode 13 (reliable or special)
        streamParam = *(int *)(g_pStreamStruct + 8); // +0x08: additional data
        if (g_lastProcessedStreamId != *g_expectedStreamId) { // DAT_0120583c, DAT_01205848
            (**(code **)(*g_pSecondaryManager + 0x1a0))(g_pSecondaryManager, *g_expectedStreamId);
            g_lastProcessedStreamId = *g_expectedStreamId;
        }
        // Call vtable offset 0x148 (e.g., sendPacket with type 4, size = streamType/2)
        (**(code **)(*g_pSecondaryManager + 0x148))
                  (g_pSecondaryManager, 4, 0, 0,
                   *(undefined4 *)(g_pStreamStruct + 8), 0,
                   (uint)(streamType * 2) >> 2);
    } else {
        int vtable = *g_pSecondaryManager;
        currentTime = FUN_0060c9d0(); // Get current game time
        // Call vtable offset 0x144 (e.g., sendPacket with type streamType)
        (**(code **)(vtable + 0x144))(pManager, streamType, 0, currentTime);
    }

    streamParam = *(int *)(g_pStreamStruct + 0x20); // +0x20: stream index
    if (g_streamState1[streamParam] != 1) { // array at DAT_011da7f0
        (**(code **)(*g_pSecondaryManager + 0x198))(g_pSecondaryManager, streamParam, 1);
        g_streamState1[streamParam] = 1;
    }
    if (g_streamState2[streamParam] != 0) { // array at DAT_011da7f4
        (**(code **)(*g_pSecondaryManager + 400))(g_pSecondaryManager, streamParam, 0, 0, 0);
        g_streamState2[streamParam] = 0;
        g_streamAccumulator += *(int *)(g_pStreamStruct + 0x10); // +0x10: delta
        return;
    }
    g_streamAccumulator += *(int *)(g_pStreamStruct + 0x10); // +0x10: delta
    return;
}