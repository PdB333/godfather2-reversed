// FUNC_NAME: StreamManager::cancelAsyncRequest
void StreamManager::cancelAsyncRequest(int slotIndex, AsyncRequest* request, undefined4 param_3, undefined4 param_4)
{
    if (request != 0) {
        if (request->isActive != 0) { // +0x1c
            goto finishCancel;
        }
        processPendingOperations(); // FUN_0060b870
        if (request->isActive != 0) {
            EnterCriticalSection(&g_requestListMutex); // DAT_012224c0
            int i = 0;
            if (0 < g_activeRequestCount) { // DAT_01205850
                do {
                    if (g_activeRequests[i] == request) { // DAT_011da8f0
                        g_activeRequestCount--;
                        if (0 < g_activeRequestCount) {
                            g_activeRequests[i] = g_activeRequests[g_activeRequestCount];
                        }
                        break;
                    }
                    i++;
                } while (i < g_activeRequestCount);
            }
            LeaveCriticalSection(&g_requestListMutex);
            if (request->isActive != 0) {
finishCancel:
                completeAsyncCancel(slotIndex, request, param_3, param_4); // FUN_0060c820
                return;
            }
        }
    }
    // Update state flags for this slot
    if (g_slotActiveFlag[slotIndex] != 1) { // DAT_011da7f0
        (*(g_streamManager->vtable->setSlotActive))(g_streamManager, slotIndex, 1); // vtable+0x198
        g_slotActiveFlag[slotIndex] = 1;
    }
    if (g_slotErrorFlag[slotIndex] != 0) { // DAT_011da7f4
        (*(g_streamManager->vtable->clearSlotError))(g_streamManager, slotIndex, 0, 0, 0); // vtable+400
        g_slotErrorFlag[slotIndex] = 0;
    }
    return;
}