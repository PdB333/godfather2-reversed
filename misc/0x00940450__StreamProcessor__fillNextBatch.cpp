// FUNC_NAME: StreamProcessor::fillNextBatch
uint __fastcall StreamProcessor::fillNextBatch(StreamContext* ctx)
{
    // ctx->+0x00: stride (size of each item in bytes)
    // ctx->+0x04: baseAddress (pointer to item data array)
    // ctx->+0x08: itemList (pointer to ItemList struct)
    // ctx->+0x0C: currentIndex (position in index array)
    // ctx->+0x10: bufferCount (0-3, number of items in triple buffer)

    ItemList* itemList = (ItemList*)ctx->itemList;
    uint count = itemList->count;           // +0x0C
    uint idx = ctx->currentIndex;           // +0x0C
    ushort* indices = (ushort*)itemList->indices; // +0x88 (0x22*4)

    do {
        if (count <= idx) {
            // No more items; return itemList pointer with low byte cleared
            return (uint)itemList & 0xFFFFFF00;
        }

        ushort itemId = indices[idx];       // read next item index
        ctx->currentIndex = idx + 1;        // advance index

        if (ctx->bufferCount == 3) {
            // Triple buffer is full; shift slots to make room
            ctx->bufferCount = 2;
            // Copy slot1 to slot0
            gBufferSlot0 = gBufferSlot1;
            // Copy slot2 to slot1
            gBufferSlot1 = gBufferSlot2;
        }

        if (itemId == 0xFFFF) {
            // End-of-list marker; reset buffer
            ctx->bufferCount = 0;
        } else {
            int slot = ctx->bufferCount;
            ctx->bufferCount = slot + 1;

            // Compute address of item data
            uint8_t* itemData = (uint8_t*)(itemId * ctx->stride + ctx->baseAddress);

            // Copy 12 bytes (3 dwords) into the buffer slot
            uint32_t* slotPtr = (uint32_t*)((uintptr_t)&gBufferSlot0 + slot * 0x10);
            slotPtr[0] = *(uint32_t*)(itemData + 0);
            slotPtr[1] = *(uint32_t*)(itemData + 4);
            slotPtr[2] = *(uint32_t*)(itemData + 8);

            if (ctx->bufferCount == 3) {
                // Buffer is now full; return item data address with low byte set to 1
                return ((uintptr_t)itemData & 0xFFFFFF00) | 1;
            }
        }

        idx = ctx->currentIndex;
    } while (true);
}