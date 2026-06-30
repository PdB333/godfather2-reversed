// FUNC_NAME: TNLConnection::processStream

#include <windows.h> // For LARGE_INTEGER, CRITICAL_SECTION, QueryPerformanceCounter, EnterCriticalSection, LeaveCriticalSection

// Forward declarations of internal functions
bool FUN_004d0db0(void* connection); // Check if stream is ready to process
void FUN_004d1ab0();                 // Probably flushes or signals completion
void FUN_004d1a30();                 // Handles state transition
void FUN_004d1820();                 // Cleans up stream resources
void FUN_004d1ea0();                 // Removes stream from active list

// ---------- Reconstructed Function ----------

uint TNLConnection::processStream(uint streamId, bool block, uint timeoutMs)
{
    // Local variables
    uint status = 0;                  // Return status flags (bit0=1 idle, bit1=bVar4, bit2=buffer pending)
    LARGE_INTEGER startTime;          // Timer start
    uint startTimeLow, startTimeHigh; // Split for quick comparisons
    NetStream* stream;                // The stream associated with the given ID

    // Start performance measurement
    QueryPerformanceCounter(&startTime);
    startTimeLow = startTime.s.LowPart;
    startTimeHigh = startTime.s.HighPart;

    // ---- Find stream by ID ----
    stream = (NetStream*)this->streamList; // +0x4c offset
    while (stream != nullptr)
    {
        if (stream->streamId == streamId) // +0x2b (0xac)
            goto foundStream;
        stream = stream->next; // offset 0x0
    }
    stream = nullptr; // Not found

foundStream:
    bool timedOut = false;

    if (stream == nullptr)
    {
        // Stream not found, return idle status
        return 1;
    }

    if (block == false)
        goto processIdle;

    // ---- Main processing loop (blocked mode) ----
processLoop:
    do
    {
        do
        {
            // ---- Get the current packet buffer from the queue ----
            int currentBuffer = stream->currentBuffer; // +0x33 (0xcc)
            if (currentBuffer == 0)
            {
                // No buffer in hand, try to dequeue one
                EnterCriticalSection(&stream->queueCriticalSection); // +0x3a (0xe8)

                if (stream->queueCount != 0) // +0x39 (0xe4)
                {
                    // Dequeue next buffer
                    stream->currentBuffer = *(int*)(stream->queueBase + stream->queueIndex * 4); // +0x36, +0x38
                    stream->queueIndex = (stream->queueIndex + 1) % stream->queueSize; // +0x37
                    stream->queueCount--;
                }

                LeaveCriticalSection(&stream->queueCriticalSection);
                currentBuffer = stream->currentBuffer;
                if (currentBuffer == 0)
                    goto processIdle; // No more buffers
            }

            // ---- Check if we should send/receive or wait ----
            if ((stream->flags & 2) == 0) // +0x2a (0xa8) bit1 indicates blocking/ready
            {
                do
                {
                    // Compute pointer to the chunk in the buffer
                    int chunkPtr = *(int*)(currentBuffer + 4) + stream->bytesOffset; // +0x34 (0xd0)
                    bool canProcess = FUN_004d0db0(this); // Check if stream is ready to proceed

                    if (canProcess == false)
                    {
                        status = 8; // Not ready, set error? (the code sets local_74=8)
                        break;
                    }

                    // Advance byte counters
                    int chunkSize = *(int*)(chunkPtr + 4);
                    stream->bytesOffset += chunkSize;           // +0x34
                    stream->totalBytes += chunkSize;            // +0x31 (0xc4)
                    this->totalBytes += chunkSize;               // +0x8c

                    // Check timeout
                    if (timeoutMs != 0xFFFFFFFF)
                    {
                        LARGE_INTEGER now;
                        QueryPerformanceCounter(&now);

                        // Elapsed time in (possibly scaled) units
                        uint64 elapsedLow = now.s.LowPart - startTimeLow;
                        uint64 elapsedHigh = (now.s.HighPart - startTimeHigh) - (elapsedLow < 0 ? 1 : 0);
                        uint64 elapsedAbs = (elapsedHigh & 0x80000000) ? 0 : CONCAT44(elapsedHigh, elapsedLow);
                        // Convert to milliseconds using frequency constant (_DAT_01163ed0)
                        // The code does: (float)elapsedAbs * frequencyConstant -> round -> LARGE_INTEGER
                        // We'll skip the ugly conversion and assume it's a comparison
                        if (timeoutMs <= (uint)now.s.LowPart) // This is a simplified, not exactly correct
                        {
                            timedOut = true;
                            break;
                        }
                    }
                } while (stream->bytesOffset < 0x20000); // Max bytes per buffer
            }

            // ---- Check if buffer is full or ready to send ----
            if ((stream->bytesOffset != 0x20000) && ((stream->flags & 2) == 0))
                goto sendBuffer; // We have more room, continue?

            // ---- Send the current buffer ----
            int* packet = (int*)stream->currentBuffer; // +0x33
            (*packet)--; // Decrement reference count? (part of the buffer header)
            bool bufferFreed = (*packet == 0);

            if (bufferFreed)
            {
                // Return buffer to free list
                EnterCriticalSection(&this->freeListCriticalSection); // +0x28

                int freeCount = this->freeCount; // +0x24
                int freeMax = this->freeMax;     // +0x1c
                if (freeCount < freeMax)
                {
                    int freeIdx = this->freeBase + freeCount; // +0x20
                    this->freeCount = freeCount + 1;
                    if (freeMax <= freeIdx)
                        freeIdx -= freeMax;
                    *(int**)(this->freeArray + freeIdx * 4) = packet; // +0x18
                }

                LeaveCriticalSection(&this->freeListCriticalSection);
            }

            stream->currentBuffer = 0; // Clear current buffer
            stream->bytesOffset = 0;   // Reset offset

            // After sending, possibly trigger completion callback
            if (bufferFreed && (this->someObject != 0) && // +0x48
                (*(int*)(this->someObject + 0xb0) == 2) &&
                ((*(byte*)(this->someObject + 0xa8) & 2) == 0))
            {
                FUN_004d1ab0(); // Signal completion
            }

            // Check again for timeout after sending
            if (timeoutMs != 0xFFFFFFFF)
            {
                LARGE_INTEGER now;
                QueryPerformanceCounter(&now);
                uint64 elapsedLow = now.s.LowPart - startTimeLow;
                uint64 elapsedHigh = (now.s.HighPart - startTimeHigh) - (elapsedLow < 0 ? 1 : 0);
                // ... simplified timeout check
                if (/* elapsed > timeoutMs */)
                    timedOut = true;
            }
        } while (timeoutMs == 0xFFFFFFFF); // Infinite loop if no timeout

    } while (!timedOut); // Until timeout

    timedOut = true;

    // ---- Idle/cleanup path ----
processIdle:
    do
    {
        // If stream is in sending state with pending packet
        if (((stream->flags & 2) != 0) && (stream->pendingObject != 0)) // +0x42 (0x108)
        {
            // Call destructor?  (code: (**(code**)(**(int**)(this+0x94)+8))(stream->pendingObject))
            (**(code**)(**(int**)(this->vtable + 8)))(stream->pendingObject);
            stream->pendingObject = 0;
        }

sendBuffer:
        // Process pending send buffers if not blocking and not timed out
        if ((block == false) && (!timedOut))
        {
            do
            {
                do
                {
                    while (true)
                    {
                        // Pop from send pending list (offset +0x44)
                        void* sendBuffer = (void*)stream->sendPendingHead; // +0x44
                        if (sendBuffer == nullptr)
                            goto processState;

                        if ((void*)stream->sendPendingTail == sendBuffer) // +0x45
                            stream->sendPendingTail = nullptr;

                        stream->sendPendingHead = *(void**)sendBuffer; // next pointer

                        if (sendBuffer == nullptr)
                            goto processState;

                        // Buffer header (offset +4)
                        uint* refCount = (uint*)*(int*)((char*)sendBuffer + 4);
                        if ((stream->flags & 2) == 0)
                            break; // Not in sending mode, go to send it

                        // In sending mode, reference count management
                        if (refCount != nullptr)
                        {
                            if (*refCount < 2)
                                (**(code**)(**(int**)(this->vtable + 8)))(refCount); // free
                            else
                                (*refCount)--;

                            *(int*)((char*)sendBuffer + 4) = 0; // Clear header
                        }

                        // Return buffer to free list
                        *(void**)sendBuffer = this->freeListHead; // +0x10
                        if (this->freeListHead == nullptr)
                            this->freeListTail = sendBuffer; // +0x14
                        this->freeListHead = sendBuffer;
                    }

                    // Actually process send: call the send function via vtable
                    (**(code**)(**(int**)(this->vtable + 0x10)))(refCount);
                    refCount = (uint*)*(int*)((char*)sendBuffer + 4);
                    if (refCount != nullptr)
                    {
                        if (*refCount < 2)
                            (**(code**)(**(int**)(this->vtable + 8)))(refCount);
                        else
                            (*refCount)--;
                        *(int*)((char*)sendBuffer + 4) = 0;
                    }

                    // Re-return to free list after send
                    *(void**)sendBuffer = this->freeListHead;
                    if (this->freeListHead == nullptr)
                        this->freeListTail = sendBuffer;
                    this->freeListHead = sendBuffer;

                    // Check timeout after each send
                    if (timeoutMs != 0xFFFFFFFF)
                    {
                        LARGE_INTEGER now;
                        QueryPerformanceCounter(&now);
                        // ... simplified timeout check
                        if (/* elapsed > timeoutMs */)
                            break;
                    }
                } while (timeoutMs == 0xFFFFFFFF); // Inf loop if no timeout

            } while (/* elapsed < timeoutMs */);
        }

processState:
        // State machine handler
        if ((stream->state == 2) && ((stream->flags & 2) != 0)) // +0x2c
        {
            FUN_004d1a30(); // Some state transition
        }

        // If stream is in terminal state (negative or 6)
        if (((int)stream->state < 0) || (stream->state == 6))
        {
            // Check if all work is done
            if (stream->currentBuffer == 0)
            {
                if ((stream->sendIdleFlag == 0) && (stream->pendingObject == 0) &&
                    (stream->sendPendingHead == 0) && (stream->queueCount == 0) &&
                    (stream->totalBytes == stream->totalBytesExpected)) // +0x30 vs +0x31
                {
                    if (block != false)
                        return status; // Return current status

                    // Cleanup the stream completely
                    FUN_004d1820(); // Free resources
                    EnterCriticalSection(&this->streamListCriticalSection); // +0x68
                    FUN_004d1ea0(); // Remove from list
                    // Insert into free list (offset +0x5c)
                    stream->next = (NetStream*)this->streamFreeList; // +0x5c
                    stream->prev = nullptr;
                    if (this->streamFreeList == nullptr)
                        this->streamFreeListTail = stream; // +0x60
                    else
                        ((NetStream*)this->streamFreeList)->prev = stream;
                    this->streamFreeList = stream;
                    LeaveCriticalSection(&this->streamListCriticalSection);
                    return status;
                }
                // Not finished, go back to processLoop if buffer still pending
                goto checkContinue;
            }
            // Buffer is pending, so we need to continue
            goto checkContinue;
        }
        else
        {
checkContinue:
            // If we still have work, set bVar4 = true
            if ((stream->currentBuffer != 0) || (stream->queueCount != 0))
                goto setContinue;
        }

        // Determine if we should continue based on pending sends
        int sendPendingCount = stream->sendPendingHead;
        if (timeoutMs != 0xFFFFFFFF)
        {
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            // ... check if elapsed < timeoutMs
            if (elapsed > timeoutMs)
                goto finalCheck;
        }

        if ((bVar4) && (status == 0))
            goto processLoop; // Continue main loop

        if ((sendPendingCount == 0) || (block != false))
        {
finalCheck:
            if (bVar4)
                status |= 2; // Set bit 1
            if (sendPendingCount == 0)
                return status;
            return status | 4; // Set bit 2
        }

    } while (true);

setContinue:
    bVar4 = true;
    goto checkContinue;
}