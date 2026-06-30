// FUNC_NAME: ReliablePacketBuffer::insertEvent
// Function at 0x00625d70
// Inserts a reliable event entry into the packet buffer. The event data is copied from the current write pointer position into a newly allocated block.
// Structure offsets:
//   this+0x08: current write pointer (uint32_t*)
//   this+0x10: pointer to a buffer descriptor with capacity at +0x20 and size at +0x24
//   newEntry+0x00..0x0F: header (0x0C stores eventData)
//   newEntry+0x10: data area (count * 8 bytes)

void ReliablePacketBuffer::insertEvent(uint32_t eventData, int32_t count) {
    // Grow buffer if necessary
    int32_t bufferDesc = *(int32_t*)(this + 0x10);
    if (*(uint32_t*)(bufferDesc + 0x20) <= *(uint32_t*)(bufferDesc + 0x24)) {
        FUN_00627360(); // grow buffer
    }

    // Allocate new event entry (header + data for 'count' items of 8 bytes each)
    int32_t newEntry = FUN_00638110(count);
    *(uint32_t*)(newEntry + 0x0C) = eventData;

    // Adjust write pointer back by count*8 (to make room for the new descriptor)
    *(int32_t*)(this + 8) = *(int32_t*)(this + 8) - count * 8;

    // Copy existing data from the (now adjusted) write pointer location into the new entry's data region
    if (count != 0) {
        uint32_t* dst = (uint32_t*)(newEntry + 0x10 + count * 8);
        do {
            dst -= 2; // move back 8 bytes (two uint32_t)
            uint32_t* src = (uint32_t*)((int32_t)dst + *(int32_t*)(this + 8) + (-0x10 - newEntry));
            *dst = *src;
            *(dst + 1) = *(src + 1);
        } while (--count != 0);
    }

    // Write the event descriptor: type 6 and pointer to the new entry
    uint32_t* writePtr = *(uint32_t**)(this + 8);
    writePtr[0] = 6;        // event type tag
    writePtr[1] = newEntry; // pointer to allocated event
    *(int32_t*)(this + 8) = (int32_t)(writePtr + 2); // advance write pointer by 8 bytes
}