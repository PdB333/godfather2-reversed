// FUNC_NAME: ReliablePacketQueue::process

// Reconstructed from function at 0x00620a90
// This function processes a reliable packet queue with circular buffer and callback handling.
// It manages send/retry logic with a timer for delayed callback execution.

class ReliablePacketQueue {
public:
    // Virtual function table at +0x00
    // vtable+0x0c: virtual update function (called multiple times)
    virtual void someUpdateFunction() = 0; // vtable offset 0x0c (index 3)

    // Known offsets (relative to 'this' pointer, int* accessed as int)
    // +0x08: m_streamId           (param_1[2])
    // +0x28: m_processCallback    (param_1[10]) - callback function for each packet
    // +0x2c: m_callbackArg        (param_1[0xb]) - argument to callback
    // +0x30: m_timerCallback      (param_1[0xc]) - timer/trigger callback
    // +0x34: m_timerContext       (param_1[0xd]) - context for timer callback
    // +0x48: m_delay              (param_1[0x12]) - float delay factor
    // +0x80: m_timerFired         (param_1[0x20]) - byte flag (0/1)
    // +0x84: m_capacity           (param_1[0x21]) - max entries in circular buffer
    // +0x88: m_count              (param_1[0x22]) - current number of pending entries
    // +0x8c: m_writeData          (param_1[0x23]) - data to write into next slot
    // +0x90: m_readIndex          (param_1[0x24])
    // +0x94: m_writeIndex         (param_1[0x25])
    // +0x98: m_bufferBase         (param_1[0x26]) - base address of circular buffer (each entry 16 bytes)
    // +0xa0: m_unknownPtr         (param_1[0x28]) - pointer, used with offset +0x10 for stream operations

    void process() {
        // Pre-update
        FUN_00620dd0(); // Likely base class timer/update preparation
        this->someUpdateFunction(); // Virtual update

        // Get current time (e.g., from real-time clock)
        int currentTime = FUN_00b9a1c0(); // Returns current time in milliseconds or ticks

        // Check if delayed callback should fire: (m_delay * g_timeScale <= currentTime)
        // DAT_00e2e230 is likely a time scaling factor (e.g., milliseconds per tick)
        if ((int)((float)m_delay * DAT_00e2e230) <= currentTime && m_timerCallback != 0) {
            // Enter global critical section (lock)
            FUN_00ab4db0(&DAT_00e2e6f0); // Acquire mutex

            // Re-check after lock (double-checked locking pattern)
            this->someUpdateFunction();
            currentTime = FUN_00b9a1c0();
            if ((int)((float)m_delay * DAT_00e2e230) <= currentTime && m_timerCallback != 0) {
                // Ensure the timer callback hasn't already been invoked
                if (m_timerFired == 0) {
                    m_timerFired = 1;
                    // Invoke the timer callback with its context
                    m_timerCallback(m_timerContext);
                }
                FUN_00ab4e70(); // Leave critical section
                return;
            }
            FUN_00ab4e70(); // Leave critical section if condition failed
        }

        // Process pending packets in circular buffer
        if (m_count != 0) {
            int writeIndex = m_writeIndex;
            while (writeIndex != 0) {
                // Prepare bitstream for writing
                // FUN_00c9cbe0 is likely BitStream::writeBegin with opcode 3 (send attempt)
                int* outputList[2]; // apuStack_30
                FUN_00c9cbe0(m_streamId, *(int*)(m_unknownPtr + 0x10), 3, outputList);

                // Set the output pointer to current write slot (if queue not empty)
                if (m_count == 0) {
                    outputList[0] = 0; // No slot to fill
                } else {
                    outputList[0] = (int*)(m_bufferBase + m_writeIndex * 0x10);
                }

                FUN_00c9eac0(); // BitStream::prepareBody?
                FUN_00c9cd40(3, outputList); // BitStream::send with opcode 3
                FUN_00c9eae0(); // BitStream::flush?

                // Check sentinel value (DAT_00e2b1a4 is likely -1.0f or a unique value)
                // If the result of the send operation equals the sentinel and queue is empty -> break
                if (fStack_28 != DAT_00e2b1a4 || m_count == 0)
                    break;

                // Write data into the current slot (if send succeeded but needs retry)
                writeIndex = m_writeIndex; // Re-read writeIndex (may have changed?)
                int base = m_bufferBase;
                int* slot = (int*)(base + writeIndex * 0x10);
                *slot = m_writeData;                    // slot[0]
                slot[2] = *(int*)(base + 8 + writeIndex * 0x10); // slot[2] preserved
                slot[1] = 0;                            // slot[1] reset

                // Advance write index cyclically
                m_writeIndex = writeIndex + 1;
                if (m_writeIndex >= m_capacity) {
                    m_writeIndex = 0;
                }
                m_count--; // Actually decrementing count (though earlier it was incremented? Logic: maybe count is slots occupied)
                writeIndex = m_count; // Continue loop
            }

            // Once we have processed some, try to read back responses
            int* readPtr = 0;
            int itemsProcessed = 0; // iStack_38

            // If there's room in the queue (m_count < m_capacity), attempt to take a pending entry for processing
            if (m_count != m_capacity) {
                readPtr = (int*)(m_bufferBase + m_readIndex * 0x10);
                m_readIndex++;
                if (m_readIndex >= m_capacity) {
                    m_readIndex = 0;
                }
                m_count++; // Increment count (indicating the slot is now "in use" again? ambiguous)
            }

            if (readPtr != 0) {
                while (true) {
                    FUN_00cff950(); // Lock (e.g., mutex lock for async response)

                    // Prepare a response packet structure on stack
                    int responseData[3]; // uStack_1c, uStack_18, uStack_10, uStack_c (some fields)
                    // Actually: uStack_c = 0 (placeholder), uStack_1c = readPtr[2], uStack_10 = readPtr[0], uStack_18 = 0
                    responseData[0] = readPtr[0]; // +0x00: some identifier
                    responseData[1] = 0;           // +0x04: reserved
                    responseData[2] = readPtr[2];  // +0x08: status/data
                    int* responsePtr = responseData; // puStack_34

                    if (m_processCallback == 0) {
                        goto checkLoopBreak;
                    }

                    // Invoke callback with response and user argument
                    m_processCallback(&responsePtr, m_callbackArg);

                    // If callback returned a non-zero value at responsePtr[3] (offset +0x0c)
                    if (responsePtr[3] != 0) {
                        // Update the slot in the buffer with the returned value
                        if (m_count != m_capacity) {
                            m_readIndex++;
                            if (m_readIndex >= m_capacity) {
                                m_readIndex = 0;
                            }
                            m_count++;
                        }
                        readPtr[0] = responsePtr[3];
                        readPtr[1] = 0;

                        // Send acknowledgment via bitstream
                        int* ackOutput[2]; // apuStack_30
                        FUN_00c9cbe0(m_streamId, *(int*)(m_unknownPtr + 0x10), 2, ackOutput);
                        ackOutput[0] = readPtr;
                        FUN_00c9eac0();
                        FUN_00c9cd40(2, ackOutput);
                        FUN_00c9eae0();

                        itemsProcessed++;
                        if (itemsProcessed > 5) {
                            break; // Limit to 5 items per call
                        }
                    }

checkLoopBreak:
                    FUN_00cff970(); // Unlock

                    // Attempt to get next pending entry
                    readPtr = 0;
                    if (m_count != m_capacity) {
                        readPtr = (int*)(m_bufferBase + m_readIndex * 0x10);
                        m_readIndex++;
                        if (m_readIndex >= m_capacity) {
                            m_readIndex = 0;
                        }
                        m_count++;
                    }
                    FUN_00cff970(); // Unlock (again? likely oversight in decompilation)
                    if (readPtr == 0) {
                        return; // No more entries to process
                    }
                }
                // Exit path when too many items processed
                FUN_00cff970(); // Unlock
            }
        }
    }
};