// FUN_0043d450: ReplicationStream::processStream
int __thiscall ReplicationStream::processStream(int typeId, uint* data, uint size) {
    // +0x20: pointer to array of pairs (type, handler)
    int* table = *(int**)(this + 0x20);
    int handler = 0;
    // Find handler for the given type or default (type==0 entry)
    do {
        if (typeId == *table || *table == 0) {
            handler = table[1];
        }
        table += 2;
    } while (handler == 0);
    
    // Notify start of processing for this type
    notify(typeId, handler); // FUN_0043cfc0(this, handler)
    
    if (data != NULL && size > 3) {
        uint itemCount = *data;
        data++;
        size -= 4;
        uint processed = 0;
        while (processed < itemCount) {
            if (size < 0x24) break;
            uint payloadSize = data[6]; // offset 24 bytes (6 uint) from item start
            uint alignedSize = (payloadSize + 3) & ~3; // round to 4
            if (size - 0x24 < alignedSize) break;
            
            // Allocate/initialize object with payload data
            int obj = allocateObject(payloadSize, data, data[4], data[5]); // FUN_0043d020
            *(uint*)(obj + 4) = data[7];
            memcpy((void*)(obj + 0x0C), data + 9, payloadSize);
            
            // Update remaining size and pointer
            size -= 0x24 + alignedSize;
            data = (uint*)((int)(data + 9) + alignedSize);
            
            *(int*)(obj + 8) = handler; // store the handler ID
            processed++;
        }
    }
    
    // Log information (global debug)
    DebugInfo debugInfo = DEBUG_GLOBAL; // DAT_0120e91c
    debugInfo.param1 = 0;
    debugInfo.param2 = 0;
    logDebug(&debugInfo, 0);
    
    return 1;
}