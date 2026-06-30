// FUNC_NAME: PerformanceStreamManager::stopStreams
void PerformanceStreamManager::stopStreams(int param_1, int param_2)
{
    if (param_1 == 0) {
        return;
    }

    int *streamArrayEnd = (int *)(param_1 + 0xc + (uint)*(byte *)(param_1 + 0x6f) * 4);
    bool bAnyStopped = true;
    int *streamArrayStart = (int *)(param_1 + 0xc);

    if (param_2 == 1) {
        // Immediate stop all streams
        for (int *pStream = streamArrayStart; pStream < streamArrayEnd; pStream++) {
            if (*pStream != 0) {
                stopStreamInternal(*pStream);  // FUN_005f16b0
                *pStream = 0;
            }
        }
        // Clear some flags (bits 0-2 and bit 7? 0xff87 = 1111111110000111, clears bits 3-6)
        *(ushort *)(param_1 + 0x6c) = *(ushort *)(param_1 + 0x6c) & 0xff87;
        *(undefined4 *)(param_1 + 0x68) = 5; // PERFORMANCE_STATE_STOPPED
    } else {
        // Graceful stop: check each stream and stop if not already in stopping state
        for (int *pStream = streamArrayStart; pStream < streamArrayEnd; pStream++) {
            int streamPtr = *pStream;
            if (streamPtr != 0) {
                if ((*(byte *)(streamPtr + 0x10) & 0x40) == 0) {
                    // Not already stopping, so request stop
                    (**(code **)(*DAT_01223510 + 0x24))(*(undefined2 *)(streamPtr + 8)); // handle
                    requestStreamStop(*(undefined2 *)(streamPtr + 8), *(undefined4 *)(streamPtr + 0x18)); // FUN_005dbc10
                    beginStopStream(streamPtr); // FUN_005f1660
                }
                bAnyStopped = false;
            }
        }
        if (!bAnyStopped) {
            *(undefined4 *)(param_1 + 0x68) = 4; // PERFORMANCE_STATE_STOPPING
            goto updateState;
        }
        *(undefined4 *)(param_1 + 0x68) = 5; // PERFORMANCE_STATE_STOPPED
    }

updateState:
    char *stateStr = "PERFORMANCE_STATE_STOPPED";
    if (*(int *)(param_1 + 0x68) != 5) {
        stateStr = "PERFORMANCE_STATE_STOPPING";
    }
    logStateChange(stateStr); // FUN_005dbc10
    return;
}