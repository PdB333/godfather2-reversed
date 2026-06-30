// FUNC_NAME: PacketPool::allocate

#include <windows.h>
#include <cstring>

// Global data used by the packet pool
extern CRITICAL_SECTION gPacketPoolCS;                      // DAT_012224c0
extern uint32_t* gPacketFreeList;                            // DAT_012224ac – linked list of recycle wrappers
extern int* gMemoryAllocator;                                // DAT_01205868 – custom allocator vtable
extern PacketBuffer** gPacketArray;                          // DAT_011da8f0 – registered active buffers
extern int gPacketCount;                                     // DAT_01205850
extern uint8_t gPacketPoolEnabled;                           // DAT_00f15a3a – flag to allow reuse
extern int gPoolIdSmall;                                     // DAT_00e44658
extern int gPoolIdLarge;                                     // DAT_00e39f98

struct PacketBuffer {
    // +0x00: vtable pointer
    int* vtable;
    // +0x04: next in free list (when unused)
    PacketBuffer* next;
    // +0x08: self‑link or data field (used as copy target)
    PacketBuffer* selfLink;
    // +0x0C: reserved
    void* reserved;
    // +0x10: pointer to allocated payload
    void* data;
    // +0x14: capacity (size of the data buffer)
    uint32_t size;
    // +0x18: packet type tag
    uint32_t type;
    // +0x1C: internal flag #1 (triggers virtual release on reuse)
    uint8_t flagRecycle;
    // +0x1D: internal flag #2 (if zero, buffer is reusable)
    uint8_t flagAvailable;
    // +0x20: padding
    // +0x24: pool identifier (small vs large)
    uint32_t poolId;
};

// Forward declarations of internal helpers
void* allocateDataBuffer();                                   // FUN_0060bd50
void  notifyPacketPoolChange();                               // FUN_0060d1d0

PacketBuffer* PacketPool::allocate(
    uint32_t size,
    const void* srcData,
    PacketBuffer* reuseBuffer,
    int type
)
{
    bool found = false;
    PacketBuffer* result = nullptr;

    // Attempt to recycle an existing buffer from the free list
    if (gPacketPoolEnabled) {
        EnterCriticalSection(&gPacketPoolCS);

        // gPacketFreeList is a linked list of 2‑word nodes: [pointer to PacketBuffer, next node]
        for (uint32_t* node = gPacketFreeList; node != nullptr; node = (uint32_t*)*node[1]) {
            PacketBuffer* buf = (PacketBuffer*)*node;

            // Buffer is reusable when flagAvailable == 0, type matches,
            // and its capacity is between size and (size*4)/3 (i.e. within 133%)
            if (buf->flagAvailable == 0 &&
                buf->type == type &&
                size <= buf->size &&
                buf->size < (size * 4) / 3)
            {
                found = true;
                result = buf;

                // If the caller supplied a replacement node (reuseBuffer), copy the content into it
                if (reuseBuffer != nullptr) {
                    // Preserve the caller's poolId field (offset +0x24) across the copy
                    uint32_t savedPoolId = *(uint32_t*)((uint8_t*)reuseBuffer + 0x24);

                    // Copy the first 40 bytes (5 * 8) of the found buffer into reuseBuffer
                    memcpy(reuseBuffer, buf, 0x28);

                    // Restore the preserved field
                    *(uint32_t*)((uint8_t*)reuseBuffer + 0x24) = savedPoolId;

                    // Retrieve the self‑link of the found buffer (offset +0x08)
                    PacketBuffer* self = (PacketBuffer*)*(uint32_t*)((uint8_t*)buf + 0x08);

                    // Use reuseBuffer as the result
                    result = reuseBuffer;

                    if (self != nullptr) {
                        // If the global memory allocator exists, call its vfunc at index 1 (offset 4)
                        if (gMemoryAllocator != nullptr) {
                            (*(void (**)(void*, int))*gMemoryAllocator + 1)(self, 0);
                        }
                        // If self is not the same as buf, zero out the self‑link of buf
                        if (buf != self) {
                            *(uint32_t*)((uint8_t*)buf + 0x08) = 0;
                        }
                    }
                }

                // If new data was provided, allocate a new data buffer and copy
                if (srcData != nullptr) {
                    void* newData = allocateDataBuffer();
                    memcpy(newData, srcData, size);

                    // If the flagRecycle field is set, release the old internal buffer
                    if (result->flagRecycle != 0) {
                        // Call virtual function at index 12 (offset 0x30) on the buffer
                        (*(void (**)(PacketBuffer*))(*result->vtable + 0x30))(result);
                        notifyPacketPoolChange();
                        break;
                    }
                    result->flagAvailable = 0;
                }

                notifyPacketPoolChange();
                break;
            }
        }

        LeaveCriticalSection(&gPacketPoolCS);
        if (found) {
            goto finalize;
        }
    }

    // No reusable buffer found – allocate a brand new object
    if (reuseBuffer == nullptr) {
        // Allocate a PacketBuffer structure (0x30 bytes)
        int allocInfo[3] = {2, 0x10, 0};   // alignment descriptor
        result = (PacketBuffer*)((*(void* (*)(int, int*))*gMemoryAllocator)(0x30, allocInfo));
        // Store a self‑reference at offset +0x08 (used for recycling)
        *(PacketBuffer**)((uint8_t*)result + 0x08) = result;
    } else {
        // Use the caller‑supplied buffer and clear its self‑link
        *(uint32_t*)((uint8_t*)reuseBuffer + 0x08) = 0;
        result = reuseBuffer;
    }

    result->size = size;

    // Allocate the payload buffer
    int allocInfo2[3] = {2, 0x10, 0};
    void* dataBuf = (*(void* (*)(int, int*))*gMemoryAllocator)(size, allocInfo2);
    result->data = dataBuf;

    // Copy source data if provided
    if (srcData != nullptr) {
        memcpy(dataBuf, srcData, size);
    }

    // Store the source pointer (or original data handle) at offset +0x18
    *(const void**)((uint8_t*)result + 0x18) = srcData;

    result->flagRecycle = 0;
    result->flagAvailable = 0;

    // Register the new buffer in the global array
    EnterCriticalSection(&gPacketPoolCS);
    gPacketArray[gPacketCount] = result;
    gPacketCount++;
    LeaveCriticalSection(&gPacketPoolCS);

finalize:
    // Tag the buffer with the appropriate pool ID based on size
    if (size > 0x10000) {
        result->poolId = gPoolIdLarge;
    } else {
        result->poolId = gPoolIdSmall;
    }

    return result;
}