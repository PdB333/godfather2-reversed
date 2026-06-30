// FUNC_NAME: PacketPool::getBuffer
// Address: 0x0060b620
// Allocates or reuses a packet buffer from the pool. If param_3 is non-null, attempts to find a matching free buffer from the free list.
// Otherwise, allocates a new buffer and adds it to the pool array.

typedef struct PacketBuffer PacketBuffer;

struct PacketBuffer {
    void **vtable;          // +0x00
    void *next;             // +0x08 (linked list or internal pointer)
    uint8_t *dataBuffer;    // +0x10 (4 bytes) - allocated data storage
    uint32_t bufferSize;    // +0x14 (4 bytes) - capacity of the buffer
    int32_t bufferType;     // +0x18 (4 bytes) - type identifier
    uint8_t flag1c;        // +0x1c
    uint8_t flag1d;        // +0x1d - non-zero indicates lock/use flag
    int32_t unknown1e;     // +0x1e padding?
    // offset 0x20: another 8-byte field copied as chunk (param_3[4])
    // offset 0x24: written later, some flag
    int32_t extraFlag;     // +0x24 - set based on buffer size threshold
    // rest up to 0x30
};

// Global state
extern CRITICAL_SECTION g_packetPoolCriticalSection;   // DAT_012224c0
extern PacketBuffer** g_packetPoolList;                 // DAT_012224ac - array of pool entries (first field: buffer ptr, second: next)
extern void** g_packetPoolAllocatorVtable;              // DAT_01205868 - allocator vtable (operator new)
extern int32_t g_packetPoolCounter;                     // DAT_01205850 - number of buffers in pool array
extern PacketBuffer* g_packetPoolArray[];               // DAT_011da8f0 - array of allocated buffers
extern uint8_t g_packetPoolEnabled;                     // DAT_00f15a3a - flag whether pool is active
extern int32_t g_packetPoolFlagLarge;                   // DAT_00e39f98 - flag for large buffers (>0x10000)
extern int32_t g_packetPoolFlagSmall;                   // DAT_00e44658 - flag for small buffers

PacketBuffer* PacketPool::getBuffer(uint32_t size, void* data, PacketBuffer* existingBuffer, int32_t typeId)
{
    bool found = false;
    PacketBuffer* result = existingBuffer;

    if (g_packetPoolEnabled != 0) {
        EnterCriticalSection(&g_packetPoolCriticalSection);
        // Search the free list for a matching buffer
        PacketBuffer** entry = g_packetPoolList;
        while (entry != nullptr) {
            PacketBuffer* buf = *entry;  // first element is the buffer pointer
            if (buf->flag1d == 0 &&                           // not in use
                buf->bufferType == typeId &&                  // same type
                size <= buf->bufferSize &&                    // fits within capacity
                buf->bufferSize < (size * 4) / 3)             // not more than 1.33x needed
            {
                found = true;
                result = buf;
                if (existingBuffer != nullptr) {
                    // Copy existing buffer data into the found buffer?
                    // This seems to copy 5*8 = 40 bytes from found to existingBuffer
                    uint32_t tmp = *(uint32_t*)((uint8_t*)existingBuffer + 4);
                    *existingBuffer = *buf;   // copy 8 bytes
                    existingBuffer[1] = buf[1];
                    existingBuffer[2] = buf[2];
                    existingBuffer[3] = buf[3];
                    existingBuffer[4] = buf[4];
                    *(uint32_t*)((uint8_t*)existingBuffer + 4) = tmp; // restore something?
                    // Handle internal pointer? buf[4] is offset 0x20?
                    PacketBuffer* internalPtr = (PacketBuffer*)buf[4]; // offset 0x20
                    if (internalPtr != nullptr) {
                        if (g_packetPoolAllocatorVtable != nullptr) {
                            // call a method on internalPtr (maybe release?)
                            (*(void (**)(PacketBuffer*, int))(*g_packetPoolAllocatorVtable + 4))(internalPtr, 0);
                        }
                        if (buf != internalPtr) {
                            // clear the internal pointer in the found buffer?
                            *(uint32_t*)((uint8_t*)buf + 4) = 0; // offset 0x04? unclear
                        }
                    }
                }
                result = existingBuffer;  // Override? Actually if existingBuffer is non-null, we used it.
                if (data != nullptr) {
                    uint8_t* newData = (uint8_t*)FUN_0060bd50(); // some allocator
                    memcpy(newData, data, size);
                    if (result->flag1c != 0) {
                        // call vtable function at offset 0x30 on result->vtable
                        (*(void (**)(void*))(*result->vtable + 0x30))(result);
                        FUN_0060d1d0();
                        break;
                    }
                    result->flag1d = 0;
                }
                FUN_0060d1d0();
                break;
            }
            // Move to next entry (second element)
            entry = (PacketBuffer**)entry[1];
        }
        LeaveCriticalSection(&g_packetPoolCriticalSection);
        if (found) goto LAB_0060b835;
    }

    if (existingBuffer == nullptr) {
        // Allocate a new buffer structure
        int allocParam[3] = {2, 0x10, 0}; // flags for allocator
        result = (PacketBuffer*)(**(void** (*)(int, int*))(*g_packetPoolAllocatorVtable))(0x30, allocParam);
        result->next = result; // self-referencing? unclear
    } else {
        result->next = nullptr; // offset 0x04? Actually setting next pointer to null
    }

    result->bufferSize = size;                         // +0x14
    int allocParam2[3] = {2, 0x10, 0};
    uint8_t* bufferData = (uint8_t*)(**(void** (*)(uint32_t, int*))(*g_packetPoolAllocatorVtable))(size, allocParam2);
    result->dataBuffer = bufferData;                   // +0x10
    if (data != nullptr) {
        memcpy(bufferData, data, size);
    }
    result->bufferType = (int32_t)data;  // This seems wrong; store param_2 as type? Or is param_2 used as data pointer? Actually source code: *(void **)(param_3 + 3) = param_2; So type is stored as pointer? Might be union.
    result->flag1c = 0;
    result->flag1d = 0;

    EnterCriticalSection(&g_packetPoolCriticalSection);
    g_packetPoolArray[g_packetPoolCounter] = result;
    g_packetPoolCounter++;
    LeaveCriticalSection(&g_packetPoolCriticalSection);

LAB_0060b835:
    if (size > 0x10000) {
        result->extraFlag = g_packetPoolFlagLarge;   // +0x24
    } else {
        result->extraFlag = g_packetPoolFlagSmall;
    }
    return result;
}