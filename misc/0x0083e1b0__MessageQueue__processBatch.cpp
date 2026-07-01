// FUNC_NAME: MessageQueue::processBatch
// Address: 0x0083e1b0
// Role: Processes a batch of incoming messages from a queue

int __thiscall MessageQueue::processBatch(int *this, int maxIterations)
{
    int processedCount = 0;
    int result = 0;
    
    // Check if the queue is active (bit 0 of flags at +0x2b)
    if ((*(byte *)(this + 0x2b) & 1) != 0) {
        extern int __cdecl FUN_0083de60(); // unknown helper
        uint availableEntries = FUN_0083c160(); // returns number of available entries
        
        if (maxIterations != 0) {
            do {
                // Clear the "processing" flag (bit 3) at +0x2b
                this[0x2b] = this[0x2b] & 0xfffffff7;
                this[0x51] = 0; // reset some counter at +0x51
                
                // Check if there is room for more entries (current + pending <= available)
                if (availableEntries <= (uint)(this[0x26] + this[0x24])) break;
                
                // Prepare temporary buffer for extracting a message
                undefined4 *tempBufferPtr = &tempBuffer;
                int messageId = 0;
                int messageData = 0;
                undefined4 tempBuffer[3] = {0, 0, 0};
                undefined8 extendedId; // 8-byte ID output from virtual function
                int iStack_4; // high part of extendedId
                
                // Call virtual function at vtable+0x2c to extract the next message
                char success = (*(code **)(*(int *)this + 0x2c))(&extendedId, &messageId, &messageData, &tempBufferPtr);
                
                int newMessageId = messageId;
                int newMessageData = messageData;
                if (success != 0) {
                    // Set the "has message" flag (bit 3) at +0x2b
                    this[0x2b] = this[0x2b] | 8;
                    
                    // Store the extended ID at +0x4b (8 bytes)
                    *(undefined8 *)(this + 0x4b) = extendedId;
                    
                    // Update the linked list node at +0x4e
                    int *nodePtrPtr = this + 0x4e;
                    this[0x4d] = iStack_4; // store high part of extended ID (partially redundant)
                    if (*nodePtrPtr != newMessageId) {
                        if (*nodePtrPtr != 0) {
                            FUN_004daf90(nodePtrPtr); // remove old node from list
                        }
                        *nodePtrPtr = newMessageId;
                        if (newMessageId != 0) {
                            // Link the new node: set next pointer (at +0x4f) and update node's prev
                            this[0x4f] = *(int *)(newMessageId + 4);
                            *(int **)(newMessageId + 4) = nodePtrPtr;
                        }
                    }
                    this[0x50] = newMessageData; // store data at +0x50
                    this[0x51] = (int)tempBufferPtr; // store temp buffer pointer at +0x51
                    
                    char processed = FUN_0083c2e0(newMessageData);
                    if (processed == 0) break;
                    
                    processedCount++;
                    maxIterations--;
                }
            } while (maxIterations != 0);
        }
        
        // Clear processing flags after batch
        this[0x2b] = this[0x2b] & 0xfffffff7;
        this[0x51] = 0;
        result = processedCount;
    }
    return result;
}