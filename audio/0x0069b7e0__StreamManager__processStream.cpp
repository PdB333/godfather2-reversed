// FUNC_NAME: StreamManager::processStream
// Address: 0x0069b7e0
// Role: Processes streaming data buffers according to flags, performs double buffering and callback notification.

struct BufferWithCallback { // 16 bytes: 3 ints + function pointer
    int data[3];            // +0x00
    void (*callback)(int);  // +0x0C
};

class StreamManager {
public:
    // +0x00: unknown (vtable?)
    // +0x04: eventCallback (void (*)(int eventType, BufferWithCallback* buf1, BufferWithCallback* buf2))
    // +0x28: someObject (int)
    // +0x2C: param1 (int)
    // +0x3C: param2 (int)
    // unknown size
};

int __thiscall StreamManager::processStream(StreamManager* this, int streamHandle, int flagsStruct) {
    BufferWithCallback readBuffer;  // local_40 + local_34
    BufferWithCallback writeBuffer; // local_50 + local_44
    BufferWithCallback tempBuffer;  // local_30 + local_24
    BufferWithCallback tempBuffer2; // aiStack_20 + pcStack_14
    char result;

    // Begin stream operation
    beginStream(streamHandle); // FUN_004d3bc0

    // Initialize buffers
    readBuffer.data[0] = 0; readBuffer.data[1] = 0; readBuffer.data[2] = 0;
    readBuffer.callback = 0;
    writeBuffer.data[0] = 0; writeBuffer.data[1] = 0; writeBuffer.data[2] = 0;
    writeBuffer.callback = 0;

    // Try to get stream buffers (like a common pool identified by DAT_00d5ceec)
    result = getStreamBuffers(&DAT_00d5ceec, &readBuffer, &writeBuffer); // FUN_004d5210
    if (result) {
        // Clear temp buffers (probably for processing)
        clearBuffer(&readBuffer); // FUN_0069b040
        clearBuffer(&writeBuffer); // FUN_0069b040

        // Check bit 1 of flags (0x2): process read buffer
        if ((*(unsigned int*)(flagsStruct + 0x1C) >> 1) & 1) {
            result = isBufferReady(&readBuffer); // FUN_00699ec0
            if (result) {
                // Initialize temp buffer for output
                tempBuffer.data[0] = 0; tempBuffer.data[1] = 0; tempBuffer.data[2] = 0;
                tempBuffer.callback = 0;

                // Process read buffer into tempBuffer using object state
                processBuffer(*(int*)(this + 0x28), this + 0x3C, this + 0x2C, &tempBuffer, 0); // FUN_00698f20

                // Notify client via callback if set
                if (*(void***)this != 0 && *(void***)this[1] != 0) {
                    // Callback signature: void (int event, BufferWithCallback* buf1, BufferWithCallback* buf2)
                    ((void (*)(int, BufferWithCallback*, BufferWithCallback*))(*(int*)(this + 4)))(2, &readBuffer, &writeBuffer);
                }

                // Call tempBuffer's own callback if data exists
                if (tempBuffer.data[0] != 0) {
                    tempBuffer.callback(tempBuffer.data[0]);
                }
            }
        }

        // Check bit 2 of flags (0x4): process write buffer
        if ((*(unsigned int*)(flagsStruct + 0x1C) >> 2) & 1) {
            // Initialize temp buffer for input
            tempBuffer.data[0] = 0; tempBuffer.data[1] = 0; tempBuffer.data[2] = 0;
            tempBuffer.callback = 0;

            result = getBufferData(&writeBuffer, &tempBuffer); // FUN_0069b130
            if (result) {
                // Initialize second temp buffer for output
                tempBuffer2.data[0] = 0; tempBuffer2.data[1] = 0; tempBuffer2.data[2] = 0;
                tempBuffer2.callback = 0;

                // Process tempBuffer into tempBuffer2
                processBuffer(*(int*)(this + 0x28), this + 0x3C, this + 0x2C, &tempBuffer2, 0); // FUN_00698f20

                // Notify client via callback if set
                if (*(void***)this != 0 && *(void***)this[1] != 0) {
                    ((void (*)(int, BufferWithCallback*, BufferWithCallback*))(*(int*)(this + 4)))(4, &readBuffer, &writeBuffer);
                }

                // Call tempBuffer2's own callback if data exists
                if (tempBuffer2.data[0] != 0) {
                    tempBuffer2.callback(tempBuffer2.data[0]);
                }
            }

            // Call tempBuffer's own callback if data exists (cleanup)
            if (tempBuffer.data[0] != 0) {
                tempBuffer.callback(tempBuffer.data[0]);
            }
        }

        // Release buffers
        releaseBuffer(&readBuffer); // FUN_0069b380
        endStream(&writeBuffer);    // FUN_004d3e20

        // Free allocated buffers via their callbacks
        if (writeBuffer.data[0] != 0) {
            writeBuffer.callback(writeBuffer.data[0]);
        }
        if (readBuffer.data[0] != 0) {
            readBuffer.callback(readBuffer.data[0]);
        }
        if (tempBuffer.data[0] != 0) {
            tempBuffer.callback(tempBuffer.data[0]);
        }

        return 1;
    }

    // Failure path: free any partial allocations
    if (writeBuffer.data[0] != 0) {
        writeBuffer.callback(writeBuffer.data[0]);
    }
    if (readBuffer.data[0] != 0) {
        readBuffer.callback(readBuffer.data[0]);
    }
    if (tempBuffer.data[0] != 0) {
        tempBuffer.callback(tempBuffer.data[0]);
    }
    return 0;
}