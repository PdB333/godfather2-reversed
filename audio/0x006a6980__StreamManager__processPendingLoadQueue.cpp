// FUNC_NAME: StreamManager::processPendingLoadQueue
// Function address: 0x006a6980
// Processes up to 32 pending load requests from a fixed-size queue.
// When the pending flag at +0x9BC is set, iterates over the queue,
// calls processing function for each unprocessed request, then clears the flag.

struct LoadRequest {
    int requestId;       // +0x00
    int dataLow;         // +0x04  (first 4 bytes of 8-byte data)
    int dataHigh;        // +0x08  (second 4 bytes of 8-byte data)
    int extra1;          // +0x0C
    int extra2;          // +0x10
    char processed;      // +0x14  (byte flag)
    // padding to 24 bytes (0x18)
};

// Forward declarations of called functions
char __fastcall processLoadRequest(int requestId, int* outResult, int arg2, int arg3);
void __fastcall freeLoadedObject(int* objectPtr);

void __thiscall StreamManager::processPendingLoadQueue(StreamManager* this)
{
    int savedRequestId;
    __int64 savedData1;
    __int64 savedData2;
    int outResult[2];
    int currentIter;
    LoadRequest* request;

    if (*(char*)((int)this + 0x9BC) != 0) {
        // Save current active load state
        savedData1 = *(__int64*)((int)this + 0x6A8);
        savedData2 = *(__int64*)((int)this + 0x6B0);
        savedRequestId = *(int*)((int)this + 0x6A4);
        outResult[0] = 0;
        outResult[1] = 0;

        // Iterate over the 32 slots in the pending request queue
        request = (LoadRequest*)((int)this + 0x6BC);
        currentIter = 32;
        do {
            if (request->requestId != 0 && request->processed == 0) {
                // Temporarily set the current load to this request
                *(int*)((int)this + 0x6A4) = request->requestId;
                *(__int64*)((int)this + 0x6A8) = *(__int64*)&request->dataLow;
                *(__int64*)((int)this + 0x6B0) = *(__int64*)&request->extra1;

                // Process the request (likely loads asset data)
                request->processed = processLoadRequest(request->requestId, outResult, 0, 0);
            }
            request++;
            currentIter--;
        } while (currentIter != 0);

        // Restore previous active load state
        *(int*)((int)this + 0x6A4) = savedRequestId;
        *(__int64*)((int)this + 0x6A8) = savedData1;
        *(__int64*)((int)this + 0x6B0) = savedData2;

        // Clear the pending flag
        *(char*)((int)this + 0x9BC) = 0;

        // If the last processed request produced an output, free it
        if (outResult[0] != 0) {
            freeLoadedObject(outResult);
        }
    }
    return;
}